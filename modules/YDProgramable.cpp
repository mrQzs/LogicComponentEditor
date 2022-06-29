#include "YDProgramable.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDProgramableName : public YDPropertyName {
 public:
  QString name() const { return YDProgramableName::tr("名称"); }
  QString codeName() const { return "Name"; }

 protected:
  virtual QString get(YDModule *m) const { return m->name(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) {
      auto name = QSTRTSTR(str);
      if (HOME_MOVE_SCRIPT_NAME == name) {
        QMessageBox::warning(nullptr, YDProgramableName::tr("错误"),
                             YDProgramableName::tr("名称已重复!"));
        return;
      }
      int ret = YDProjectManage::updateLogicProcessName(
          m->getYDTask()->id(), m->getLogicProcessId(), name);
      switch (ret) {
        case -1:
          QMessageBox::warning(nullptr, YDProgramableName::tr("错误"),
                               YDProgramableName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDProgramableName::tr("错误"),
                               YDProgramableName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDProgramableSafe : public YDPropertySafeVar {
 public:
  QString name() const { return YDProgramableSafe::tr("安全保护"); }
  QString codeName() const { return "Safe"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSafeVarName(); }
  virtual void set(YDModule *m, QString str) { m->setSafeVarName(str); }
};

class YDProgramableTime : public YDPropertyInt {
 public:
  YDProgramableTime() : YDPropertyInt{0, 6000000} {}
  QString name() const { return YDProgramableTime::tr("等待时间(毫秒)"); }
  QString codeName() const { return "Time"; }

 protected:
  virtual int get(YDModule *m) const { return m->getWaitTime(); }
  virtual void set(YDModule *m, int value) { m->setWaitTime(value); }
};

class YDProgramableSize : public YDPropertyInt {
 public:
  YDProgramableSize() : YDPropertyInt{0, 6000000} {}
  QString name() const { return YDProgramableSize::tr("数据缓存大小(字节)"); }
  QString codeName() const { return "Size"; }

 protected:
  virtual int get(YDModule *m) const { return m->getDataCashSize(); }
  virtual void set(YDModule *m, int value) { m->setDataCashSize(value); }
};

class YDProgramableWay : public YDPropertyEnum {
 public:
  YDProgramableWay(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDProgramableWay::tr("脚本类型"); }
  QString codeName() const { return "Type"; }

 protected:
  virtual int get(YDModule *m) const { return m->getCodeType(); }
  virtual void set(YDModule *m, int index) { m->setCodeType(index); }
};

class YDProgramCode : public YDCustomWProp {
 public:
  YDProgramCode(YDModule *m) : YDCustomWProp(m, WidgetType::e_PROGRAM) {}
  virtual QString name() const { return YDProgramCode::tr("脚本代码"); }
  virtual QString codeName() const { return "Code"; }

 protected:
  virtual QStringList get(YDModule *m) const { return m->getCodeList(); }
  virtual void set(YDModule *m, QStringList list) { m->setCodeList(list); }
};

YDProgramable::YDProgramable() {
  setPreview(QPixmap(":/Module/Program.png"));
  auto w = new YDModuleWidget(this, OtherColor, OtherFColor);

  setWidget(w);

  m_properties << new YDProgramableName;
  m_properties << new YDProgramableSafe;
  // m_properties << new YDProgramableTime;
  // m_properties << new YDProgramableSize;

  QStringList type;
  type << "VB.NET"
       << "C#.NET";
  //       << "C/C++";

  m_properties << new YDProgramableWay(type);
  m_properties << new YDProgramCode(this);
}

Module::Type YDProgramable::type() const { return Module::Programable; }

void YDProgramable::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachProgramModule(logicProcessId, m_programModule);
  Q_ASSERT(m_programModule);

  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDProgramable::tr("可编程模块%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDProgramable::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachProgramModule(lp->id, m_programModule);
  Q_ASSERT(m_programModule);
  setData();
}

void YDProgramable::getData() {
  m_logicProcess->type = LOGIC_PROCESS_PROGRAMABLE;

  uint64 safeVarId = YDProjectManage::getSafeVirtualVarId(getSafeVarName());
  if (0 != safeVarId) m_programModule->safeguard_referid = safeVarId;
  m_programModule->wait_time = getWaitTime();
  m_programModule->data_cache_size = getDataCashSize();
  m_programModule->script_type = getCodeType() + SCRIPT_TYPE_VB_NET;
}

void YDProgramable::setData() {
  auto safeVarName = YDProjectManage::getSafeVirtualVarName(
      m_programModule->safeguard_referid);
  setSafeVarName(safeVarName);

  setWaitTime(m_programModule->wait_time);
  setDataCashSize(m_programModule->data_cache_size);
  setCodeType(m_programModule->script_type - SCRIPT_TYPE_VB_NET);

  auto name = QSTRTSTR(this->name());
  auto type = m_programModule->script_type;
  auto file = YDProjectManage::getProgrammableProcessCodeFilePath(name, type);
  auto filestr = STRTQSTR(file.c_str());
  auto code = YDHelper::readFile(filestr);
  if (code.isEmpty()) {
    setCodeList(QStringList{YDProgramable::tr("无代码")});
  } else {
    setCodeList(QStringList{YDProgramable::tr("待检查")});
  }
}
