#ifndef YDLOGICDEBUG_H
#define YDLOGICDEBUG_H

#include <QWidget>

class YDTreeView;

class YDLogicDebug : public QWidget {
  Q_OBJECT
 public:
  explicit YDLogicDebug(QWidget* parent = nullptr);

 signals:

 private:
  YDTreeView* m_menuTree;
  QWidget* m_widget;
};

#endif  // YDLOGICDEBUG_H
