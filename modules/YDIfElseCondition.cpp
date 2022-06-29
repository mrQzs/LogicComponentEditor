#include "YDIfElseCondition.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleIFElseWidget.h"
#include "widget/module/YDModuleWidget.h"

class YDIfElseConditionName : public YDPropertyName {
 public:
  QString name() const { return YDIfElseConditionName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDIfElseConditionName::tr("错误"),
                               YDIfElseConditionName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateIfElseName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDIfElseConditionName::tr("错误"),
                               YDIfElseConditionName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDIfElseConditionWay : public YDPropertyEnum {
 public:
  YDIfElseConditionWay(QStringList enumText) : YDPropertyEnum{enumText} {}
  virtual QString name() const {
    return YDIfElseConditionWay::tr("逻辑运算符");
  }
  virtual QString codeName() const { return "Way"; }

 protected:
  virtual int get(YDModule *m) const { return m->getConditionWay(); }
  virtual void set(YDModule *m, int index) { m->setConditionWay(index); }
};

class YDIfElseConditionVar : public YDCustomWProp {
 public:
  YDIfElseConditionVar() : YDCustomWProp(WidgetType::e_CONDITION) {}
  virtual QString name() const { return YDIfElseConditionVar::tr("判定条件"); }
  virtual QString codeName() const { return "Conditions"; }

 protected:
  virtual QStringList get(YDModule *m) const { return m->getConditionList(); }
  virtual void set(YDModule *m, QStringList list) { m->setConditionList(list); }
};

YDIfElseCondition::YDIfElseCondition()
    : m_widget{new YDModuleIFElseWidget(this)} {
  setPreview(QPixmap(":/Module/IfElse.png"));
  setWidget(m_widget);

  QStringList conditionWay;
  conditionWay << YDIfElseCondition::tr("与运算")
               << YDIfElseCondition::tr("或运算");

  m_properties << new YDIfElseConditionName;
  m_properties << new YDIfElseConditionWay(conditionWay);
  m_properties << new YDIfElseConditionVar;
}

Module::Type YDIfElseCondition::type() const {
  return Module::IfElse_Condition;
}

void YDIfElseCondition::initModule(YDTask *task, uint64 parentId) {
  setTask(task);
  YDProjectManage::createTaskIfElseProcess(task->id(), m_ifElseProcess);
  Q_ASSERT(m_ifElseProcess);
  m_logicProcess = m_ifElseProcess->pProcess;
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  m_ifElseProcess->pConditionModule->logic_operator = LOGIC_OPERATOR_AND;
}

void YDIfElseCondition::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::getIfElseProcess(lp->id, m_ifElseProcess);
  Q_ASSERT(m_ifElseProcess);
  setData();
}

void YDIfElseCondition::getData() {
  Q_ASSERT(m_ifElseProcess->pModule);

  m_ifElseProcess->pModule->listTrueProcessIds.clear();
  m_ifElseProcess->pModule->listFalseProcessIds.clear();

  auto trueIds = m_widget->getTrueProcessIds(getLogicProcessId());
  auto falseIds = m_widget->getFalseProcessIds(getLogicProcessId());

  for (auto id : trueIds)
    m_ifElseProcess->pModule->listTrueProcessIds.push_back(id);
  for (auto id : falseIds)
    m_ifElseProcess->pModule->listFalseProcessIds.push_back(id);
}

void YDIfElseCondition::setData() {
  Q_ASSERT(m_ifElseProcess->pModule);
  auto tlist = m_ifElseProcess->pModule->listTrueProcessIds;
  if (!tlist.empty()) {
    std::vector<yd::lg::LogicProcess *> listTrueProcesses;
    YDProjectManage::getProcesses(getLogicProcessId(), tlist,
                                  listTrueProcesses);
    m_widget->addTrueModules(m_task, listTrueProcesses);
  }

  auto flist = m_ifElseProcess->pModule->listFalseProcessIds;
  if (!flist.empty()) {
    std::vector<yd::lg::LogicProcess *> listFalseProcesses;
    YDProjectManage::getProcesses(getLogicProcessId(), flist,
                                  listFalseProcesses);
    m_widget->addFalseModules(m_task, listFalseProcesses);
  }
}

int YDIfElseCondition::high() const { return m_widget->high(); }

void YDIfElseCondition::setStateMap(
    const QMap<uint32, yd::proto::ProcState> &map) {
  m_widget->setState(map);
}

void YDIfElseCondition::resize() { m_widget->resizeModule(); }
