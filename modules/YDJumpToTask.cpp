#include "YDJumpToTask.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDJumpToTaskName : public YDPropertyName {
 public:
  QString name() const { return YDJumpToTaskName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDJumpToTaskName::tr("错误"),
                               YDJumpToTaskName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDJumpToTaskName::tr("错误"),
                               YDJumpToTaskName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDJumpToTaskModule : public YDPropertyModule {
 public:
  YDJumpToTaskModule(YDModule *m) : YDPropertyModule{m} {}
  QString name() const { return YDJumpToTaskModule::tr("选择控件"); }
  QString codeName() const { return "Module"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSelectModule(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) m->setSelectModule(str);
  }
};

YDJumpToTask::YDJumpToTask() {
  setPreview(QPixmap(":/Module/JumpToTask.png"));
  auto w = new YDModuleWidget(this, OtherColor, OtherFColor);

  setWidget(w);

  m_properties << new YDJumpToTaskName;
  m_properties << new YDJumpToTaskModule(this);
}

Module::Type YDJumpToTask::type() const { return Module::Jump_To_Task; }

void YDJumpToTask::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachJumpToModule(logicProcessId, m_jumpToModule);
  Q_ASSERT(m_jumpToModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDJumpToTask::tr("跳转控件%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDJumpToTask::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  m_logicProcess = lp;
  YDProjectManage::attachJumpToModule(lp->id, m_jumpToModule);
  Q_ASSERT(m_jumpToModule);
  setData();
}

void YDJumpToTask::getData() {
  m_logicProcess->type = LOGIC_PROCESS_JUMP_TO;
  auto tid = getYDTask()->id();
  auto name = getSelectModule();

  auto root = YDProjectManage::getYDTaskRoot();
  auto childs = root->childs();
  for (auto s : childs) {
    if (s->id() == tid) {
      QList<YDModule *> modules = s->getModules();
      for (auto m : modules) {
        if (name == m->name()) {
          m_jumpToModule->process_id = m->getLogicProcessId();
          break;
        }
      }
      break;
    }
  }
}

void YDJumpToTask::setData() {
  auto map = YDProjectManage::getProcessNames();
  if (0 != m_jumpToModule->process_id) {
    std::string name = map.at(m_jumpToModule->process_id);
    setSelectModule(STRTQSTR(name.c_str()));
  }
}
