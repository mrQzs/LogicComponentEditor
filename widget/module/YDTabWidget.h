#ifndef YDTABWIDGET_H
#define YDTABWIDGET_H

#include <QWidget>

#include "debug/YDDgHelper.h"
#include "yd_project.h"

class YDModuleListWidget;
class YDTask;
class YDModule;

class YDTabWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDTabWidget(YDTask *task, QWidget *parent = nullptr);
  ~YDTabWidget();

 public:
  QList<YDModule *> getModules();

  void initModules(YDTask *task,
                   const std::vector<yd::lg::LogicProcess *> &list);

  void setModulesState(std::vector<yd::proto::ProcState> &states);

  void resizeModel();

 signals:

 private:
  YDTask *m_task;
  YDModuleListWidget *m_listWidget;
};

#endif  // YDTABWIDGET_H
