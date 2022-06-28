#ifndef YDTASK_H
#define YDTASK_H

#include <QIcon>
#include <QList>
#include <QString>
#include <QWidget>

#include "YDProjectManage.h"
#include "debug/YDDgHelper.h"

class YDNameLineEdit;
class YDTabWidget;
class YDModule;

class YDTask {
 public:
  YDTask(YDTask* parent = nullptr);

  YDTask(yd::lg::LogicTask* logicTask, YDTask* parent = nullptr);

  YDTask(yd::lg::LogicSubTask* logicSubTask, YDTask* parent = nullptr);

  ~YDTask();

 public:
  // get
  YDTask* parent() const;

  QString name() const;

  QList<YDTask*> childs() const;

  QString Icon() const;

  int childSize() const;

  YDTask* child(int index) const;

  int row() const;

  QWidget* editor(QWidget* parent);

  QWidget* widget() const;

  uint32 id() const;

  QList<YDModule*> getModules() const;

  uint8 getExecuteMethod() const;

  // set
  void setName(const QString& name);

  void setExecuteMethod(uint8 method);

  void setState(const yd::proto::TaskState& state);

  // other
  void initLogicProcess();

  void initChilds(std::vector<yd::lg::LogicSubTask*>& list);

  void initModules();

  void addChild(YDTask* task);

  void delChild(YDTask* task);

  void appendChild(YDTask* pChild);

  void insertChild(int idx, YDTask* pChild);

  void removeChild(YDTask* p);

  void copy(YDTask* task);

  void deleteTask();

  void resizeModel();

  void clear();

 private:
  YDTask* m_parent;
  QList<YDTask*> m_childs;
  YDNameLineEdit* m_widget;
  YDTabWidget* m_tabWidget;
  bool m_isDeleteTask;

 private:
  yd::lg::LogicTask* m_logicTask;
  yd::lg::LogicSubTask* m_logicSubTask;
};

#endif  // YDTASK_H
