#include "YDTabWidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QSpacerItem>

#include "YDModuleListWidget.h"
#include "common/YDGlobal.h"
#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "modules/YDModules.h"

YDTabWidget::YDTabWidget(YDTask *task, QWidget *parent)
    : QWidget{parent},
      m_task{task},
      m_listWidget{new YDModuleListWidget(task, this)} {
  m_listWidget->setTask(task);
  auto hlay = new QHBoxLayout{this};
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_listWidget);
}

YDTabWidget::~YDTabWidget() {}

QList<YDModule *> YDTabWidget::getModules() {
  QList<YDModule *> list;
  for (int i = 0; i < m_listWidget->count(); ++i) {
    auto item = m_listWidget->item(i);
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(item->data(Qt::UserRole));
    list << cast.ptr;
  }
  return list;
}

void YDTabWidget::initModules(YDTask *task,
                              const std::vector<yd::lg::LogicProcess *> &list) {
  for (auto lp : list) {
    if (m_task->id() == lp->parent_id) {
      auto m = YDProjectManage::getModule(lp->type);
      if (m) {
        m->setTask(task);
        m->initModule(lp);
        m_listWidget->addModule(m);
      }
    }
  }
}

void YDTabWidget::setModulesState(std::vector<proto::ProcState> &states) {
  QMap<uint32, yd::proto::ProcState> map;

  for (int i = 0; i < states.size(); ++i) {
    map[states[i].id] = states[i];
    states[i].begin = 0;
    states[i].end = 0;
  }

  auto list = getModules();
  for (auto m : list) {
    auto state = map[m->getLogicProcessId()];
    m->setDebugState(state);
    switch (m->type()) {
      case Module::If_Condition:
      case Module::IfElse_Condition:
      case Module::Condition_Loop:
      case Module::Times_Loop:
        m->setStateMap(map);
        break;
      default:
        break;
    }
  }
}

void YDTabWidget::resizeModel() { YDHelper::resizeModel(m_listWidget); }

YDTask *YDTabWidget::getTask() { return m_task; }
