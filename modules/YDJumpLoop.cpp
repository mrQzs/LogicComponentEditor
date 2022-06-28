#include "YDJumpLoop.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDJumpLoopName : public YDPropertyName {
 public:
  QString name() const { return YDJumpLoopName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDJumpLoopName::tr("错误"),
                               YDJumpLoopName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDJumpLoopName::tr("错误"),
                               YDJumpLoopName::tr("名称已重复!"));
          break;
      }
    }
  }
};

YDJumpLoop::YDJumpLoop() {
  setPreview(QPixmap(":/Module/Jump_Loop.png"));
  auto w = new YDModuleWidget(this, ControlColor, ControlFColor);

  setWidget(w);

  m_properties << new YDJumpLoopName;
}

Module::Type YDJumpLoop::type() const { return Module::Jump_Loop; }

void YDJumpLoop::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachBreakModule(logicProcessId, m_jumpModule);
  Q_ASSERT(m_jumpModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDJumpLoop::tr("跳出循环%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDJumpLoop::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  m_logicProcess = lp;
  YDProjectManage::attachBreakModule(lp->id, m_jumpModule);
  Q_ASSERT(m_jumpModule);
  setData();
}

void YDJumpLoop::getData() { m_logicProcess->type = LOGIC_PROCESS_BREAK; }

void YDJumpLoop::setData() {}

bool YDJumpLoop::isValid() const { return isInLoop(m_logicProcess); }

bool YDJumpLoop::isInLoop(yd::lg::LogicProcess *process) const {
  lg::LogicProcess *p = nullptr;
  YDProjectManage::getProcess(process->parent_id, p);
  if (nullptr == p) return false;
  if (p->type == LOGIC_PROCESS_CONDITION_LOOP ||
      p->type == LOGIC_PROCESS_COUNTER_LOOP) {
    m_jumpModule->near_loopid = p->id;
    return true;
  } else if (p->type == LOGIC_PROCESS_IF_ELSE || p->type == LOGIC_PROCESS_IF) {
    return isInLoop(p);
  }
  return false;
}
