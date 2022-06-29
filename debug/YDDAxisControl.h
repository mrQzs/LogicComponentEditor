#ifndef YDDAXISCONTROL_H
#define YDDAXISCONTROL_H

#include <QDialog>

#include "ProtocolClientImpl.h"
#include "ProtocolImp.h"

class QTreeWidget;
class YDStateWidget;
class YDSpeedSetWidget;
class YDMoveControlWidget;
class YDAXisListView;
class QTreeWidgetItem;
class QLabel;
class YDState;
class QPushButton;

class YDDAxisControl : public QDialog {
  Q_OBJECT
 public:
  YDDAxisControl(QWidget *parent = nullptr);
  ~YDDAxisControl();

 public:
  void updateData();

 private slots:
  void slotTreeDooubleClick(const QModelIndex &index);

 signals:
  void start();
  void stop();
  void updateTime(int);

 private:
  void initUi();
  void initTree();

  void showWidget(int type);

 private:
  QTreeWidget *m_menuTree;
  YDAXisListView *m_view;
  QWidget *m_widget;
  YDStateWidget *m_stateW;
  YDSpeedSetWidget *m_speedSetW;
  YDMoveControlWidget *m_moveconW;

  QTreeWidgetItem *m_smi;
  QTreeWidgetItem *m_ssi;
  QTreeWidgetItem *m_mci;

  int m_type;
};

#endif  // YDDAXISCONTROL_H
