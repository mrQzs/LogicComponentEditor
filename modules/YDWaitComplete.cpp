#include "YDWaitComplete.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDWaitCompleteName : public YDPropertyName {
 public:
  QString name() const { return YDWaitCompleteName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDWaitCompleteName::tr("错误"),
                               YDWaitCompleteName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDWaitCompleteName::tr("错误"),
                               YDWaitCompleteName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDWaitCompleteTask : public YDPropertyTask {
 public:
  QString name() const { return YDWaitCompleteTask::tr("选择任务"); }
  QString codeName() const { return "Task"; }

 protected:
  virtual quint32 get(YDModule *m) const { return m->getCallTask(); }
  virtual void set(YDModule *m, quint32 id) { m->setTaskCall(id); }
};

YDWaitComplete::YDWaitComplete() {
  setPreview(QPixmap(":/Module/Task_Wait.png"));
  auto w = new YDModuleWidget(this, OtherColor, OtherFColor);

  setWidget(w);

  m_properties << new YDWaitCompleteName;
  m_properties << new YDWaitCompleteTask;
}

Module::Type YDWaitComplete::type() const { return Module::Wait_Complete; }

void YDWaitComplete::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachTaskStateWaitModule(logicProcessId, m_taskWaitModule);
  Q_ASSERT(m_taskWaitModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDWaitComplete::tr("任务等待完成%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDWaitComplete::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachTaskStateWaitModule(lp->id, m_taskWaitModule);
  Q_ASSERT(m_taskWaitModule);
  setData();
}

void YDWaitComplete::getData() {
  m_logicProcess->type = LOGIC_PROCESS_TASK_STATE_WAIT;
  m_taskWaitModule->task_id = getCallTask();
}

void YDWaitComplete::setData() { setTaskCall(m_taskWaitModule->task_id); }
