#include "YDConditionLoop.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleIFElseWidget.h"
#include "widget/module/YDModuleLoopWidget.h"
#include "widget/module/YDModuleWidget.h"

class YDConditionLoopName : public YDPropertyName {
 public:
  QString name() const { return YDConditionLoopName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDConditionLoopName::tr("错误"),
                               YDConditionLoopName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateLoopName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDConditionLoopName::tr("错误"),
                               YDConditionLoopName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDConditionLoopWay : public YDPropertyEnum {
 public:
  YDConditionLoopWay(QStringList enumText) : YDPropertyEnum{enumText} {}
  virtual QString name() const { return YDConditionLoopWay::tr("逻辑运算符"); }
  virtual QString codeName() const { return "Way"; }

 protected:
  virtual int get(YDModule *m) const { return m->getLoopConditionWay(); }
  virtual void set(YDModule *m, int index) { m->setLoopConditionWay(index); }
};

class YDConditionLoopVar : public YDCustomWProp {
 public:
  YDConditionLoopVar() : YDCustomWProp(WidgetType::e_CONDITION) {}
  virtual QString name() const { return YDConditionLoopVar::tr("判断条件"); }
  virtual QString codeName() const { return "Conditions"; }

 protected:
  virtual QStringList get(YDModule *m) const {
    return m->getLoopConditionList();
  }
  virtual void set(YDModule *m, QStringList list) {
    m->setLoopConditionList(list);
  }
};

YDConditionLoop::YDConditionLoop() : m_widget{new YDModuleLoopWidget(1, this)} {
  setPreview(QPixmap(":/Module/Condition_Loop.png"));
  setWidget(m_widget);

  QStringList conditionWay;
  conditionWay << YDConditionLoop::tr("与运算")
               << YDConditionLoop::tr("或运算");

  m_properties << new YDConditionLoopName;
  m_properties << new YDConditionLoopWay(conditionWay);
  m_properties << new YDConditionLoopVar;
}

Module::Type YDConditionLoop::type() const { return Module::Condition_Loop; }

void YDConditionLoop::initModule(YDTask *task, uint64 parentId) {
  setTask(task);
  YDProjectManage::createTaskConditionLoopProcess(task->id(),
                                                  m_conditionProcess);
  Q_ASSERT(m_conditionProcess);
  m_logicProcess = m_conditionProcess->pProcess;
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDConditionLoop::tr("条件循环%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());

  m_conditionProcess->pConditionModule->logic_operator = LOGIC_OPERATOR_AND;
}

void YDConditionLoop::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::getConditionLoopProcess(lp->id, m_conditionProcess);
  Q_ASSERT(m_conditionProcess);
  setData();
}

void YDConditionLoop::getData() {
  Q_ASSERT(m_conditionProcess->pModule);

  m_conditionProcess->pModule->listProcessIds.clear();

  auto loopIds = m_widget->getLoopModulesIds(getLogicProcessId());

  for (auto id : loopIds)
    m_conditionProcess->pModule->listProcessIds.push_back(id);
}

void YDConditionLoop::setData() {
  Q_ASSERT(m_conditionProcess->pModule);
  auto processlist = m_conditionProcess->pModule->listProcessIds;
  if (!processlist.empty()) {
    std::vector<yd::lg::LogicProcess *> listProcesses;
    YDProjectManage::getProcesses(getLogicProcessId(), processlist,
                                  listProcesses);
    m_widget->addLoopModules(m_task, listProcesses);
  }
}

int YDConditionLoop::high() const { return m_widget->high(); }

void YDConditionLoop::setStateMap(
    const QMap<uint32, yd::proto::ProcState> &map) {
  m_widget->setState(map);
}

void YDConditionLoop::resize() { m_widget->resizeModel(); }
