#include "YDControlAO.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDControlAOName : public YDPropertyName {
 public:
  QString name() const { return YDControlAOName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDControlAOName::tr("错误"),
                               YDControlAOName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDControlAOName::tr("错误"),
                               YDControlAOName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDControlAOSelect : public YDPropertyAoVar {
 public:
  QString name() const { return YDControlAOSelect::tr("AO选择"); }
  QString codeName() const { return "Select"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getAOName(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) m->setAOName(str);
  }
};

class YDControlAOValue : public YDPropertyIOVar {
 public:
  QString name() const { return YDControlAOValue::tr("AO数值"); }
  QString codeName() const { return "Value"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getIOName(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) m->setIOName(str);
  }
};

YDControlAO::YDControlAO() {
  setPreview(QPixmap(":/Module/Control_Ao.png"));
  auto w = new YDModuleWidget(this, IoColor, IoFColor);

  setWidget(w);

  m_properties << new YDControlAOName;
  m_properties << new YDControlAOSelect;
  m_properties << new YDControlAOValue;
}

Module::Type YDControlAO::type() const { return Module::Control_AO; }

void YDControlAO::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachAOControlModule(logicProcessId, m_aoControlModule);
  Q_ASSERT(m_aoControlModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDControlAO::tr("控制AO输出%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDControlAO::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachAOControlModule(lp->id, m_aoControlModule);
  Q_ASSERT(m_aoControlModule);
  setData();
}

void YDControlAO::getData() {
  m_logicProcess->type = LOGIC_PROCESS_AO_CONTROL;
  auto aoname = getAOName();
  auto ioname = getIOName();
  auto aoinfos = YDProjectManage::getAOInfos();
  for (auto a : aoinfos) {
    auto name = QString::fromLocal8Bit(a->io_name.c_str());
    if (aoname == name) {
      m_aoControlModule->device_id = a->device_id;
      m_aoControlModule->ao_index = a->io_index;
      break;
    }
  }

  m_aoControlModule->value_referid = YDProjectManage::getVarId(ioname);
}

void YDControlAO::setData() {
  auto id = m_aoControlModule->device_id;
  auto index = m_aoControlModule->ao_index;
  auto varId = m_aoControlModule->value_referid;

  auto aoinfos = YDProjectManage::getAOInfos();
  for (auto a : aoinfos) {
    if (id == a->device_id && index == a->io_index) {
      setAOName(QString::fromLocal8Bit(a->io_name.c_str()));
      break;
    }
  }

  auto varName = YDProjectManage::getVarName(varId);
  setIOName(varName);
}
