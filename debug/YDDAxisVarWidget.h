#ifndef YDDAXISVARWIDGET_H
#define YDDAXISVARWIDGET_H

#include <QList>
#include <QMap>
#include <QWidget>

#include "platform.h"
#include "yd_project.h"
#include "yddef.h"

class QTreeWidget;
class YDDAxisVarView;
class YDDAxisVarModel;
class YDDAxisVarDeletegate;
class YDDAxisVarDeletegate2;
class QPushButton;

class YDMoveControlWidget;

union YDVarCast {
  yd::vr::SystemVariable *ptr;
  qintptr i;
};

class YDDAxisVarWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDDAxisVarWidget(QWidget *parent = nullptr);

 public:
  void initTree();
  void updateData();

 signals:

 private slots:
  void slotViewSingleClicked(const QModelIndex &index);
  void slotShowClicked(const QModelIndex &index);
  void slotStartJogMove(const QModelIndex &index);
  void slotStopJogMove(const QModelIndex &index);
  void slotStartDJogMove(const QModelIndex &index);
  void slotStopDJogMove(const QModelIndex &index);
  void slotMoveClicked(const QModelIndex &index);
  void slotUpdateAxis(bool);

 private:
  yd::dev::MCAxisInfo *getAxis(const yd::COORDS &coords, int row);

 private:
  YDMoveControlWidget *m_mcw;
  QTreeWidget *m_tree;
  YDDAxisVarView *m_view;
  YDDAxisVarModel *m_model;
  YDDAxisVarDeletegate *m_deletegate;
  YDDAxisVarDeletegate2 *m_deletegate2;
  QPushButton *m_btn1;
};

#endif  // YDDAXISVARWIDGET_H
