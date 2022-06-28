#ifndef YDDTASKWIDGET_H
#define YDDTASKWIDGET_H

#include <QModelIndex>
#include <QWidget>

#include "platform.h"
#include "yddef.h"

class YDTreeView;
class YDMenuModel;
class QPushButton;
class QLabel;
class QLineEdit;

class YDDTaskWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDDTaskWidget(QWidget *parent = nullptr);
  ~YDDTaskWidget();

 public:
  void updateDate();

 signals:

 private:
  void slotTaskItemClick(const QModelIndex &index);
  void slotTaskItemDoubleClick(const QModelIndex &index);
  void slotStartClick(bool);
  void slotStopClick(bool);

 private:
  YDTreeView *m_menuView;
  YDMenuModel *m_model;
  QWidget *m_widget;

  QLabel *m_task;
  QLabel *m_taskEdit;
  QPushButton *m_btn1;
  QPushButton *m_btn2;

  uint32 m_id;
};

#endif  // YDDTASKWIDGET_H
