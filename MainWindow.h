#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

#include "yd_project.h"
#include "yddef.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class QMenu;
QT_END_NAMESPACE

class YDTask;
class YDModule;
class YDMenuModel;
class YDMoveModel;
class YDIOModel;
class YDControlModel;
class YDOtherModel;
class YDModulePropModel;
class YDVariableModel;
class YDProjectManage;
class YDTabWidget;
class YDAddVariableDialog;
class YDAddSafeVarDialog;
class YDAddReciVarDialog;
class YDAddTempVarDialog;
class YDCylinderModel;
class YDVariableGroupModel;
class YDSafeVariableModel;
class YDAddDeviceDialog;
class YDAddCylinderDialog;
class YDDeviceSetDialog;
class YDCodeManage;
class YDMenu;
class YDMenuItem;
class YDNetSetDialog;
class YDDebugDialog;
class YDTreeView;
class YDListView;
class YDScriptModel;
class YDScriptPropDialog;
class YDNameDialog;
class YDReciVariableModel;
class YDTempVariableModel;
class YDShowMessage;
class QAciton;
class YDBackPointDialog;
class YDBPCodeManage;
class YDLogThread;
class YDDCylinderWidget;
class YDDInputWidget;
class YDDOutputWidget;
class YDDAxisControl;
class YDTimer;
class YDDVarWidget;
class YDAboutDialog;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public:
  YDModulePropModel *getModPropModel() const;
  void UpdateTabName(YDTask *task);
  QWidget *getView() const;
  void updateList();
  YDShowMessage *getLogWidget() const;

 signals:
  void sigResult(const QString &);
  void sigLog(const QString &);
  void start();
  void stop();
  void updateTime(int);

  void startTiming();
  void stopTiming();
  void updateTiming(int);

 private slots:
  void slotTreeMenu(const QPoint &pos);

  void slotAddTask(bool);

  void slotRemoveTask(bool);

  void slotAddSubTask(bool);

  void slotLoopOne(bool);

  void slotAlwaysLoop(bool);

  void slotEditTaskName(bool);

  void slotVarMenu(const QPoint &pos);

  void slotAddVarGroup(bool);

  void slotRemoveVarGroup(bool);

  void slotAddVarSubGroup(bool);

  void slotEditVarGroupName(bool);

  void slotSafeVarMenu(const QPoint &pos);

  void slotAddSafeVarGroup(bool);

  void slotRemoveSafeVarGroup(bool);

  void slotAddSafeVarSubGroup(bool);

  void slotEditSafeVarGroupName(bool);

  void slotReciVarMenu(const QPoint &pos);

  void slotAddReciVarGroup(bool);

  void slotRemoveReciVarGroup(bool);

  void slotAddReciVarSubGroup(bool);

  void slotEditReciVarGroupName(bool);

  void slotTempVarMenu(const QPoint &pos);

  void slotAddTempVarGroup(bool);

  void slotRemoveTempVarGroup(bool);

  void slotAddTempVarSubGroup(bool);

  void slotEditTempVarGroupName(bool);

  void on_AddVarG_clicked();

  void on_DelVarG_clicked();

  void on_AddSafeVarG_clicked();

  void on_DelSafeVarG_clicked();

  void on_AddVarG_2_clicked();

  void on_DelVarG_2_clicked();

  void on_AddVarG_4_clicked();

  void on_DelVarG_4_clicked();

  void slotTaskItemClick(const QModelIndex &index);

  void slotTaskItemDoubleClick(const QModelIndex &index);

  void addVar(int type, const QStringList &list, yd::vr::SystemVariable *);

  void addReciVar(int type, const QStringList &list, yd::vr::SystemVariable *);

  void on_addVar_clicked();

  void slotAddVarFinished();

  void on_addVar_2_clicked();

  void slotAddReciVarFinished();

  void on_addVar_4_clicked();

  void slotAddTempVarFinished();

  void slotUpdateVar();

  void slotUpdateReciVar();

  void slotUpdateTempVar();

  void on_addSafeVar_clicked();

  void slotAddSafeVarFinished();

  void slotUpdateSafeVar();

  void on_GasAdd_clicked();

  void slotAddCylinderFinished();

  void slotChangeCylinderFinished();

  void slotCylinderItemSingleClick(const QModelIndex &index);

  void slotCylinderItemDoubleClick(const QModelIndex &index);

  void slotVarGroupClick(const QModelIndex &index);

  void slotReciVarGroupClick(const QModelIndex &index);

  void slotTempVarGroupClick(const QModelIndex &index);

  void slotVarGroupDoubleClick(const QModelIndex &);

  void slotVarViewDoubleClick(const QModelIndex &index);

  void slotReciVarViewDoubleClick(const QModelIndex &index);

  void slotTempVarViewDoubleClick(const QModelIndex &index);

  void slotSafeGroupClick(const QModelIndex &index);

  void slotSafeGroupDoubleClick(const QModelIndex &index);

  void slotSafeVarDoubleClick(const QModelIndex &index);

  void slotDeviceSetDlgFinished();

  void slotNetSetFinished();

  void slotDialogFinished();

  void slotCodeDiaFinish();

  void slotCratePFinished();

  void slotChangeNFinished();

  void slotSaveasFinished();

  void slotActionTriggered(bool);

  void slotWayActionTriggered(bool);

  void slotDelActionTriggered(bool);

  void slotDelWayActionTriggered(bool);

  void slotCreateReciFinished();

  void slotChangeReciFinished();

  void slotSaveasReciFinished();

  void slotDebugTrigger(bool);

  void slotBPDialogFinished();

  void slotTabClosed(int);

 private slots:
  // menu
  void showHardConfig();

  void showVarConfig(int);

  void showZeroScript(int);

  void slotScriptMenu(const QPoint &pos);

  void slotAddScript(bool);

  void slotEditScriptProp(bool);

  void slotRemoveScript(bool);

  void slotScriptItemClicked(const QModelIndex &);

  void slotScriptItemDBClicked(const QModelIndex &);

  void slotScriptPropClose();

  void showCusModule(int);

  void slotWidgetAction(bool);

  void showMotionMonitoring(int type);

  //菜单栏

  void on_a_new_triggered();

  void on_a_close_triggered();

  void on_a_rename_triggered();

  void on_a_save_triggered();

  void on_a_saveall_triggered();

  void on_a_saveoth_triggered();

  void on_a_exit_triggered();

  void on_a_newway_triggered();

  void on_a_saveway_triggered();

  void on_a_saveow_triggered();

  void on_a_changeWay_triggered();

  void on_a_dupload_triggered();

  void on_a_ddownload_triggered();

  void on_a_dstartz_triggered();

  void on_a_dstartm_triggered();

  void on_a_dpausem_triggered();

  void on_a_dstopm_triggered();

  void on_a_ttalkset_triggered();

  void on_DelVar_clicked();

  void on_DelSafeVar_clicked();

  void on_DelVa_2_clicked();

  void on_DelVar_4_clicked();

  void on_a_startDebug_triggered();

  void on_a_closeDebug_triggered();

  void on_a_doldebug_triggered(bool checked);

  void on_a_LogicStart_triggered();

  void on_a_LogicStop_triggered();

  void SlotTimingSave();

  void on_a_notSave_triggered();

  void on_a_save5_triggered();

  void on_a_save10_triggered();

  void on_a_save20_triggered();

  void on_a_save30_triggered();

  void on_a_habout_triggered();

 private:
  void initThread();

  void initMenu();

  void initRightMouseMenu();

  void initMenuTree();

  void initModules();

  void initModuleProp();

  void initVariableTable();

  void initCylinderDock();

  void initConnect();

  void initOtherSetting();

  void initOpenMenu();

  void initOpenWayMenu();

  void initReciWidget();

  void initDebugActionEnable(const bool &flag);

 private:
  void updateVarGroupModel();

  void updateSafeVarModel();

  void updateCylinderModels();

  void updateCylinderInfos(yd::dev::Cylinder *cyl, const QStringList &infos);

  QStringList getCylinderInfos(yd::dev::Cylinder *cyl) const;

  void updateProjectName(QString rName = "");

  void updateRecipName();

  bool judgeAxisEnabled();

  bool judgeNetWorkEmpty();

  void updateData();

  void updateTaskData();

  void stopThread();

  void setControlEnabled(bool enable);

  void screenShot();

  void setBtnState(bool b);

  void setSelectTime(int index);

 private:
  Ui::MainWindow *ui;
  QMenu *m_menuR1;
  QMenu *m_menuR3;
  QMenu *m_varRMain;
  QMenu *m_varRsubMenu;
  QMenu *m_safeVRMenu;
  QMenu *m_safeVRsubMenu;
  QMenu *m_reciMenu;
  QMenu *m_reciSubMenu;
  QMenu *m_tempMenu;
  QMenu *m_tempSubMenu;
  QModelIndex m_taskIndex;
  QModelIndex m_deviceIndex;
  QModelIndex m_cylinderIndex;
  QModelIndex m_varIndex;
  QModelIndex m_varViewIndex;
  QModelIndex m_safeVarIndex;
  QModelIndex m_safeVarViewIndex;
  QModelIndex m_reciVarIndex;
  QModelIndex m_reciViewIndex;
  QModelIndex m_tempVarIndex;
  QModelIndex m_tempViewIndex;
  YDMenuModel *m_menuModel;
  YDMoveModel *m_moveModel;
  YDIOModel *m_ioModel;
  YDControlModel *m_controlModel;
  YDOtherModel *m_otherModel;
  YDModulePropModel *m_modulePropModel;
  YDVariableModel *m_variablModel;
  YDCylinderModel *m_cylinderModel;
  YDVariableGroupModel *m_varGroupModel;
  YDSafeVariableModel *m_safeVarModel;
  YDAddVariableDialog *m_addVarDlg;
  YDAddSafeVarDialog *m_addSafeVarDlg;
  YDAddReciVarDialog *m_addReciVarDlg;
  YDAddTempVarDialog *m_addTempVarDlg;
  QAction *m_oneLoop;
  QAction *m_alwaysLoop;
  yd::vr::SafeVariable *m_selectSafeVar;
  YDAddCylinderDialog *m_addCylinderDlg;
  YDDeviceSetDialog *m_deviceSetDlg;

  YDReciVariableModel *m_reciVarModel;
  YDTempVariableModel *m_tempVarModel;

  YDShowMessage *m_logDlg;   //日志信息
  YDShowMessage *m_infoDlg;  //调试信息

  YDAboutDialog *m_aboutDlg;

  yd::COORDS m_coords;

  // debug
  YDNetSetDialog *m_netSetDlg;
  YDDebugDialog *m_debugDlg;

  // code
  YDCodeManage *m_codeManage;

  // menu
  YDMenu *m_hdConfig;

  YDMenu *m_varManage;
  QWidget *m_varManageW;

  YDMenu *m_scriptManage;
  QWidget *m_scriptMangeW;
  YDMenu *m_cusScriptW;
  QWidget *m_scriptViewW;
  YDListView *m_scriptView;
  YDScriptModel *m_scriptModel;
  QModelIndex m_scriptIndex;
  QMenu *m_scriptMenu1;
  QMenu *m_scriptMenu2;
  YDScriptPropDialog *m_scriptProp;
  bool m_scriptSaved;

  YDMenu *m_cusModule;
  QWidget *m_cusModuleW;

  YDMenu *m_moveSystem;
  QWidget *m_moveSysW;
  YDMenu *m_moveLogic;
  YDTreeView *m_logicTree;

  // action
  YDNameDialog *m_createPDlg;
  YDNameDialog *m_changeDlg;
  YDNameDialog *m_saveasDlg;

  QList<QAction *> m_files;
  QList<QAction *> m_ways;
  QList<QAction *> m_delFiles;
  QList<QAction *> m_delWays;

  // recipes
  YDNameDialog *m_createReciDlg;
  YDNameDialog *m_changeReciDlg;
  YDNameDialog *m_saveasReciDlg;
  bool m_isShowReciWidget;

  // backpoint
  YDBackPointDialog *m_backPDlg;
  YDBPCodeManage *m_bpCodeManage;

  //运动监控
  YDDAxisControl *m_axisWidget;
  YDDCylinderWidget *m_cylinderWidget;
  YDDInputWidget *m_inputWidget;
  YDDOutputWidget *m_outputWidget;
  YDDVarWidget *m_varWidget;

  // Logic
  uint32 m_taskId;
  int m_debugWindowType;
  bool m_isLogicTaskStart;

  // timer
  YDTimer *m_timer;
  QThread *m_timerThread;
  YDTimer *m_timingSave;
  QThread *m_timingThread;
};
#endif  // MAINWINDOW_H
