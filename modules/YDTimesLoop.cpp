#include "YDTimesLoop.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleLoopWidget.h"
#include "widget/module/YDModuleWidget.h"

class YDTimesLoopName : public YDPropertyName {
 public:
  QString name() const { return YDTimesLoopName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDTimesLoopName::tr("错误"),
                               YDTimesLoopName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateLoopName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDTimesLoopName::tr("错误"),
                               YDTimesLoopName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDDelayLoopTimes : public YDPropertyString {
 public:
  YDDelayLoopTimes() : YDPropertyString{1} {}
  QString name() const { return YDDelayLoopTimes::tr("循环次数"); }
  QString codeName() const { return "Times"; }

 protected:
  virtual QString get(YDModule *m) const {
    return QString::number(m->getLoopTimes());
  }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) m->setLoopTimes(str.toUInt());
  }
};

YDTimesLoop::YDTimesLoop() : m_widget{new YDModuleLoopWidget(0, this)} {
  setPreview(QPixmap(":/Module/Count_Loop.png"));
  setWidget(m_widget);

  m_properties << new YDTimesLoopName;
  m_properties << new YDDelayLoopTimes;
}

Module::Type YDTimesLoop::type() const { return Module::Times_Loop; }

void YDTimesLoop::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachCounterLoopModule(logicProcessId, m_timesLoopModule);
  Q_ASSERT(m_timesLoopModule);
  m_timesLoopModule->loop_counter = 0;
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDTimesLoop::tr("次数循环%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDTimesLoop::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachCounterLoopModule(lp->id, m_timesLoopModule);
  Q_ASSERT(m_timesLoopModule);
  setData();
}

void YDTimesLoop::getData() {
  m_logicProcess->type = LOGIC_PROCESS_COUNTER_LOOP;
  m_timesLoopModule->listProcessIds.clear();
  auto loopIds = m_widget->getLoopModulesIds(getLogicProcessId());
  for (auto id : loopIds) m_timesLoopModule->listProcessIds.push_back(id);

  m_timesLoopModule->loop_counter = getLoopTimes();
}

void YDTimesLoop::setData() {
  auto loopIds = m_timesLoopModule->listProcessIds;
  if (!loopIds.empty()) {
    std::vector<yd::lg::LogicProcess *> listProcesses;
    YDProjectManage::getProcesses(getLogicProcessId(), loopIds, listProcesses);
    m_widget->addLoopModules(m_task, listProcesses);
  }

  setLoopTimes(m_timesLoopModule->loop_counter);
}

int YDTimesLoop::high() const { return m_widget->high(); }

void YDTimesLoop::setStateMap(const QMap<uint32, yd::proto::ProcState> &map) {
  m_widget->setState(map);
}

void YDTimesLoop::resize() { m_widget->resizeModel(); }
