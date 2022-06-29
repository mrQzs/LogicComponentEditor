#include "YDIfCondition.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDIfConditionWidget.h"
#include "widget/module/YDModuleWidget.h"

class YDIfConditionName : public YDPropertyName {
 public:
  QString name() const { return YDIfConditionName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDIfConditionName::tr("错误"),
                               YDIfConditionName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateIfName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDIfConditionName::tr("错误"),
                               YDIfConditionName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDIfConditionWay : public YDPropertyEnum {
 public:
  YDIfConditionWay(QStringList enumText) : YDPropertyEnum{enumText} {}
  virtual QString name() const { return YDIfConditionWay::tr("逻辑运算符"); }
  virtual QString codeName() const { return "Way"; }

 protected:
  virtual int get(YDModule *m) const { return m->getIfConditionWay(); }
  virtual void set(YDModule *m, int index) { m->setIfConditionWay(index); }
};

class YDIfConditionVar : public YDCustomWProp {
 public:
  YDIfConditionVar() : YDCustomWProp(WidgetType::e_CONDITION) {}
  virtual QString name() const { return YDIfConditionVar::tr("判定条件"); }
  virtual QString codeName() const { return "Conditions"; }

 protected:
  virtual QStringList get(YDModule *m) const { return m->getIfConditionList(); }
  virtual void set(YDModule *m, QStringList list) {
    m->setIfConditionList(list);
  }
};

YDIfCondition::YDIfCondition() : m_widget{new YDIfConditionWidget(this)} {
  setPreview(QPixmap(":/Module/IfCondition.png"));
  setWidget(m_widget);

  QStringList conditionWay;
  conditionWay << YDIfCondition::tr("与运算") << YDIfCondition::tr("或运算");

  m_properties << new YDIfConditionName;
  m_properties << new YDIfConditionWay(conditionWay);
  m_properties << new YDIfConditionVar;
}

Module::Type YDIfCondition::type() const { return Module::If_Condition; }

void YDIfCondition::initModule(YDTask *task, uint64 parentId) {
  setTask(task);
  YDProjectManage::createTaskIfProcess(task->id(), m_ifProcess);
  Q_ASSERT(m_ifProcess);
  m_logicProcess = m_ifProcess->pProcess;
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  m_ifProcess->pConditionModule->logic_operator = LOGIC_OPERATOR_AND;
}

void YDIfCondition::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::getIfProcess(lp->id, m_ifProcess);
  Q_ASSERT(m_ifProcess);
  setData();
}

void YDIfCondition::getData() {
  Q_ASSERT(m_ifProcess->pModule);
  m_ifProcess->pModule->listProcessIds.clear();

  auto trueIds = m_widget->getTrueProcessIds(getLogicProcessId());

  for (auto id : trueIds) m_ifProcess->pModule->listProcessIds.push_back(id);
}

void YDIfCondition::setData() {
  Q_ASSERT(m_ifProcess->pModule);
  auto tlist = m_ifProcess->pModule->listProcessIds;
  if (!tlist.empty()) {
    std::vector<yd::lg::LogicProcess *> listTrueProcesses;
    YDProjectManage::getProcesses(getLogicProcessId(), tlist,
                                  listTrueProcesses);
    m_widget->addTrueModules(m_task, listTrueProcesses);
  }
}

int YDIfCondition::high() const { return m_widget->high(); }

void YDIfCondition::setStateMap(const QMap<uint32, yd::proto::ProcState> &map) {
  m_widget->setState(map);
}

void YDIfCondition::resize() { m_widget->resizeModule(); }
