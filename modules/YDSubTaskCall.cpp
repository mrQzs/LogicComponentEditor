#include "YDSubTaskCall.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDSubTaskCallName : public YDPropertyName {
 public:
  QString name() const { return YDSubTaskCallName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDSubTaskCallName::tr("错误"),
                               YDSubTaskCallName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDSubTaskCallName::tr("错误"),
                               YDSubTaskCallName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDSubTaskCallTask : public YDPropertyTask {
 public:
  QString name() const { return YDSubTaskCallTask::tr("选择任务"); }
  QString codeName() const { return "Task"; }

 protected:
  virtual quint32 get(YDModule *m) const { return m->getCallTask(); }
  virtual void set(YDModule *m, quint32 id) { m->setTaskCall(id); }
};

YDSubTaskCall::YDSubTaskCall() {
  setPreview(QPixmap(":/Module/Sub_Task.png"));
  auto w = new YDModuleWidget(this, OtherColor, OtherFColor);

  setWidget(w);

  m_properties << new YDSubTaskCallName;
  m_properties << new YDSubTaskCallTask;
}

Module::Type YDSubTaskCall::type() const { return Module::SubTask_Call; }

void YDSubTaskCall::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachTaskCallerModule(logicProcessId, m_subTaskModule);
  Q_ASSERT(m_subTaskModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDSubTaskCall::tr("任务调用%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDSubTaskCall::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachTaskCallerModule(lp->id, m_subTaskModule);
  Q_ASSERT(m_subTaskModule);
  setData();
}

void YDSubTaskCall::getData() {
  m_logicProcess->type = LOGIC_PROCESS_TASK_CALLER;
  m_subTaskModule->task_id = getCallTask();
}

void YDSubTaskCall::setData() { setTaskCall(m_subTaskModule->task_id); }
