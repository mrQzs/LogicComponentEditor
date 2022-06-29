#include "YDControlDO.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDControlDOName : public YDPropertyName {
 public:
  QString name() const { return YDControlDOName::tr("名称"); }
  QString codeName() const { return "Name"; }

 protected:
  virtual QString get(YDModule *m) const { return m->name(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) {
      auto name = QSTRTSTR(str);
      int ret = YDProjectManage::updateLogicProcessName(
          m->getYDTask()->id(), m->getLogicProcessId(), name);
      switch (ret) {
        case -1:
          QMessageBox::warning(nullptr, YDControlDOName::tr("错误"),
                               YDControlDOName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDControlDOName::tr("错误"),
                               YDControlDOName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDControlDOSelect : public YDPropertyDoVar {
 public:
  QString name() const { return YDControlDOSelect::tr("DO选择"); }
  QString codeName() const { return "Select"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getDOName(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) m->setDOName(str);
  }
};

class YDControlDOState : public YDPropertyEnum {
 public:
  YDControlDOState(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDControlDOState::tr("DO状态"); }
  QString codeName() const { return "State"; }

 protected:
  virtual int get(YDModule *m) const { return m->getDOState(); }
  virtual void set(YDModule *m, int index) { m->setDOState(index); }
};

YDControlDO::YDControlDO() {
  setPreview(QPixmap(":/Module/Control_Do.png"));
  auto w = new YDModuleWidget(this, IoColor, IoFColor);

  setWidget(w);

  QStringList dostate;
  dostate << YDControlDO::tr("打开") << YDControlDO::tr("关闭");

  m_properties << new YDControlDOName;
  m_properties << new YDControlDOSelect;
  m_properties << new YDControlDOState(dostate);
}

Module::Type YDControlDO::type() const { return Module::Control_DO; }

void YDControlDO::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachDOControlModule(logicProcessId, m_doControlModule);
  Q_ASSERT(m_doControlModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDControlDO::tr("控制DO输出%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDControlDO::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachDOControlModule(lp->id, m_doControlModule);
  Q_ASSERT(m_doControlModule);
  setData();
}

void YDControlDO::getData() {
  m_logicProcess->type = LOGIC_PROCESS_DO_CONTROL;
  auto doname = getDOName();
  auto doinfos = YDProjectManage::getDOInfos();
  for (auto a : doinfos) {
    auto name = STRTQSTR(a->io_name.c_str());
    if (doname == name) {
      m_doControlModule->device_id = a->device_id;
      m_doControlModule->do_index = a->io_index;
      break;
    }
  }

  m_doControlModule->do_status = getDOState();
}

void YDControlDO::setData() {
  auto id = m_doControlModule->device_id;
  auto index = m_doControlModule->do_index;
  auto status = m_doControlModule->do_status;

  auto doinfos = YDProjectManage::getDOInfos();
  for (auto a : doinfos) {
    if (id == a->device_id && index == a->io_index) {
      setDOName(STRTQSTR(a->io_name.c_str()));
      break;
    }
  }
  setDOState(status);
}
