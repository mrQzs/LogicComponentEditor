#ifndef YDDEBUGDIALOG_H
#define YDDEBUGDIALOG_H

#include <QDialog>

#include "ProtocolClientImpl.h"
#include "ProtocolImp.h"

class QTreeWidget;
class YDDInputWidget;
class YDDOutputWidget;
class YDStateWidget;
class YDSpeedSetWidget;
class YDMoveControlWidget;
class YDDAxisVarWidget;
class YDDVariableWidget;
class YDDCylinderWidget;
class YDAXisListView;
class QTreeWidgetItem;
class YDDTaskWidget;
class QLabel;
class YDState;
class QFrame;
class QPushButton;
class QThread;
class YDTimer;
class QLineEdit;

class YDDebugDialog : public QDialog {
  Q_OBJECT
 public:
  YDDebugDialog(QWidget *parent = nullptr);
  ~YDDebugDialog();

 public:
  void stopThread();

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

 private slots:
  void slotStart(bool);
  void slotStop(bool);
  void slotPause(bool);
  void slotResume(bool);
  void slotAuto(bool);
  void slotManu(bool);

  void updateData();
  void updateServer();

  void slotUpdateTime(bool);

 private:
  QTreeWidget *m_menuTree;
  QWidget *m_widget;
  YDAXisListView *m_view;
  YDDInputWidget *m_inputW;
  YDDOutputWidget *m_outputW;
  YDStateWidget *m_stateW;
  YDSpeedSetWidget *m_speedSetW;
  YDMoveControlWidget *m_moveconW;
  YDDVariableWidget *m_varW;
  YDDAxisVarWidget *m_axisVarW;
  YDDCylinderWidget *m_cylinderW;
  YDDTaskWidget *m_taskW;

  QWidget *m_topW;
  QLabel *m_state;
  QLabel *m_state1;
  QPushButton *m_start;
  QPushButton *m_stop;
  QPushButton *m_pause;
  QPushButton *m_resume;
  QLabel *m_timeLab;
  QLineEdit *m_timeEdit;
  QPushButton *m_timeBtn;

  QLabel *m_mode;
  QLabel *m_modeLab;
  QPushButton *m_auto;
  QPushButton *m_manu;
  QFrame *m_line;

  QTreeWidgetItem *m_ini;
  QTreeWidgetItem *m_opi;
  QTreeWidgetItem *m_smi;
  QTreeWidgetItem *m_ssi;
  QTreeWidgetItem *m_mci;
  QTreeWidgetItem *m_nvi;
  QTreeWidgetItem *m_avi;
  QTreeWidgetItem *m_cyi;
  QTreeWidgetItem *m_tvi;

  yd::proto::IProtocolClient *m_pProtocolClient;
  int m_type;

  QThread *m_timerThread;
  YDTimer *m_timer;
  bool m_runing;
  bool m_automode;
};

#endif  // YDDEBUGDIALOG_H
