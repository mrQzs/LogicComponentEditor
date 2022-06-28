#include "YDTask.h"

#include <QHBoxLayout>

#include "common/YDHelper.h"
#include "widget/YDNameLineEdit.h"
#include "widget/module/YDTabWidget.h"

YDTask::YDTask(YDTask *parent)
    : m_parent{parent},
      m_tabWidget{new YDTabWidget(this)},
      m_isDeleteTask{true},
      m_logicTask{nullptr},
      m_logicSubTask{nullptr} {}

YDTask::YDTask(yd::lg::LogicTask *logicTask, YDTask *parent)
    : m_parent{parent},
      m_tabWidget{new YDTabWidget(this)},
      m_isDeleteTask{true},
      m_logicTask{logicTask},
      m_logicSubTask{nullptr} {}

YDTask::YDTask(yd::lg::LogicSubTask *logicSubTask, YDTask *parent)
    : m_parent{parent},
      m_tabWidget{new YDTabWidget(this)},
      m_isDeleteTask{true},
      m_logicTask{nullptr},
      m_logicSubTask{logicSubTask} {}

YDTask::~YDTask() {
  qDeleteAll(m_childs);
  if (m_tabWidget) delete m_tabWidget;
  if (m_isDeleteTask) deleteTask();
}

YDTask *YDTask::parent() const { return m_parent; }

QString YDTask::name() const {
  if (m_logicTask)
    return QString::fromLocal8Bit(m_logicTask->name.c_str());
  else
    return QString::fromLocal8Bit(m_logicSubTask->name.c_str());
}

QList<YDTask *> YDTask::childs() const { return m_childs; }

QString YDTask::Icon() const {
  if (parent()->parent())
    return QString(":/Icon/subtask.png");
  else
    return QString(":/Icon/task.png");
}

int YDTask::childSize() const { return m_childs.size(); }

YDTask *YDTask::child(int index) const {
  Q_ASSERT(0 <= index && index < m_childs.size());
  return m_childs[index];
}

int YDTask::row() const {
  if (m_parent) return m_parent->childs().indexOf(this);
  return 0;
}

QWidget *YDTask::editor(QWidget *parent) {
  m_widget = new YDNameLineEdit(parent);
  return m_widget;
}

QWidget *YDTask::widget() const { return m_tabWidget; }

uint32 YDTask::id() const {
  if (m_logicTask) return m_logicTask->id;
  return m_logicSubTask->id;
}

QList<YDModule *> YDTask::getModules() const {
  return m_tabWidget->getModules();
}

uint8 YDTask::getExecuteMethod() const {
  if (m_logicTask) return m_logicTask->execute_method;
  return m_logicSubTask->execute_method;
}

void YDTask::setName(const QString &name) {
  if (m_logicTask)
    m_logicTask->name = std::string(name.toLocal8Bit().data());
  else
    m_logicSubTask->name = std::string(name.toLocal8Bit().data());

  YDHelper::UpdateTabName(this);
}

void YDTask::setExecuteMethod(uint8 method) {
  if (m_logicTask)
    m_logicTask->execute_method = method;
  else
    m_logicSubTask->execute_method = method;
}

void YDTask::setState(const yd::proto::TaskState &state) {
  m_tabWidget->setModulesState(state.process_states);
}

void YDTask::initLogicProcess() {
  if (nullptr == m_parent->parent()) {
    YDProjectManage::createTask(m_logicTask);
    Q_ASSERT(m_logicTask);
  } else {
    YDProjectManage::createSubTask(m_parent->id(), m_logicSubTask);
    Q_ASSERT(m_logicSubTask);
  }
}

void YDTask::initChilds(std::vector<yd::lg::LogicSubTask *> &list) {
  for (auto t : list) {
    auto task = new YDTask(t, this);
    task->initModules();
    addChild(task);
  }
}

void YDTask::initModules() {
  std::vector<yd::lg::LogicProcess *> list;
  if (m_logicTask)
    YDProjectManage::getTaskProcesses(m_logicTask->id, list);
  else
    YDProjectManage::getSubTaskProcesses(m_logicSubTask->id, list);

  m_tabWidget->initModules(this, list);
}

void YDTask::addChild(YDTask *task) {
  Q_ASSERT(task);
  m_childs.append(task);
}

void YDTask::delChild(YDTask *task) {
  Q_ASSERT(m_childs.removeOne(task));
  delete task;
  task = nullptr;
}

void YDTask::appendChild(YDTask *pChild) { m_childs.append(pChild); }

void YDTask::insertChild(int idx, YDTask *pChild) {
  m_childs.insert(idx, pChild);
}

void YDTask::removeChild(YDTask *p) {
  int index = m_childs.indexOf(p);
  Q_ASSERT(index >= 0);
  m_childs.removeAt(index);
  delete p;
  p = nullptr;
}

void YDTask::copy(YDTask *task) {
  if (m_tabWidget) delete m_tabWidget;
  m_tabWidget = task->m_tabWidget;
  task->m_tabWidget = nullptr;

  m_logicTask = task->m_logicTask;
  m_logicSubTask = task->m_logicSubTask;
  task->m_isDeleteTask = false;
}

void YDTask::deleteTask() {
  if (m_logicTask) YDProjectManage::deleteTask(m_logicTask->id);
  if (m_logicSubTask)
    YDProjectManage::deleteSubTask(m_parent->id(), m_logicSubTask->id);
}

void YDTask::resizeModel() { m_tabWidget->resizeModel(); }

void YDTask::clear() {
  int size = m_childs.size();
  for (int i = size - 1; i >= 0; --i) removeChild(m_childs[i]);
}
