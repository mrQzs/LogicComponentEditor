#include "MainWindow.h"

#include <QAbstractItemView>
#include <QAction>
#include <QDateTime>
#include <QDebug>
#include <QHeaderView>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QStandardItemModel>
#include <QThread>
#include <QTreeView>
#include <QVBoxLayout>

#include "RapidJsonHelper.h"
#include "common/YDHelper.h"
#include "common/YDLogThread.h"
#include "common/YDLogger.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "core/YDVariable.h"
#include "core/thread/YDThreads.h"
#include "debug/YDDAxisControl.h"
#include "debug/YDDCylinderWidget.h"
#include "debug/YDDInputWidget.h"
#include "debug/YDDOutputWidget.h"
#include "debug/YDDVarWidget.h"
#include "debug/YDDebugDialog.h"
#include "debug/YDDgHelper.h"
#include "debug/YDNetSetDialog.h"
#include "model/YDControlModel.h"
#include "model/YDCylinderModel.h"
#include "model/YDIOModel.h"
#include "model/YDMenuModel.h"
#include "model/YDModulePropModel.h"
#include "model/YDMoveModel.h"
#include "model/YDOtherModel.h"
#include "model/YDReciVariableModel.h"
#include "model/YDSafeVariableModel.h"
#include "model/YDScriptModel.h"
#include "model/YDTempVariableModel.h"
#include "model/YDVariableGroupModel.h"
#include "model/YDVariableModel.h"
#include "modules/YDModules.h"
#include "ui_MainWindow.h"
#include "view/YDListView.h"
#include "view/YDTreeView.h"
#include "widget/YDAboutDialog.h"
#include "widget/YDBPCodeManage.h"
#include "widget/YDBackPointDialog.h"
#include "widget/YDCodeManage.h"
#include "widget/YDDeviceSetDialog.h"
#include "widget/YDMenu.h"
#include "widget/YDMenuHead.h"
#include "widget/YDMenuItem.h"
#include "widget/YDNameDialog.h"
#include "widget/YDScriptPropDialog.h"
#include "widget/YDShowMessage.h"
#include "widget/base/YDDockWidget.h"
#include "widget/module/YDTabWidget.h"
#include "widget/property/YDAddCylinderDialog.h"
#include "widget/property/YDAddDeviceDialog.h"
#include "widget/property/YDAddReciVarDialog.h"
#include "widget/property/YDAddSafeVarDialog.h"
#include "widget/property/YDAddTempVarDialog.h"
#include "widget/property/YDAddVariableDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
      ui{new Ui::MainWindow},
      m_menuR1{new QMenu(this)},
      m_menuR3{new QMenu(this)},
      m_varRMain{new QMenu(this)},
      m_varRsubMenu{new QMenu(this)},
      m_safeVRMenu{new QMenu(this)},
      m_safeVRsubMenu{new QMenu(this)},
      m_reciMenu{new QMenu(this)},
      m_reciSubMenu{new QMenu(this)},
      m_tempMenu{new QMenu(this)},
      m_tempSubMenu{new QMenu(this)},
      m_moveModel{new YDMoveModel(this)},
      m_ioModel{new YDIOModel(this)},
      m_controlModel{new YDControlModel(this)},
      m_otherModel{new YDOtherModel(this)},
      m_modulePropModel{new YDModulePropModel(this)},
      m_variablModel{new YDVariableModel(this)},
      m_cylinderModel{new YDCylinderModel(this)},
      m_safeVarModel{new YDSafeVariableModel(this)},
      m_addVarDlg{nullptr},
      m_addSafeVarDlg{nullptr},
      m_addReciVarDlg{nullptr},
      m_addTempVarDlg{nullptr},
      m_selectSafeVar{nullptr},
      m_addCylinderDlg{nullptr},
      m_deviceSetDlg{new YDDeviceSetDialog(this)},
      m_reciVarModel{new YDReciVariableModel(this)},
      m_tempVarModel{new YDTempVariableModel(this)},
      m_netSetDlg{new YDNetSetDialog(this)},
      m_debugDlg{nullptr},
      m_codeManage{new YDCodeManage(this)},
      m_hdConfig{new YDMenu(this)},
      m_varManage{new YDMenu(this)},
      m_varManageW{new QWidget(this)},
      m_scriptManage{new YDMenu(this)},
      m_scriptMangeW{new QWidget(this)},
      m_cusScriptW{new YDMenu(m_scriptMangeW)},
      m_scriptViewW{new QWidget(m_cusScriptW)},
      m_scriptView{new YDListView(m_scriptViewW)},
      m_scriptModel{new YDScriptModel(m_scriptViewW)},
      m_scriptMenu1{new QMenu(m_scriptViewW)},
      m_scriptMenu2{new QMenu(m_scriptViewW)},
      m_scriptProp{new YDScriptPropDialog(this)},
      m_scriptSaved{false},
      m_cusModule{new YDMenu(this)},
      m_cusModuleW{new QWidget(this)},
      m_moveSystem{new YDMenu(this)},
      m_moveSysW{new QWidget(this)},
      m_moveLogic{new YDMenu(this)},
      m_logicTree{new YDTreeView(this)},
      m_createPDlg{new YDNameDialog(this)},
      m_changeDlg{new YDNameDialog(this)},
      m_saveasDlg{new YDNameDialog(this)},
      m_createReciDlg{new YDNameDialog(this)},
      m_changeReciDlg{new YDNameDialog(this)},
      m_saveasReciDlg{new YDNameDialog(this)},
      m_isShowReciWidget{false},
      m_logDlg{new YDShowMessage(this)},
      m_infoDlg{new YDShowMessage(this)},
      m_aboutDlg{new YDAboutDialog(this)},
      m_backPDlg{new YDBackPointDialog(this)},
      m_bpCodeManage{new YDBPCodeManage(this)},
      m_axisWidget{nullptr},
      m_cylinderWidget{nullptr},
      m_inputWidget{nullptr},
      m_outputWidget{nullptr},
      m_varWidget{nullptr},
      m_taskId{0},
      m_debugWindowType{-1},
      m_isLogicTaskStart{false},
      m_timer{new YDTimer},
      m_timerThread{new QThread},
      m_timingSave{new YDTimer},
      m_timingThread{new QThread},
      m_taskTimer{new YDTaskState},
      m_taskThread{new QThread},
      m_curTabIndex{-1},
      m_logicStart{new QPushButton},
      m_logicStop{new QPushButton},
      m_closeWidget{new QPushButton} {
  ui->setupUi(this);

  m_menuModel = new YDMenuModel(YDProjectManage::getYDTaskRoot(), this);
  m_varGroupModel =
      new YDVariableGroupModel(YDProjectManage::getVarRoot(), this);
  m_tabButton = new QWidget(ui->tabWidget->tabBar());

  YDHelper::setMainW(this);
  initThread();
  initMenu();
  initRightMouseMenu();
  initMenuTree();
  initModules();
  initModuleProp();
  initVariableTable();
  initCylinderDock();
  initConnect();
  initOtherSetting();
  initOpenMenu();
  initOpenWayMenu();
}

MainWindow::~MainWindow() {
  emit stopTask();
  m_taskThread->requestInterruption();
  m_taskThread->exit(0);
  m_taskThread->wait();
  delete m_taskTimer;
  delete m_taskThread;

  emit stop();
  m_timerThread->requestInterruption();
  m_timerThread->exit(0);
  m_timerThread->wait();
  delete m_timer;
  delete m_timerThread;

  emit stopTiming();
  m_timingThread->requestInterruption();
  m_timingThread->exit(0);
  m_timingThread->wait();
  delete m_timingSave;
  delete m_timingThread;

  delete ui;
  delete YDProjectManage::getYDTaskRoot();
  delete YDProjectManage::getVarRoot();
}

YDModulePropModel *MainWindow::getModPropModel() const {
  ui->PropertyDock->raise();
  return m_modulePropModel;
}

void MainWindow::UpdateTabName(YDTask *task) {
  auto taskW = task->widget();
  auto tabw = ui->tabWidget;

  for (int i = 0; i < tabw->count(); ++i) {
    auto w = tabw->widget(i);
    if (taskW == w) tabw->setTabText(i, task->name());
  }
}

QWidget *MainWindow::getView() const { return ui->tabWidget; }

void MainWindow::updateList() {
  auto w = ui->tabWidget->currentWidget();
  w->update();
}

YDShowMessage *MainWindow::getLogWidget() const { return m_logDlg; }

void MainWindow::slotTreeMenu(const QPoint &pos) {
  QModelIndex curIndex = m_logicTree->indexAt(pos);
  const YDTask *o = reinterpret_cast<YDTask *>(curIndex.internalPointer());
  if (nullptr == o)
    m_menuR1->exec(QCursor::pos());
  else {
    m_taskIndex = curIndex;
    if (o->parent() == YDProjectManage::getYDTaskRoot()) {
      m_menuR3->removeAction(m_oneLoop);
      m_menuR3->removeAction(m_alwaysLoop);
      m_menuR3->addAction(m_oneLoop);
      m_menuR3->addAction(m_alwaysLoop);
      if (LOGIC_EXECUTE_METHOD_ONCE == o->getExecuteMethod()) {
        m_oneLoop->setIcon(QIcon(":/Icon/SelectLoop.bmp"));
        m_alwaysLoop->setIcon(QIcon(":/Icon/UnselectLoop.bmp"));
      } else {
        m_oneLoop->setIcon(QIcon(":/Icon/UnselectLoop.bmp"));
        m_alwaysLoop->setIcon(QIcon(":/Icon/SelectLoop.bmp"));
      }
    } else {
      m_menuR3->removeAction(m_oneLoop);
      m_menuR3->removeAction(m_alwaysLoop);
    }

    m_menuR3->exec(QCursor::pos());
  }
}

void MainWindow::slotAddTask(bool) {
  int row = m_menuModel->rowCount(QModelIndex());
  m_taskIndex = m_menuModel->index(row, 0, QModelIndex());
  m_menuModel->addTree(m_taskIndex);
  m_logicTree->expand(m_taskIndex);
}

void MainWindow::slotRemoveTask(bool) {
  auto rb = QMessageBox::information(
      this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
      MainWindow::tr("确认"), MainWindow::tr("取消"));

  if (0 == rb) {
    if (selectModule &&
        selectModule->getYDTask()->name() ==
            m_menuModel->data(m_taskIndex, Qt::DisplayRole).toString()) {
      selectModule = nullptr;
    }

    m_menuModel->removeTree(m_taskIndex);
    m_taskIndex = QModelIndex();
    m_logicTree->setCurrentIndex(m_taskIndex);
  }
}

void MainWindow::slotAddSubTask(bool) {
  m_menuModel->addTree(m_taskIndex);
  m_logicTree->expand(m_taskIndex);
}

void MainWindow::slotLoopOne(bool) {
  if (m_taskIndex.isValid()) {
    YDTask *o = reinterpret_cast<YDTask *>(m_taskIndex.internalPointer());
    o->setExecuteMethod(LOGIC_EXECUTE_METHOD_ONCE);
  }
}

void MainWindow::slotAlwaysLoop(bool) {
  if (m_taskIndex.isValid()) {
    YDTask *o = reinterpret_cast<YDTask *>(m_taskIndex.internalPointer());
    o->setExecuteMethod(LOGIC_EXECUTE_METHOD_LOOP);
  }
}

void MainWindow::slotEditTaskName(bool) { m_logicTree->setEdit(m_taskIndex); }

void MainWindow::slotVarMenu(const QPoint &pos) {
  QModelIndex curIndex = ui->VarGroupView->indexAt(pos);
  const YDVariable *o =
      reinterpret_cast<YDVariable *>(curIndex.internalPointer());
  if (nullptr == o)
    m_varRMain->exec(QCursor::pos());
  else {
    m_varIndex = curIndex;
    m_varRsubMenu->exec(QCursor::pos());
  }
}

void MainWindow::slotAddVarGroup(bool) {
  int row = m_varGroupModel->rowCount(QModelIndex());
  m_varIndex = m_varGroupModel->index(row, 0, QModelIndex());
  m_varGroupModel->addTree(m_varIndex);
  ui->VarGroupView->expand(m_varIndex);
}

void MainWindow::slotRemoveVarGroup(bool) { on_DelVarG_clicked(); }

void MainWindow::slotAddVarSubGroup(bool) {
  m_varGroupModel->addTree(m_varIndex);
  ui->VarGroupView->expand(m_varIndex);
}

void MainWindow::slotEditVarGroupName(bool) {
  ui->VarGroupView->setEdit(m_varIndex);
}

void MainWindow::slotSafeVarMenu(const QPoint &pos) {
  QModelIndex curIndex = ui->SafeGroupView->indexAt(pos);
  const YDVariable *o =
      reinterpret_cast<YDVariable *>(curIndex.internalPointer());
  if (nullptr == o)
    m_safeVRMenu->exec(QCursor::pos());
  else {
    m_safeVarIndex = curIndex;
    m_safeVRsubMenu->exec(QCursor::pos());
  }
}

void MainWindow::slotAddSafeVarGroup(bool) {
  int row = m_varGroupModel->rowCount(QModelIndex());
  m_safeVarIndex = m_varGroupModel->index(row, 0, QModelIndex());
  m_varGroupModel->addTree(m_safeVarIndex);
  ui->SafeGroupView->expand(m_safeVarIndex);
}

void MainWindow::slotRemoveSafeVarGroup(bool) { on_DelSafeVarG_clicked(); }

void MainWindow::slotAddSafeVarSubGroup(bool) {
  m_varGroupModel->addTree(m_safeVarIndex);
  ui->SafeGroupView->expand(m_safeVarIndex);
}

void MainWindow::slotEditSafeVarGroupName(bool) {
  ui->SafeGroupView->setEdit(m_safeVarIndex);
}

void MainWindow::slotReciVarMenu(const QPoint &pos) {
  QModelIndex curIndex = ui->VarGroupView_2->indexAt(pos);
  const YDVariable *o =
      reinterpret_cast<YDVariable *>(curIndex.internalPointer());
  if (nullptr == o)
    m_reciMenu->exec(QCursor::pos());
  else {
    m_reciVarIndex = curIndex;
    m_reciSubMenu->exec(QCursor::pos());
  }
}

void MainWindow::slotAddReciVarGroup(bool) {
  int row = m_varGroupModel->rowCount(QModelIndex());
  m_reciVarIndex = m_varGroupModel->index(row, 0, QModelIndex());
  m_varGroupModel->addTree(m_reciVarIndex);
  ui->VarGroupView_2->expand(m_reciVarIndex);
}

void MainWindow::slotRemoveReciVarGroup(bool) { on_DelVarG_2_clicked(); }

void MainWindow::slotAddReciVarSubGroup(bool) {
  m_varGroupModel->addTree(m_reciVarIndex);
  ui->VarGroupView_2->expand(m_reciVarIndex);
}

void MainWindow::slotEditReciVarGroupName(bool) {
  ui->VarGroupView_2->setEdit(m_reciVarIndex);
}

void MainWindow::slotTempVarMenu(const QPoint &pos) {
  QModelIndex curIndex = ui->VarGroupView_4->indexAt(pos);
  const YDVariable *o =
      reinterpret_cast<YDVariable *>(curIndex.internalPointer());
  if (nullptr == o)
    m_tempMenu->exec(QCursor::pos());
  else {
    m_tempVarIndex = curIndex;
    m_tempSubMenu->exec(QCursor::pos());
  }
}

void MainWindow::slotAddTempVarGroup(bool) {
  int row = m_varGroupModel->rowCount(QModelIndex());
  m_tempVarIndex = m_varGroupModel->index(row, 0, QModelIndex());
  m_varGroupModel->addTree(m_tempVarIndex);
  ui->VarGroupView_4->expand(m_tempVarIndex);
}

void MainWindow::slotRemoveTempVarGroup(bool) { on_DelVarG_4_clicked(); }

void MainWindow::slotAddTempVarSubGroup(bool) {
  m_varGroupModel->addTree(m_tempVarIndex);
  ui->VarGroupView_4->expand(m_tempVarIndex);
}

void MainWindow::slotEditTempVarGroupName(bool) {
  ui->VarGroupView_4->setEdit(m_tempVarIndex);
}

void MainWindow::on_AddVarG_clicked() {
  m_varGroupModel->addTree(m_varIndex);
  ui->VarGroupView->expand(m_varIndex);
}

void MainWindow::on_DelVarG_clicked() {
  if (m_varIndex.isValid()) {
    auto rb = QMessageBox::information(
        this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
        MainWindow::tr("确认"), MainWindow::tr("取消"));
    if (0 == rb) {
      m_varGroupModel->removeTree(m_varIndex);
      m_varIndex = QModelIndex();
      ui->VarGroupView->setCurrentIndex(m_varIndex);
      m_variablModel->setGroupId(0);
    }
  } else {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("请选择要删除的分组!"));
  }
}

void MainWindow::on_AddSafeVarG_clicked() {
  m_varGroupModel->addTree(m_safeVarIndex);
  ui->SafeGroupView->expand(m_safeVarIndex);
}

void MainWindow::on_DelSafeVarG_clicked() {
  if (m_safeVarIndex.isValid()) {
    auto rb = QMessageBox::information(
        this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
        MainWindow::tr("确认"), MainWindow::tr("取消"));
    if (0 == rb) {
      m_varGroupModel->removeTree(m_safeVarIndex);
      m_safeVarIndex = QModelIndex();
      ui->SafeGroupView->setCurrentIndex(m_safeVarIndex);
      m_safeVarModel->setGroupId(0);
    }
  } else {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("请选择要删除的分组!"));
  }
}

void MainWindow::on_AddVarG_2_clicked() {
  m_varGroupModel->addTree(m_reciVarIndex);
  ui->VarGroupView_2->expand(m_reciVarIndex);
}

void MainWindow::on_DelVarG_2_clicked() {
  if (m_reciVarIndex.isValid()) {
    auto rb = QMessageBox::information(
        this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
        MainWindow::tr("确认"), MainWindow::tr("取消"));
    if (0 == rb) {
      m_varGroupModel->removeTree(m_reciVarIndex);
      m_reciVarIndex = QModelIndex();
      ui->VarGroupView_2->setCurrentIndex(m_reciVarIndex);
      m_reciVarModel->setGroupId(0);
    }
  } else {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("请选择要删除的分组!"));
  }
}

void MainWindow::on_AddVarG_4_clicked() {
  m_varGroupModel->addTree(m_tempVarIndex);
  ui->VarGroupView_4->expand(m_tempVarIndex);
}

void MainWindow::on_DelVarG_4_clicked() {
  if (m_tempVarIndex.isValid()) {
    auto rb = QMessageBox::information(
        this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
        MainWindow::tr("确认"), MainWindow::tr("取消"));
    if (0 == rb) {
      m_varGroupModel->removeTree(m_tempVarIndex);
      m_tempVarIndex = QModelIndex();
      ui->VarGroupView_4->setCurrentIndex(m_tempVarIndex);
      m_tempVarModel->setGroupId(0);
    }
  } else {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("请选择要删除的分组!"));
  }
}

void MainWindow::slotTaskItemClick(const QModelIndex &index) {
  m_taskIndex = index;
}

void MainWindow::slotTaskItemDoubleClick(const QModelIndex &index) {
  if (!YDHelper::getTestStart()) {
    YDTask *o = reinterpret_cast<YDTask *>(index.internalPointer());
    auto tabW = ui->tabWidget;
    auto name = o->name();
    QWidget *w = o->widget();

    for (int i = 0; i < tabW->count(); ++i) {
      if (tabW->widget(i) == w) {
        tabW->setCurrentIndex(i);
        return;
      }
    }

    auto idx = tabW->addTab(w, name);
    tabW->setCurrentIndex(idx);
  }
}

void MainWindow::initThread() {
  m_timer->moveToThread(m_timerThread);
  QObject::connect(m_timer, &YDTimer::timeout, this, &MainWindow::updateData);
  QObject::connect(this, &MainWindow::start, m_timer, &YDTimer::startrun);
  QObject::connect(this, &MainWindow::stop, m_timer, &YDTimer::stop);
  QObject::connect(this, &MainWindow::updateTime, m_timer, &YDTimer::setTime);

  m_timerThread->start();

  m_timingSave->moveToThread(m_timingThread);
  QObject::connect(m_timingSave, &YDTimer::timeout, this,
                   &MainWindow::SlotTimingSave);
  QObject::connect(this, &MainWindow::startTiming, m_timingSave,
                   &YDTimer::startrun);
  QObject::connect(this, &MainWindow::stopTiming, m_timingSave, &YDTimer::stop);
  QObject::connect(this, &MainWindow::updateTiming, m_timingSave,
                   &YDTimer::setTime);
  m_timingThread->start();

  m_taskTimer->moveToThread(m_taskThread);
  QObject::connect(m_taskTimer, &YDTaskState::sigTransState, this,
                   &MainWindow::SlotTaskState);
  QObject::connect(this, &MainWindow::startTask, m_taskTimer,
                   &YDTaskState::startrun);
  QObject::connect(this, &MainWindow::stopTask, m_taskTimer,
                   &YDTaskState::stop);
  QObject::connect(this, &MainWindow::updateTask, m_taskTimer,
                   &YDTaskState::setTime);
  m_taskThread->start();
}

void MainWindow::initMenu() {
  m_hdConfig->setText(MainWindow::tr("硬件配置"));
  m_varManage->setText(MainWindow::tr("变量管理"));
  m_scriptManage->setText(MainWindow::tr("脚本管理"));
  m_cusModule->setText(MainWindow::tr("自定义组件"));
  m_moveSystem->setText(MainWindow::tr("运动监控"));
  m_moveLogic->setText(MainWindow::tr("动作逻辑编程"));

  m_hdConfig->setIcon(":/Icon/Device.png");
  m_varManage->setIcon(":/Icon/Variable.png");
  m_scriptManage->setIcon(":/Icon/edit.png");
  m_cusModule->setIcon(":/Icon/VarManage.png");
  m_moveSystem->setIcon(":/Icon/MoveView.png");
  m_moveLogic->setIcon(":/Icon/Code.png");

  auto vlout = new QVBoxLayout(ui->scroa);
  vlout->setContentsMargins(0, 0, 0, 0);
  vlout->setSpacing(2);
  vlout->addWidget(m_hdConfig);
  vlout->addWidget(m_varManage);
  vlout->addWidget(m_scriptManage);
  vlout->addWidget(m_cusModule);
  vlout->addWidget(m_moveSystem);
  vlout->addWidget(m_moveLogic);
  vlout->addStretch();

  connect(m_hdConfig, &YDMenu::sigClicked, this, &MainWindow::showHardConfig);

  auto vlay2 = new QVBoxLayout(m_varManageW);
  vlay2->setContentsMargins(0, 0, 0, 0);
  vlay2->setSpacing(0);

  QStringList m_varlist;
  m_varlist << MainWindow::tr("全局变量") << MainWindow::tr("配方变量")
            << MainWindow::tr("临时变量") << MainWindow::tr("安全变量");

  for (int i = 0; i < m_varlist.size(); ++i) {
    auto item = new YDMenuItem(i, m_varManageW);
    item->setText(m_varlist[i]);
    item->setIcon(":/Icon/Bianliang.png");
    vlay2->addWidget(item);
    connect(item, &YDMenuItem::sigClicked, this, &MainWindow::showVarConfig);
  }
  vlay2->addSpacing(15);
  m_varManage->setWidget(m_varManageW);

  auto vlay3 = new QVBoxLayout(m_scriptMangeW);
  vlay3->setContentsMargins(0, 0, 0, 0);
  vlay3->setSpacing(0);

  QStringList m_scriptlist;
  m_scriptlist << MainWindow::tr("回原点脚本");

  for (int i = 0; i < m_scriptlist.size(); ++i) {
    auto item = new YDMenuItem(i, m_scriptMangeW);
    item->setText(m_scriptlist[i]);
    item->setIcon(":/Icon/Jiaoben.png");
    vlay3->addWidget(item);
    connect(item, &YDMenuItem::sigClicked, this, &MainWindow::showZeroScript);
  }

  m_scriptViewW->setObjectName("ScriptView");
  m_scriptViewW->setStyleSheet("QWidget#ScriptView{background:white;}");
  auto hlay3 = new QHBoxLayout(m_scriptViewW);
  hlay3->setContentsMargins(0, 0, 0, 0);
  hlay3->setSpacing(0);
  hlay3->addSpacing(26);
  hlay3->addWidget(m_scriptView);

  m_cusScriptW->setIcon(":/Icon/Jiaoben.png");
  m_cusScriptW->setWidget(m_scriptViewW);
  m_cusScriptW->setItemModel(true);
  vlay3->addWidget(m_cusScriptW);
  vlay3->addSpacing(15);
  m_scriptManage->setWidget(m_scriptMangeW);

  auto vlay4 = new QVBoxLayout(m_cusModuleW);
  vlay4->setContentsMargins(0, 0, 0, 0);
  vlay4->setSpacing(0);

  QStringList modulelist;
  modulelist << MainWindow::tr("气油缸") << MainWindow::tr("飞达")
             << MainWindow::tr("Tray盒") << MainWindow::tr("弹夹");

  for (int i = 0; i < modulelist.size(); ++i) {
    auto item = new YDMenuItem(i, m_cusModuleW);
    item->setText(modulelist[i]);
    item->setIcon(":/Icon/Zujian.png");
    vlay4->addWidget(item);
    connect(item, &YDMenuItem::sigClicked, this, &MainWindow::showCusModule);
  }
  vlay4->addSpacing(15);
  m_cusModule->setWidget(m_cusModuleW);

  auto vlay5 = new QVBoxLayout(m_moveSysW);
  vlay5->setContentsMargins(0, 0, 0, 0);
  vlay5->setSpacing(0);

  QStringList watchlist;
  watchlist << MainWindow::tr("轴控制") << MainWindow::tr("气油缸控制")
            << MainWindow::tr("输入状态") << MainWindow::tr("输出状态")
            << MainWindow::tr("变量监测");

  for (int i = 0; i < watchlist.size(); ++i) {
    auto item = new YDMenuItem(i, m_moveSysW);
    item->setText(watchlist[i]);
    item->setIcon(":/Icon/Jiankong.png");
    item->setDebug(true);
    vlay5->addWidget(item);
    connect(item, &YDMenuItem::sigClicked, this,
            &MainWindow::showMotionMonitoring);
  }
  vlay5->addSpacing(15);

  m_moveSystem->setWidget(m_moveSysW);
  m_moveLogic->setWidget(m_logicTree);

  QVBoxLayout *logLayout = new QVBoxLayout(ui->widget_2);
  logLayout->setSpacing(0);
  logLayout->setContentsMargins(2, 0, 4, 1);
  logLayout->addWidget(m_logDlg);

  QVBoxLayout *debugLayout = new QVBoxLayout(ui->dockWidgetContents_5);
  debugLayout->setSpacing(0);
  debugLayout->setContentsMargins(2, 0, 4, 1);
  debugLayout->addWidget(m_infoDlg);

  ui->a_wpromg->setChecked(true);
  ui->a_property->setChecked(true);
  ui->a_wgbvar->setChecked(true);
  ui->a_wwyvar->setChecked(true);
  ui->a_wtpvar->setChecked(true);
  ui->a_wsfvar->setChecked(true);
  ui->a_wcylinder->setChecked(true);
  ui->a_wfeida->setChecked(true);
  ui->a_wtrayp->setChecked(true);
  ui->a_wdanjia->setChecked(true);
  ui->a_logOut->setChecked(true);
  ui->a_debugInfo->setChecked(true);

  if (YDProjectManage::IsOnlineDebugOpened()) {
    ui->a_doldebug->setChecked(true);
    ui->a_startDebug->setEnabled(false);
    ui->a_closeDebug->setEnabled(true);
    initDebugActionEnable(true);
  } else {
    ui->a_doldebug->setChecked(false);
    ui->a_startDebug->setEnabled(true);
    ui->a_closeDebug->setEnabled(false);
    initDebugActionEnable(false);
  }

  QHBoxLayout *tabLayout = new QHBoxLayout(m_tabButton);

  m_logicStart->setStyleSheet(
      "QPushButton{width:20px; height:20px; image: "
      "url(:/Icon/start2.png);border:none;}"
      "QPushButton:hover {background-color:rgba(20,20,20,20)}"
      "QPushButton:disabled {image: url(:/Icon/start1.png)}");
  m_logicStop->setStyleSheet(
      "QPushButton{width:20px; height:20px; image: "
      "url(:/Icon/stop2.png);border:none;}"
      "QPushButton:hover {background-color:rgba(20,20,20,20)}"
      "QPushButton:disabled {image: url(:/Icon/stop1.png)}");
  m_closeWidget->setStyleSheet(
      "QPushButton{width:20px; height:20px; image: "
      "url(:/Icon/close1.png);border:none;} "
      "QPushButton:hover {image: url(:/Icon/close2.png)}");

  m_logicStart->setToolTip(MainWindow::tr("逻辑任务启动"));
  m_logicStop->setToolTip(MainWindow::tr("逻辑任务停止"));
  m_closeWidget->setToolTip(MainWindow::tr("关闭Tab"));

  tabLayout->setSpacing(0);
  tabLayout->setContentsMargins(0, 0, 0, 0);
  tabLayout->addWidget(m_logicStart);
  tabLayout->addWidget(m_logicStop);
  tabLayout->addWidget(m_closeWidget);
  connect(m_logicStart, &QPushButton::clicked, this,
          &MainWindow::on_a_LogicStart_triggered);
  connect(m_logicStop, &QPushButton::clicked, this,
          &MainWindow::on_a_LogicStop_triggered);
  connect(m_closeWidget, &QPushButton::clicked, this,
          &MainWindow::slotTabClosed);

  ui->a_ecopy->setEnabled(false);  //菜单栏编辑 功能缺失
  ui->a_ecut->setEnabled(false);
  ui->e_epaste->setEnabled(false);
  ui->a_edel->setEnabled(false);
  ui->a_eprop->setEnabled(false);

  connect(ui->a_wpromg, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_property, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_wgbvar, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_wwyvar, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_wtpvar, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_wsfvar, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_wcylinder, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_wfeida, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_wtrayp, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_wdanjia, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_logOut, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);
  connect(ui->a_debugInfo, &QAction::triggered, this,
          &MainWindow::slotWidgetAction);

  connect(ui->a_doldebug, &QAction::triggered, this,
          &MainWindow::slotDebugTrigger);
}

void MainWindow::initRightMouseMenu() {
  m_menuR1->addAction(QIcon(":/Icon/add.png"), MainWindow::tr("新建任务"), this,
                      SLOT(slotAddTask(bool)));

  m_menuR3->addAction(QIcon(":/Icon/add.png"), MainWindow::tr("新建子任务"),
                      this, SLOT(slotAddSubTask(bool)));
  m_menuR3->addAction(QIcon(":/Icon/delete.png"), MainWindow::tr("删除任务"),
                      this, SLOT(slotRemoveTask(bool)));
  m_menuR3->addAction(QIcon(":/Icon/edit.png"), MainWindow::tr("修改名字"),
                      this, SLOT(slotEditTaskName(bool)));
  m_oneLoop = m_menuR3->addAction(QIcon(":/Icon/SelectLoop.bmp"),
                                  MainWindow::tr("执行一次"), this,
                                  SLOT(slotLoopOne(bool)));
  m_alwaysLoop = m_menuR3->addAction(QIcon(":/Icon/UnselectLoop.bmp"),
                                     MainWindow::tr("一直循环"), this,
                                     SLOT(slotAlwaysLoop(bool)));

  m_varRMain->addAction(QIcon(":/Icon/add.png"),
                        MainWindow::tr("新建一级变量分组"), this,
                        SLOT(slotAddVarGroup(bool)));

  m_varRsubMenu->addAction(QIcon(":/Icon/add.png"),
                           MainWindow::tr("新建二级量分组"), this,
                           SLOT(slotAddVarSubGroup(bool)));
  m_varRsubMenu->addAction(QIcon(":/Icon/delete.png"),
                           MainWindow::tr("删除分组"), this,
                           SLOT(slotRemoveVarGroup(bool)));
  m_varRsubMenu->addAction(QIcon(":/Icon/edit.png"), MainWindow::tr("修改名字"),
                           this, SLOT(slotEditVarGroupName(bool)));

  m_safeVRMenu->addAction(QIcon(":/Icon/add.png"),
                          MainWindow::tr("新建一级变量分组"), this,
                          SLOT(slotAddSafeVarGroup(bool)));

  m_safeVRsubMenu->addAction(QIcon(":/Icon/add.png"),
                             MainWindow::tr("新建二级量分组"), this,
                             SLOT(slotAddSafeVarSubGroup(bool)));
  m_safeVRsubMenu->addAction(QIcon(":/Icon/delete.png"),
                             MainWindow::tr("删除分组"), this,
                             SLOT(slotRemoveSafeVarGroup(bool)));
  m_safeVRsubMenu->addAction(QIcon(":/Icon/edit.png"),
                             MainWindow::tr("修改名字"), this,
                             SLOT(slotEditSafeVarGroupName(bool)));

  m_reciMenu->addAction(QIcon(":/Icon/add.png"),
                        MainWindow::tr("新建一级变量分组"), this,
                        SLOT(slotAddReciVarGroup(bool)));

  m_reciSubMenu->addAction(QIcon(":/Icon/add.png"),
                           MainWindow::tr("新建二级量分组"), this,
                           SLOT(slotAddReciVarSubGroup(bool)));
  m_reciSubMenu->addAction(QIcon(":/Icon/delete.png"),
                           MainWindow::tr("删除分组"), this,
                           SLOT(slotRemoveReciVarGroup(bool)));
  m_reciSubMenu->addAction(QIcon(":/Icon/edit.png"), MainWindow::tr("修改名字"),
                           this, SLOT(slotEditReciVarGroupName(bool)));

  m_tempMenu->addAction(QIcon(":/Icon/add.png"),
                        MainWindow::tr("新建一级变量分组"), this,
                        SLOT(slotAddTempVarGroup(bool)));

  m_tempSubMenu->addAction(QIcon(":/Icon/add.png"),
                           MainWindow::tr("新建二级量分组"), this,
                           SLOT(slotAddTempVarSubGroup(bool)));
  m_tempSubMenu->addAction(QIcon(":/Icon/delete.png"),
                           MainWindow::tr("删除分组"), this,
                           SLOT(slotRemoveTempVarGroup(bool)));
  m_tempSubMenu->addAction(QIcon(":/Icon/edit.png"), MainWindow::tr("修改名字"),
                           this, SLOT(slotEditTempVarGroupName(bool)));

  m_scriptMenu1->addAction(QIcon(":/Icon/add.png"), MainWindow::tr("添加脚本"),
                           this, SLOT(slotAddScript(bool)));

  m_scriptMenu2->addAction(QIcon(":/Icon/edit.png"), MainWindow::tr("属性"),
                           this, SLOT(slotEditScriptProp(bool)));
  m_scriptMenu2->addAction(QIcon(":/Icon/delete.png"),
                           MainWindow::tr("删除脚本"), this,
                           SLOT(slotRemoveScript(bool)));
}

void MainWindow::initMenuTree() {
  auto l = m_scriptView;
  l->setStyleSheet("border:none");
  l->setModel(m_scriptModel);

  connect(m_scriptView, &YDListView::clicked, this,
          &MainWindow::slotScriptItemClicked);

  connect(m_scriptView, &YDListView::doubleClicked, this,
          &MainWindow::slotScriptItemDBClicked);

  m_scriptView->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(m_scriptView, &YDListView::customContextMenuRequested, this,
          &MainWindow::slotScriptMenu);

  auto t = m_logicTree;

  t->setStyleSheet("border:none");

  t->setItemDelegate(new YDMenuDeletegate(t));

  // tree
  t->setEditTriggers(QTreeView::DoubleClicked);
  t->setSelectionBehavior(QTreeView::SelectRows);
  t->setSelectionMode(QTreeView::SingleSelection);
  t->setFocusPolicy(Qt::NoFocus);

  // drag and drop 追加
  t->setDragEnabled(true);
  t->setAcceptDrops(true);
  t->setDropIndicatorShown(true);
  t->setDragDropMode(QAbstractItemView::InternalMove);
  // ------------------

  // tree head
  t->header()->setHighlightSections(true);
  t->header()->setDefaultAlignment(Qt::AlignCenter);
  t->header()->setDefaultSectionSize(100);
  t->header()->setStretchLastSection(true);
  t->header()->setSortIndicator(0, Qt::AscendingOrder);

  t->header()->hide();

  // tree model
  t->setModel(m_menuModel);

  t->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(t, &QTreeView::customContextMenuRequested, this,
          &MainWindow::slotTreeMenu);
  connect(t, &QTreeView::clicked, this, &MainWindow::slotTaskItemClick);
  connect(t, &QTreeView::doubleClicked, this,
          &MainWindow::slotTaskItemDoubleClick);
}

void MainWindow::initModules() {
  ui->MoveListView->setModel(m_moveModel);
  ui->IOListView->setModel(m_ioModel);
  ui->ControlListView->setModel(m_controlModel);
  ui->OtherListView->setModel(m_otherModel);
}

void MainWindow::initModuleProp() {
  ui->property_tree->setAlternatingRowColors(true);
  ui->property_tree->setModel(m_modulePropModel);
  ui->property_tree->setItemDelegate(new YDPropertyDelegate(this));
  ui->property_tree->setColumnWidth(0, 150);
}

void MainWindow::initVariableTable() {
  YDProjectManage::setVariableGruopModle(m_varGroupModel);
  YDProjectManage::updateVariableGroupModel();
  ui->VarGroupView->setItemDelegate(new YDVarGroupDeletegate(ui->VarGroupView));
  ui->VarGroupView->setEditTriggers(QTreeView::DoubleClicked);
  ui->VarGroupView->setSelectionBehavior(QTreeView::SelectRows);
  ui->VarGroupView->setSelectionMode(QTreeView::SingleSelection);
  ui->VarGroupView->setAlternatingRowColors(true);
  ui->VarGroupView->setFocusPolicy(Qt::NoFocus);
  ui->VarGroupView->setModel(m_varGroupModel);

  ui->VarGroupView_2->setItemDelegate(
      new YDVarGroupDeletegate(ui->VarGroupView_2));
  ui->VarGroupView_2->setEditTriggers(QTreeView::DoubleClicked);
  ui->VarGroupView_2->setSelectionBehavior(QTreeView::SelectRows);
  ui->VarGroupView_2->setSelectionMode(QTreeView::SingleSelection);
  ui->VarGroupView_2->setAlternatingRowColors(true);
  ui->VarGroupView_2->setFocusPolicy(Qt::NoFocus);

  ui->VarGroupView_4->setItemDelegate(
      new YDVarGroupDeletegate(ui->VarGroupView_4));
  ui->VarGroupView_4->setEditTriggers(QTreeView::DoubleClicked);
  ui->VarGroupView_4->setSelectionBehavior(QTreeView::SelectRows);
  ui->VarGroupView_4->setSelectionMode(QTreeView::SingleSelection);
  ui->VarGroupView_4->setAlternatingRowColors(true);
  ui->VarGroupView_4->setFocusPolicy(Qt::NoFocus);
  ui->VarGroupView_4->setModel(m_varGroupModel);

  ui->SafeGroupView->setItemDelegate(
      new YDVarGroupDeletegate(ui->SafeGroupView));
  ui->SafeGroupView->setEditTriggers(QTreeView::DoubleClicked);
  ui->SafeGroupView->setSelectionBehavior(QTreeView::SelectRows);
  ui->SafeGroupView->setSelectionMode(QTreeView::SingleSelection);
  ui->SafeGroupView->setAlternatingRowColors(true);
  ui->SafeGroupView->setFocusPolicy(Qt::NoFocus);
  ui->SafeGroupView->setModel(m_varGroupModel);

  ui->VarGroupView->header()->setHighlightSections(true);
  ui->VarGroupView->header()->setDefaultAlignment(Qt::AlignCenter);
  ui->VarGroupView->header()->setDefaultSectionSize(100);
  ui->VarGroupView->header()->setStretchLastSection(true);
  ui->VarGroupView->header()->setSortIndicator(0, Qt::AscendingOrder);

  ui->VarGroupView_2->header()->setHighlightSections(true);
  ui->VarGroupView_2->header()->setDefaultAlignment(Qt::AlignCenter);
  ui->VarGroupView_2->header()->setDefaultSectionSize(100);
  ui->VarGroupView_2->header()->setStretchLastSection(true);
  ui->VarGroupView_2->header()->setSortIndicator(0, Qt::AscendingOrder);

  ui->VarGroupView_4->header()->setHighlightSections(true);
  ui->VarGroupView_4->header()->setDefaultAlignment(Qt::AlignCenter);
  ui->VarGroupView_4->header()->setDefaultSectionSize(100);
  ui->VarGroupView_4->header()->setStretchLastSection(true);
  ui->VarGroupView_4->header()->setSortIndicator(0, Qt::AscendingOrder);

  ui->SafeGroupView->header()->setHighlightSections(true);
  ui->SafeGroupView->header()->setDefaultAlignment(Qt::AlignCenter);
  ui->SafeGroupView->header()->setDefaultSectionSize(100);
  ui->SafeGroupView->header()->setStretchLastSection(true);
  ui->SafeGroupView->header()->setSortIndicator(0, Qt::AscendingOrder);

  ui->VarView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->VarView->setModel(m_variablModel);
  ui->VarView->setSelectionBehavior(QTableView::SelectRows);

  ui->VarView_2->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);

  ui->VarView_4->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->VarView_4->setModel(m_tempVarModel);
  ui->VarView_4->setSelectionBehavior(QTableView::SelectRows);

  ui->SafeVarView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->SafeVarView->setModel(m_safeVarModel);
  ui->SafeVarView->setSelectionBehavior(QTableView::SelectRows);

  ui->VarGroupView->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->VarGroupView, &QTreeView::customContextMenuRequested, this,
          &MainWindow::slotVarMenu);

  ui->SafeGroupView->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->SafeGroupView, &QTreeView::customContextMenuRequested, this,
          &MainWindow::slotSafeVarMenu);

  ui->VarGroupView_4->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->VarGroupView_4, &QTreeView::customContextMenuRequested, this,
          &MainWindow::slotTempVarMenu);

  connect(ui->VarGroupView, &QTreeView::clicked, this,
          &MainWindow::slotVarGroupClick);
  connect(ui->VarGroupView_2, &QTreeView::clicked, this,
          &MainWindow::slotReciVarGroupClick);
  connect(ui->VarGroupView_4, &QTreeView::clicked, this,
          &MainWindow::slotTempVarGroupClick);

  connect(ui->VarView, &QTableView::doubleClicked, this,
          &MainWindow::slotVarViewDoubleClick);

  connect(ui->VarView_2, &QTableView::doubleClicked, this,
          &MainWindow::slotReciVarViewDoubleClick);

  connect(ui->VarView_4, &QTableView::doubleClicked, this,
          &MainWindow::slotTempVarViewDoubleClick);

  connect(ui->SafeGroupView, &QTreeView::clicked, this,
          &MainWindow::slotSafeGroupClick);
  connect(ui->SafeGroupView, &QTreeView::doubleClicked, this,
          &MainWindow::slotSafeGroupDoubleClick);

  connect(ui->SafeVarView, &QTableView::doubleClicked, this,
          &MainWindow::slotSafeVarDoubleClick);
}

void MainWindow::initCylinderDock() {
  ui->CylinderList->setModel(m_cylinderModel);
  connect(ui->CylinderList, &QListView::clicked, this,
          &MainWindow::slotCylinderItemSingleClick);
  connect(ui->CylinderList, &QListView::doubleClicked, this,
          &MainWindow::slotCylinderItemDoubleClick);
}

void MainWindow::initConnect() {
  connect(m_deviceSetDlg, &QDialog::finished, this,
          &MainWindow::slotDeviceSetDlgFinished);

  connect(m_netSetDlg, &QDialog::finished, this,
          &MainWindow::slotNetSetFinished);

  connect(m_scriptProp, &QDialog::finished, this,
          &MainWindow::slotScriptPropClose);

  connect(m_createPDlg, &YDNameDialog::finished, this,
          &MainWindow::slotCratePFinished);

  connect(m_changeDlg, &YDNameDialog::finished, this,
          &MainWindow::slotChangeNFinished);

  connect(m_saveasDlg, &YDNameDialog::finished, this,
          &MainWindow::slotSaveasFinished);

  connect(m_createReciDlg, &YDNameDialog::finished, this,
          &MainWindow::slotCreateReciFinished);

  connect(m_changeReciDlg, &YDNameDialog::finished, this,
          &MainWindow::slotChangeReciFinished);

  connect(m_saveasReciDlg, &YDNameDialog::finished, this,
          &MainWindow::slotSaveasReciFinished);

  connect(m_backPDlg, &QDialog::finished, this,
          &MainWindow::slotBPDialogFinished);

  //  connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this,
  //          &MainWindow::slotTabClosed);

  connect(ui->tabWidget, &QTabWidget::currentChanged, this,
          &MainWindow::slotTabChanged);

  connect(ui->MenuDock, &YDDockWidget::sigCloseClicked, this,
          [this]() { ui->a_wpromg->setChecked(false); });
  connect(ui->PropertyDock, &YDDockWidget::sigCloseClicked, this,
          [this]() { ui->a_property->setChecked(false); });
  connect(ui->VarDock, &YDDockWidget::sigCloseClicked, this,
          [this]() { ui->a_wgbvar->setChecked(false); });
  connect(ui->PeiFVarDock, &YDDockWidget::sigCloseClicked, this,
          [this]() { ui->a_wwyvar->setChecked(false); });
  connect(ui->TempVarDock, &YDDockWidget::sigCloseClicked, this,
          [this]() { ui->a_wtpvar->setChecked(false); });
  connect(ui->SafeVarDock, &YDDockWidget::sigCloseClicked, this,
          [this]() { ui->a_wsfvar->setChecked(false); });
  connect(ui->CylinderDock, &YDDockWidget::sigCloseClicked, this,
          [this]() { ui->a_wcylinder->setChecked(false); });
  connect(ui->InputDock, &YDDockWidget::sigCloseClicked, this,
          [this]() { ui->a_logOut->setChecked(false); });
  connect(ui->DebugDock, &YDDockWidget::sigCloseClicked, this,
          [this]() { ui->a_debugInfo->setChecked(false); });
}

void MainWindow::initOtherSetting() {
  m_createPDlg->setBtnName(MainWindow::tr("创建"));
  m_changeDlg->setBtnName(MainWindow::tr("更改"));
  m_saveasDlg->setBtnName(MainWindow::tr("另存为"));

  m_createReciDlg->setLabText(MainWindow::tr("配方名称:"));
  m_changeReciDlg->setLabText(MainWindow::tr("配方名称:"));
  m_saveasReciDlg->setLabText(MainWindow::tr("配方名称:"));

  m_createReciDlg->setBtnName(MainWindow::tr("创建"));
  m_changeReciDlg->setBtnName(MainWindow::tr("更改"));
  m_saveasReciDlg->setBtnName(MainWindow::tr("另存为"));

  ui->toolBox->setCurrentIndex(0);
  tabifyDockWidget(ui->PropertyDock, ui->VarDock);
  tabifyDockWidget(ui->VarDock, ui->SafeVarDock);
  tabifyDockWidget(ui->SafeVarDock, ui->PeiFVarDock);
  tabifyDockWidget(ui->PeiFVarDock, ui->TempVarDock);
  tabifyDockWidget(ui->TempVarDock, ui->CylinderDock);

  tabifyDockWidget(ui->InputDock, ui->DebugDock);

  ui->InputDock->raise();
  ui->PropertyDock->raise();

  ui->addVar->setDisabled(true);
  ui->DelVar->setDisabled(true);

  ui->addSafeVar->setDisabled(true);
  ui->DelSafeVar->setDisabled(true);

  ui->AddVarG_2->setDisabled(true);
  ui->DelVarG_2->setDisabled(true);

  ui->addVar_2->setDisabled(true);
  ui->DelVa_2->setDisabled(true);

  ui->addVar_4->setDisabled(true);
  ui->DelVar_4->setDisabled(true);

  m_codeManage->resize(1744, 970);

  //  ui->a_LogicStart->setDisabled(true);
  //  ui->a_LogicStop->setDisabled(true);

  m_logicStart->setDisabled(true);
  m_logicStop->setDisabled(true);

  //  ui->tabWidget->setTabsClosable(true);

  ui->a_notSave->setChecked(true);

  //  ui->tabWidget->setStyleSheet(
  //      "QTabBar::tab{background:white;  border-right:1px solid #bfbfbf;  "
  //      "border-left:1px solid #bfbfbf;"
  //      "border-bottom:1px solid #bfbfbf;  border-top: 1px solid #bfbfbf;  "
  //      "padding-bottom:-1px;"
  //      "min-width:126;  min-height:26px;  font-size:14px;  "
  //      "font-family:Microsoft YaHei;}"
  //      "QTabBar::tab:selected{background:white;color:black;}"
  //      "QTabBar::tab:!selected{background:#f0f0f0;color:black;}"
  //      "QTabBar::tab:hover{background:#e5f1fb;color:black;}"
  //      "QTabBar::close-button {image:url(:/Icon/close_normal.png);}"
  //      "QTabBar::close-button:hover {image:url(:/Icon/close_press.png);}");
}

void MainWindow::initOpenMenu() {
  auto m = ui->a_open;
  for (QAction *f : m_files) m->removeAction(f);
  m_files.clear();

  auto dm = ui->a_del;
  for (QAction *f : m_delFiles) dm->removeAction(f);
  m_delFiles.clear();

  std::vector<std::string> list;
  YDProjectManage::enumuerateProjects(list);
  auto name = YDProjectManage::getCurrentProject();
  for (auto v : list) {
    auto str = STRTQSTR(v.c_str());
    if (str == name) continue;
    auto a = m->addAction(str);
    connect(a, &QAction::triggered, this, &MainWindow::slotActionTriggered);

    auto b = dm->addAction(str);
    connect(b, &QAction::triggered, this, &MainWindow::slotDelActionTriggered);
    m_files.push_back(a);
    m_delFiles.push_back(b);
  }

  selectModule = nullptr;
  initOpenWayMenu();
}

void MainWindow::initOpenWayMenu() {
  auto m = ui->a_openway;
  auto dm = ui->a_dellway;
  for (QAction *f : m_ways) m->removeAction(f);
  for (QAction *f : m_delWays) dm->removeAction(f);
  m_ways.clear();
  m_delWays.clear();

  std::vector<std::string> list;
  YDProjectManage::enumuerateRecipes(list);
  auto name = YDProjectManage::getCurrentRecipe();
  for (auto v : list) {
    auto str = STRTQSTR(v.c_str());
    if (str == name) continue;
    auto a = m->addAction(str);
    connect(a, &QAction::triggered, this, &MainWindow::slotWayActionTriggered);
    auto b = dm->addAction(str);
    connect(b, &QAction::triggered, this,
            &MainWindow::slotDelWayActionTriggered);
    m_ways.push_back(a);
    m_delWays.push_back(b);
  }
  updateRecipName();
}

void MainWindow::initReciWidget() {
  if (!m_isShowReciWidget) {
    m_isShowReciWidget = true;
    ui->VarGroupView_2->setModel(m_varGroupModel);
    ui->VarView_2->setModel(m_reciVarModel);
    ui->VarView_2->setSelectionBehavior(QTableView::SelectRows);
    ui->VarGroupView_2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->VarGroupView_2, &QTreeView::customContextMenuRequested, this,
            &MainWindow::slotReciVarMenu);

    ui->AddVarG_2->setEnabled(true);
    ui->DelVarG_2->setEnabled(true);
  }
}

void MainWindow::initDebugActionEnable(const bool &flag) {
  ui->a_dstartz->setEnabled(flag);
  ui->a_dstartm->setEnabled(flag);
  ui->a_dpausem->setEnabled(flag);
  ui->a_dstopm->setEnabled(flag);
  //  ui->a_LogicStart->setEnabled(flag);
  m_logicStart->setEnabled(flag);
  m_isLogicTaskStart = false;

  setControlEnabled(!flag);
  YDHelper::setDebugMode(flag);
  m_moveSysW->update();
}

void MainWindow::updateVarGroupModel() {
  ui->VarGroupView->setModel(nullptr);
  ui->VarGroupView->setModel(m_varGroupModel);
  ui->SafeGroupView->setModel(nullptr);
  ui->SafeGroupView->setModel(m_varGroupModel);
}

void MainWindow::updateSafeVarModel() {
  ui->SafeVarView->setModel(nullptr);
  ui->SafeVarView->setModel(m_safeVarModel);
}

void MainWindow::updateCylinderModels() {
  ui->CylinderList->setModel(nullptr);
  ui->CylinderList->setModel(m_cylinderModel);
}

void MainWindow::updateCylinderInfos(yd::dev::Cylinder *cyl,
                                     const QStringList &infos) {
  cyl->base.name = QSTRTSTR(infos[0]);
  cyl->direction1_name = QSTRTSTR(infos[1]);
  cyl->direction2_name = QSTRTSTR(infos[2]);
  int index = 5;
  auto DOVars = YDProjectManage::getDOInfos();
  auto DIVars = YDProjectManage::getDIInfos();
  auto AxisVars = YDProjectManage::getAxisList();
  if (infos[3] == "single") {
    for (auto v : DOVars) {
      if (STRTQSTR(v->io_name.c_str()) == infos[4]) {
        cyl->direction1_control.refer_device_id = v->device_id;
        cyl->direction1_control.refer_index = v->io_index;
        cyl->direction1_control.action_value = 0;
        cyl->direction2_control.refer_device_id = v->device_id;
        cyl->direction2_control.refer_index = v->io_index;
        cyl->direction2_control.action_value = 1;
        break;
      }
    }
  } else {
    index = 6;
    for (auto v : DOVars) {
      auto name = STRTQSTR(v->io_name.c_str());
      if (name == infos[4]) {
        cyl->direction1_control.refer_device_id = v->device_id;
        cyl->direction1_control.refer_index = v->io_index;
        cyl->direction1_control.action_value = 1;
      } else if (name == infos[5]) {
        cyl->direction2_control.refer_device_id = v->device_id;
        cyl->direction2_control.refer_index = v->io_index;
        cyl->direction2_control.action_value = 1;
      }
    }
  }

  int wayF = infos[index].toUInt();
  if (0 == wayF) {
    cyl->direction1_inplace.type = CYLINDER_ARRIVE_IF_DELAYED;
    cyl->direction1_inplace.refer_device_id = 0;
    cyl->direction1_inplace.refer_index = 0;
    cyl->direction1_inplace.action_value = 0;
    cyl->direction1_inplace.delay_time = infos[index + 2].toUInt();
  } else if (3 == wayF) {
    cyl->direction1_inplace.type = CYLINDER_ARRIVE_IF_AXIS_ENCODER_TO;
    for (auto v : AxisVars) {
      if (STRTQSTR(v->axis_name.c_str()) == infos[index + 1]) {
        cyl->direction1_inplace.refer_device_id = v->device_id;
        cyl->direction1_inplace.refer_index = v->axis_index;
        cyl->direction1_inplace.action_value = infos[index + 2].toUInt();
      }
    }
  } else {
    if (1 == wayF)
      cyl->direction1_inplace.type = CYLINDER_ARRIVE_IF_DITRIGGRED;
    else
      cyl->direction1_inplace.type = CYLINDER_ARRIVE_IF_DITRIGGRED_T_DELAYED;

    for (auto v : DIVars) {
      if (STRTQSTR(v->io_name.c_str()) == infos[index + 1]) {
        cyl->direction1_inplace.refer_device_id = v->device_id;
        cyl->direction1_inplace.refer_index = v->io_index;
        cyl->direction1_inplace.action_value = 1;
        if (2 == wayF) {
          cyl->direction1_inplace.delay_time = infos[index + 2].toUInt();
        }
        break;
      }
    }
  }
  cyl->direction1_inplace.alarm_time = infos[index + 3].toUInt();

  index += 4;
  wayF = infos[index].toUInt();
  if (0 == wayF) {
    cyl->direction2_inplace.type = CYLINDER_ARRIVE_IF_DELAYED;
    cyl->direction2_inplace.refer_device_id = 0;
    cyl->direction2_inplace.refer_index = 0;
    cyl->direction2_inplace.action_value = 1;
    cyl->direction2_inplace.delay_time = infos[index + 2].toUInt();
  } else if (3 == wayF) {
    cyl->direction2_inplace.type = CYLINDER_ARRIVE_IF_AXIS_ENCODER_TO;
    for (auto v : AxisVars) {
      if (STRTQSTR(v->axis_name.c_str()) == infos[index + 1]) {
        cyl->direction2_inplace.refer_device_id = v->device_id;
        cyl->direction2_inplace.refer_index = v->axis_index;
        cyl->direction2_inplace.action_value = infos[index + 2].toUInt();
      }
    }
  } else {
    if (1 == wayF)
      cyl->direction2_inplace.type = CYLINDER_ARRIVE_IF_DITRIGGRED;
    else
      cyl->direction2_inplace.type = CYLINDER_ARRIVE_IF_DITRIGGRED_T_DELAYED;

    for (auto v : DIVars) {
      if (STRTQSTR(v->io_name.c_str()) == infos[index + 1]) {
        cyl->direction2_inplace.refer_device_id = v->device_id;
        cyl->direction2_inplace.refer_index = v->io_index;
        cyl->direction2_inplace.action_value = 1;
        if (2 == wayF) {
          cyl->direction2_inplace.delay_time = infos[index + 2].toUInt();
        }
        break;
      }
    }
  }
  cyl->direction2_inplace.alarm_time = infos[index + 3].toUInt();

  YDProjectManage::updateCylinderVariables(cyl);
  updateCylinderModels();
}

QStringList MainWindow::getCylinderInfos(yd::dev::Cylinder *cyl) const {
  auto DOVars = YDProjectManage::getDOInfos();
  auto DIVars = YDProjectManage::getDIInfos();
  auto AxisVars = YDProjectManage::getAxisList();
  QStringList infos;
  infos << STRTQSTR(cyl->base.name.c_str());
  infos << STRTQSTR(cyl->direction1_name.c_str());
  infos << STRTQSTR(cyl->direction2_name.c_str());
  if ((cyl->direction1_control.refer_device_id ==
       cyl->direction2_control.refer_device_id) &&
      (cyl->direction1_control.refer_index ==
       cyl->direction2_control.refer_index)) {
    infos << "single";
    QString doName;
    for (auto d : DOVars) {
      if (d->device_id == cyl->direction1_control.refer_device_id &&
          d->io_index == cyl->direction1_control.refer_index) {
        doName = STRTQSTR(d->io_name.c_str());
        break;
      }
    }
    infos << doName;

  } else {
    infos << "double";
    QString doName1;
    for (auto d : DOVars) {
      if (d->device_id == cyl->direction1_control.refer_device_id &&
          d->io_index == cyl->direction1_control.refer_index) {
        doName1 = STRTQSTR(d->io_name.c_str());
        break;
      }
    }
    infos << doName1;

    QString doName2;
    for (auto d : DOVars) {
      if (d->device_id == cyl->direction2_control.refer_device_id &&
          d->io_index == cyl->direction2_control.refer_index) {
        doName2 = STRTQSTR(d->io_name.c_str());
        break;
      }
    }
    infos << doName2;
  }

  int index = cyl->direction1_inplace.type - CYLINDER_ARRIVE_IF_DELAYED;
  infos << QString::number(index);

  switch (index) {
    case 0: {
      infos << "";
      infos << QString::number(cyl->direction1_inplace.delay_time);
    } break;
    case 1: {
      QString diName;
      for (auto d : DIVars) {
        if (d->device_id == cyl->direction1_inplace.refer_device_id &&
            d->io_index == cyl->direction1_inplace.refer_index) {
          diName = STRTQSTR(d->io_name.c_str());
          break;
        }
      }
      infos << diName;
      infos << "0";
    } break;
    case 2: {
      QString diName;
      for (auto d : DIVars) {
        if (d->device_id == cyl->direction1_inplace.refer_device_id &&
            d->io_index == cyl->direction1_inplace.refer_index) {
          diName = STRTQSTR(d->io_name.c_str());
          break;
        }
      }
      infos << diName;
      infos << QString::number(cyl->direction1_inplace.delay_time);
    } break;
    case 3: {
      QString axName;
      for (auto ax : AxisVars) {
        if (ax->device_id == cyl->direction1_inplace.refer_device_id &&
            ax->axis_index == cyl->direction1_inplace.refer_index) {
          axName = STRTQSTR(ax->axis_name);
          break;
        }
        infos << axName;
        infos << QString::number(cyl->direction1_inplace.action_value);
      }
    } break;
  }
  infos << QString::number(cyl->direction1_inplace.alarm_time);

  index = cyl->direction2_inplace.type - CYLINDER_ARRIVE_IF_DELAYED;
  infos << QString::number(index);

  switch (index) {
    case 0: {
      infos << "";
      infos << QString::number(cyl->direction2_inplace.delay_time);
    } break;
    case 1: {
      QString diname;
      for (auto d : DIVars) {
        if (d->device_id == cyl->direction2_inplace.refer_device_id &&
            d->io_index == cyl->direction2_inplace.refer_index) {
          diname = STRTQSTR(d->io_name.c_str());
          break;
        }
      }
      infos << diname;
      infos << "0";
    } break;
    case 2: {
      QString diname;
      for (auto d : DIVars) {
        if (d->device_id == cyl->direction2_inplace.refer_device_id &&
            d->io_index == cyl->direction2_inplace.refer_index) {
          diname = STRTQSTR(d->io_name.c_str());
          break;
        }
      }
      infos << diname;
      infos << QString::number(cyl->direction2_inplace.delay_time);
    } break;
    case 3: {
      QString axName;
      for (auto ax : AxisVars) {
        if (ax->device_id == cyl->direction2_inplace.refer_device_id &&
            ax->axis_index == cyl->direction2_inplace.refer_index) {
          axName = STRTQSTR(ax->axis_name);
          break;
        }
      }
      infos << axName;
      infos << QString::number(cyl->direction2_inplace.action_value);
    } break;
  }

  infos << QString::number(cyl->direction2_inplace.alarm_time);

  return infos;
}

void MainWindow::updateProjectName(QString rName) {
  QString name = MainWindow::tr("业务逻辑编辑软件");
  QString project = YDProjectManage::getCurrentProject();
  if (!project.isEmpty()) {
    name = QString("%1  --  %2").arg(name, project);
  }
  if (rName != "") {
    name.append("/").append(rName);
  }

  setWindowTitle(name);
}

void MainWindow::updateRecipName() {
  auto rname = YDProjectManage::getCurrentRecipe();
  auto name = QString("%1 - %2").arg(MainWindow::tr("配方变量"), rname);
  ui->PeiFVarDock->setWindowTitle(name);
  updateProjectName(rname);
}

//运动监控时判断轴是否使能
bool MainWindow::judgeAxisEnabled() {
  bool isFlag = false;
  auto list = YDProjectManage::getMotionDevices();
  if (list.empty()) {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("需要添加设备!"));
    return isFlag;
  }
  for (auto item : list) {
    auto axises = item->listAxises;
    if (axises.empty()) {
      QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                           MainWindow::tr("轴列表不能为空!"));
      return isFlag;
    }
    for (auto axis : axises) {
      if (axis->enable) {
        isFlag = true;
        return isFlag;
      }
    }
  }
  QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                       MainWindow::tr("最少需要启用一个轴使能!"));
  return isFlag;
}

//判断网络IP是否为空
bool MainWindow::judgeNetWorkEmpty() {
  bool flag = true;
  if (!YDDgHelper::createInstance()) return flag;

  std::string strAddress = "";
  uint16 usPort = 0;
  uint32 uiTimeout = 0;
  YDProjectManage::GetDataGateway(strAddress, usPort, uiTimeout);

  if (strAddress.empty()) {
    auto rb = QMessageBox::information(this, MainWindow::tr("提示"),
                                       MainWindow::tr("请先设置后台数据网关!"),
                                       MainWindow::tr("确认"));
    if (0 == rb) {
      m_netSetDlg->open();
      return flag;
    }
  }
  auto filename = YDProjectManage::getFileName();
  if (!YDDgHelper::isInitialized(filename, STRTQSTR(strAddress), usPort))
    return flag;

  if (!YDDgHelper::getIProtocolClient()) return flag;

  if (!YDDgHelper::connect(3)) return flag;
  YDLogger::info(MainWindow::tr("网络连接成功!"));
  return false;
}

void MainWindow::updateData() {
  switch (m_debugWindowType) {
    case 0:
      m_axisWidget->updateData();
      break;
    case 1:
      m_cylinderWidget->updateData();
      break;
    case 2:
      m_inputWidget->updateData();
      break;
    case 3:
      m_outputWidget->updateData();
      break;
    case 4:
      m_varWidget->updateData();
      break;
  }

  updateTaskData();
}

void MainWindow::updateTaskData() {
  if (m_isLogicTaskStart) {
    auto index = ui->tabWidget->currentIndex();
    if (index >= 0) {
      auto w = static_cast<YDTabWidget *>(ui->tabWidget->widget(index));
      YDTask *o = w->getTask();
      if (o) {
        auto id = o->id();
        yd::proto::TaskState state;
        state.id = 0;
        state.state = 0;
        state.process_states.clear();

        YDDgHelper::getTaskState(id, &state);
        o->setState(state);
      }
    }
  }
}

void MainWindow::stopThread() { emit stop(); }

/**
 * @brief 调试时设置使能
 * @param enable
 */
void MainWindow::setControlEnabled(bool enable) {
  m_scriptMangeW->setEnabled(enable);
  m_menuR1->setEnabled(enable);    //新建任务
  m_menuR3->setEnabled(enable);    //子任务
  m_varRMain->setEnabled(enable);  //一级变量分组
  m_safeVRMenu->setEnabled(enable);
  m_reciMenu->setEnabled(enable);
  m_tempMenu->setEnabled(enable);
  m_varRsubMenu->setEnabled(enable);  //二级变量分组
  m_safeVRsubMenu->setEnabled(enable);
  m_reciSubMenu->setEnabled(enable);
  m_tempSubMenu->setEnabled(enable);
  m_scriptMenu1->setEnabled(enable);  //脚本
  m_scriptMenu2->setEnabled(enable);

  ui->AddVarG->setEnabled(enable);  //全局变量
  ui->DelVarG->setEnabled(enable);
  ui->GasAdd->setEnabled(enable);  //气油缸
  ui->GasDel->setEnabled(enable);
  ui->AddSafeVarG->setEnabled(enable);  //安全变量
  ui->DelSafeVarG->setEnabled(enable);
  ui->AddVarG_2->setEnabled(enable);  //配方变量
  ui->DelVarG_2->setEnabled(enable);
  ui->AddVarG_4->setEnabled(enable);  //临时变量
  ui->DelVarG_4->setEnabled(enable);

  if (!enable) {
    ui->addVar->setEnabled(enable);
    ui->DelVar->setEnabled(enable);
    ui->addSafeVar->setEnabled(enable);
    ui->DelSafeVar->setEnabled(enable);
    ui->addVar_2->setEnabled(enable);
    ui->DelVa_2->setEnabled(enable);
    ui->addVar_4->setEnabled(enable);
    ui->DelVar_4->setEnabled(enable);
    ui->a_notSave->trigger();
  }

  ui->VarView->setEnabled(enable);
  ui->VarView_2->setEnabled(enable);
  ui->VarView_4->setEnabled(enable);
  ui->SafeVarView->setEnabled(enable);
  ui->CylinderList->setEnabled(enable);

  ui->a_new->setEnabled(enable);  //菜单栏
  ui->a_open->setEnabled(enable);
  ui->a_close->setEnabled(enable);
  ui->a_rename->setEnabled(enable);
  ui->a_save->setEnabled(enable);
  ui->a_saveall->setEnabled(enable);
  ui->a_saveoth->setEnabled(enable);
  ui->a_del->setEnabled(enable);
  ui->a_exit->setEnabled(enable);
  ui->a_newway->setEnabled(enable);
  ui->a_openway->setEnabled(enable);
  ui->a_changeWay->setEnabled(enable);
  ui->a_saveway->setEnabled(enable);
  ui->a_saveow->setEnabled(enable);
  ui->a_dellway->setEnabled(enable);
  ui->a_ttalkset->setEnabled(enable);
  ui->a_timingSave->setEnabled(enable);
  ui->property_tree->setEnabled(enable);
}

void MainWindow::screenShot() {
  auto w = static_cast<QListWidget *>(ui->tabWidget->currentWidget());
  if (w) {
    QPixmap pix = w->grab();
    auto index = ui->tabWidget->currentIndex();
    QString pre = QCoreApplication::applicationDirPath() + "/screenshot/";
    QString text = ui->tabWidget->tabText(index);
    QString time = QDateTime::currentDateTime().toString("yyMMdd_hhmmss");
    QString file = QString("%1%2_%3.png").arg(pre, text, time);

    pix.save(file, Q_NULLPTR, 100);
  }
}

void MainWindow::setBtnState(bool b) {
  auto root = YDProjectManage::getYDTaskRoot();
  root->clear();

  m_menuModel->updateModel();
  setControlEnabled(b);
  ui->a_startDebug->setEnabled(b);
  ui->a_dupload->setEnabled(b);
  ui->a_ddownload->setEnabled(b);
  ui->a_doldebug->setEnabled(b);
}

void MainWindow::setSelectTime(int index) {
  ui->a_notSave->setChecked(false);
  ui->a_save5->setChecked(false);
  ui->a_save10->setChecked(false);
  ui->a_save20->setChecked(false);
  ui->a_save30->setChecked(false);
  switch (index) {
    case 0:
      ui->a_notSave->setChecked(true);
      break;
    case 1:
      ui->a_save5->setChecked(true);
      break;
    case 2:
      ui->a_save10->setChecked(true);
      break;
    case 3:
      ui->a_save20->setChecked(true);
      break;
    case 4:
      ui->a_save30->setChecked(true);
      break;
    default:
      break;
  }
}

void MainWindow::addVar(int type, const QStringList &list,
                        yd::vr::SystemVariable *var) {
  if (var) {
    var->variable_name = std::string(list[0].toLocal8Bit().data());

    var->value_type = type;
    int index = list[1].toUInt();

    switch (index) {
      case 0:
        var->init_value =
            (list[2] == "False" ? std::string("0") : std::string("1"));
        break;
      case 1:
      case 2:
        var->init_value = std::string(list[2].toLocal8Bit().data());
        var->min_value = std::string(list[3].toLocal8Bit().data());
        var->max_value = std::string(list[4].toLocal8Bit().data());
        break;
      case 3:
        var->init_value = std::string(list[2].toLocal8Bit().data());
        break;
      case 4: {
        memset(&m_coords, 0, sizeof(yd::COORDS));
        m_coords.ucCtrlType = 0;
        QStringList grouplist = list[2].split(',');
        for (int i = 0; i < grouplist.size(); ++i) {
          if (!grouplist[i].isEmpty()) {
            QStringList itemlist = grouplist[i].split('@');
            YDHelper::updateCoorData(m_coords.arrCoords[i], itemlist);
            m_coords.ucNumber = i + 1;
          }
        }

        std::string stdjson;
        yd::CRapidJsonHelper::AxisCoords2Json(&m_coords, stdjson);
        var->init_value = stdjson;
      } break;
    }
  }
}

void MainWindow::addReciVar(int type, const QStringList &list,
                            yd::vr::SystemVariable *var) {
  if (var) {
    var->variable_name = std::string(list[0].toLocal8Bit().data());

    var->value_type = type;
    int index = list[1].toUInt();

    switch (index) {
      case 0:
        var->current_value =
            (list[2] == "False" ? std::string("0") : std::string("1"));
        break;
      case 1:
      case 2:
        var->current_value = std::string(list[2].toLocal8Bit().data());
        var->min_value = std::string(list[3].toLocal8Bit().data());
        var->max_value = std::string(list[4].toLocal8Bit().data());
        break;
      case 3:
        var->current_value = std::string(list[2].toLocal8Bit().data());
        break;
      case 4: {
        memset(&m_coords, 0, sizeof(yd::COORDS));
        m_coords.ucCtrlType = 0;
        QStringList grouplist = list[2].split(',');
        for (int i = 0; i < grouplist.size(); ++i) {
          if (!grouplist[i].isEmpty()) {
            QStringList itemlist = grouplist[i].split('@');
            YDHelper::updateCoorData(m_coords.arrCoords[i], itemlist);
            m_coords.ucNumber = i + 1;
          }
        }

        std::string stdjson;
        yd::CRapidJsonHelper::AxisCoords2Json(&m_coords, stdjson);
        var->current_value = stdjson;
      } break;
    }
  }
}

void MainWindow::on_addVar_clicked() {
  if (m_addVarDlg) delete m_addVarDlg;
  m_addVarDlg = new YDAddVariableDialog(this);
  connect(m_addVarDlg, &YDAddVariableDialog::finished, this,
          &MainWindow::slotAddVarFinished);
  m_addVarDlg->open();
}

void MainWindow::slotAddVarFinished() {
  if (m_addVarDlg->result() == QDialog::Accepted) {
    auto list = m_addVarDlg->textList();
    if (!list.isEmpty()) {
      auto type = YDHelper::getDataTypeIndex(list[1]);
      yd::vr::SystemVariable *var = nullptr;
      YDVariable *subvg =
          reinterpret_cast<YDVariable *>(m_varIndex.internalPointer());
      YDProjectManage::createGlobalVar(subvg->parent()->groupId(),
                                       subvg->groupId(), type, var);
      addVar(type, list, var);
      YDLogger::info(MainWindow::tr("创建全局变量: %1 成功").arg(list[0]));
      m_variablModel->setGroupId(subvg->groupId());
    }
  }
}

void MainWindow::on_addVar_2_clicked() {
  if (m_addReciVarDlg) delete m_addReciVarDlg;
  m_addReciVarDlg = new YDAddReciVarDialog(this);
  connect(m_addReciVarDlg, &YDAddReciVarDialog::finished, this,
          &MainWindow::slotAddReciVarFinished);
  m_addReciVarDlg->open();
}

void MainWindow::slotAddReciVarFinished() {
  if (m_addReciVarDlg->result() == QDialog::Accepted) {
    auto list = m_addReciVarDlg->textList();
    if (!list.isEmpty()) {
      auto type = YDHelper::getDataTypeIndex(list[1]);
      yd::vr::SystemVariable *var = nullptr;
      YDVariable *subvg =
          reinterpret_cast<YDVariable *>(m_reciVarIndex.internalPointer());
      YDProjectManage::CreateReciVar(subvg->parent()->groupId(),
                                     subvg->groupId(), type, var);

      addReciVar(type, list, var);
      YDLogger::info(MainWindow::tr("创建配方变量: %1 成功").arg(list[0]));
      m_reciVarModel->setGroupId(subvg->groupId());
    }
  }
}

void MainWindow::on_addVar_4_clicked() {
  if (m_addTempVarDlg) delete m_addTempVarDlg;
  m_addTempVarDlg = new YDAddTempVarDialog(this);
  connect(m_addTempVarDlg, &YDAddTempVarDialog::finished, this,
          &MainWindow::slotAddTempVarFinished);
  m_addTempVarDlg->open();
}

void MainWindow::slotAddTempVarFinished() {
  if (m_addTempVarDlg->result() == QDialog::Accepted) {
    auto list = m_addTempVarDlg->textList();
    if (!list.isEmpty()) {
      auto type = YDHelper::getDataTypeIndex(list[1]);
      yd::vr::SystemVariable *var = nullptr;
      YDVariable *subvg =
          reinterpret_cast<YDVariable *>(m_tempVarIndex.internalPointer());
      YDProjectManage::CreateTempVar(subvg->parent()->groupId(),
                                     subvg->groupId(), type, var);
      addVar(type, list, var);
      YDLogger::info(MainWindow::tr("创建临时变量: %1 成功").arg(list[0]));
      m_tempVarModel->setGroupId(subvg->groupId());
    }
  }
}

void MainWindow::slotUpdateVar() {
  if (m_addVarDlg->result() == QDialog::Accepted) {
    auto list = m_addVarDlg->textList();
    YDVariable *vg =
        reinterpret_cast<YDVariable *>(m_varIndex.internalPointer());
    int row = m_varViewIndex.row();
    auto vars = YDProjectManage::GetGroupedGlobalVars(vg->groupId());

    if (row < vars.size()) {
      auto var = vars[row];
      var->variable_name = std::string(list[0].toLocal8Bit().data());
      var->value_type = YDHelper::getDataTypeIndex(list[1]);
      int index = list[1].toUInt();

      switch (index) {
        case 0:
          var->init_value =
              (list[2] == "False" ? std::string("0") : std::string("1"));
          break;
        case 1:
        case 2:
          var->init_value = std::string(list[2].toLocal8Bit().data());
          var->min_value = std::string(list[3].toLocal8Bit().data());
          var->max_value = std::string(list[4].toLocal8Bit().data());
          break;
        case 3:
          var->init_value = std::string(list[2].toLocal8Bit().data());
          var->min_value = "";
          var->max_value = "";
          break;
        case 4: {
          memset(&m_coords, 0, sizeof(yd::COORDS));
          m_coords.ucCtrlType = 0;
          QStringList grouplist = list[2].split(',');
          for (int i = 0; i < grouplist.size(); ++i) {
            if (!grouplist[i].isEmpty()) {
              QStringList itemlist = grouplist[i].split('@');
              YDHelper::updateCoorData(m_coords.arrCoords[i], itemlist);
              m_coords.ucNumber = i + 1;
            }
          }

          std::string stdjson;
          yd::CRapidJsonHelper::AxisCoords2Json(&m_coords, stdjson);
          var->init_value = stdjson;
          var->min_value = "";
          var->max_value = "";
        } break;
      }

      YDLogger::info(MainWindow::tr("修改全局变量: %1 成功").arg(list[0]));
      m_variablModel->setGroupId(vg->groupId());
      YDProjectManage::UpdateGlobalVarValue(var->variable_id, var->init_value);
    }
  }
}

void MainWindow::slotUpdateReciVar() {
  if (m_addReciVarDlg->result() == QDialog::Accepted) {
    auto list = m_addReciVarDlg->textList();
    YDVariable *vg =
        reinterpret_cast<YDVariable *>(m_reciVarIndex.internalPointer());
    int row = m_reciViewIndex.row();
    auto vars = YDProjectManage::GetGroupedReciVars(vg->groupId());

    if (row < vars.size()) {
      auto var = vars[row];
      var->variable_name = std::string(list[0].toLocal8Bit().data());
      var->value_type = YDHelper::getDataTypeIndex(list[1]);
      int index = list[1].toUInt();

      switch (index) {
        case 0:
          var->init_value =
              (list[2] == "False" ? std::string("0") : std::string("1"));
          break;
        case 1:
        case 2:
          var->init_value = std::string(list[2].toLocal8Bit().data());
          var->min_value = std::string(list[3].toLocal8Bit().data());
          var->max_value = std::string(list[4].toLocal8Bit().data());
          break;
        case 3:
          var->init_value = std::string(list[2].toLocal8Bit().data());
          var->min_value = "";
          var->max_value = "";
          break;
        case 4: {
          memset(&m_coords, 0, sizeof(yd::COORDS));
          m_coords.ucCtrlType = 0;
          QStringList grouplist = list[2].split(',');
          for (int i = 0; i < grouplist.size(); ++i) {
            if (!grouplist[i].isEmpty()) {
              QStringList itemlist = grouplist[i].split('@');
              YDHelper::updateCoorData(m_coords.arrCoords[i], itemlist);
              m_coords.ucNumber = i + 1;
            }
          }

          std::string stdjson;
          yd::CRapidJsonHelper::AxisCoords2Json(&m_coords, stdjson);
          var->init_value = stdjson;
          var->min_value = "";
          var->max_value = "";
        } break;
      }
      YDLogger::info(MainWindow::tr("修改配方变量: %1 成功").arg(list[0]));
      m_reciVarModel->setGroupId(vg->groupId());
      YDProjectManage::UpdateReciVarValue(var->variable_id, var->init_value);
    }
  }
}

void MainWindow::slotUpdateTempVar() {
  if (m_addTempVarDlg->result() == QDialog::Accepted) {
    auto list = m_addTempVarDlg->textList();
    YDVariable *vg =
        reinterpret_cast<YDVariable *>(m_tempVarIndex.internalPointer());
    int row = m_tempViewIndex.row();
    auto vars = YDProjectManage::GetGroupedTempVars(vg->groupId());

    if (row < vars.size()) {
      auto var = vars[row];
      var->variable_name = std::string(list[0].toLocal8Bit().data());
      var->value_type = YDHelper::getDataTypeIndex(list[1]);
      int index = list[1].toUInt();

      switch (index) {
        case 0:
          var->init_value =
              (list[2] == "False" ? std::string("0") : std::string("1"));
          break;
        case 1:
        case 2:
          var->init_value = std::string(list[2].toLocal8Bit().data());
          var->min_value = std::string(list[3].toLocal8Bit().data());
          var->max_value = std::string(list[4].toLocal8Bit().data());
          break;
        case 3:
          var->init_value = std::string(list[2].toLocal8Bit().data());
          var->min_value = "";
          var->max_value = "";
          break;
        case 4: {
          memset(&m_coords, 0, sizeof(yd::COORDS));
          m_coords.ucCtrlType = 0;
          QStringList grouplist = list[2].split(',');
          for (int i = 0; i < grouplist.size(); ++i) {
            if (!grouplist[i].isEmpty()) {
              QStringList itemlist = grouplist[i].split('@');
              YDHelper::updateCoorData(m_coords.arrCoords[i], itemlist);
              m_coords.ucNumber = i + 1;
            }
          }

          std::string stdjson;
          yd::CRapidJsonHelper::AxisCoords2Json(&m_coords, stdjson);
          var->init_value = stdjson;
          var->min_value = "";
          var->max_value = "";
        } break;
      }
      YDLogger::info(MainWindow::tr("修改临时变量: %1 成功").arg(list[0]));
      m_tempVarModel->setGroupId(vg->groupId());
      YDProjectManage::UpdateTempVarValue(var->variable_id, var->init_value);
    }
  }
}

void MainWindow::on_addSafeVar_clicked() {
  if (m_addSafeVarDlg) delete m_addSafeVarDlg;
  m_addSafeVarDlg = new YDAddSafeVarDialog(this);
  m_addSafeVarDlg->setWindowTitle(YDAddSafeVarDialog::tr("添加安全变量"));
  connect(m_addSafeVarDlg, &YDAddSafeVarDialog::finished, this,
          &MainWindow::slotAddSafeVarFinished);
  m_addSafeVarDlg->open();
}

void MainWindow::slotAddSafeVarFinished() {
  if (m_addSafeVarDlg->result() == QDialog::Accepted) {
    auto list = m_addSafeVarDlg->textList();
    if (!list.isEmpty()) {
      yd::vr::SafeVariable *var = nullptr;
      YDVariable *subvg =
          reinterpret_cast<YDVariable *>(m_safeVarIndex.internalPointer());
      YDProjectManage::createSafeVariable(subvg->parent()->groupId(),
                                          subvg->groupId(), var);
      if (var) {
        var->variable_name = std::string(list[0].toLocal8Bit().data());
        var->logic_operator =
            (list[1].toUInt() == 0 ? LOGIC_OPERATOR_AND : LOGIC_OPERATOR_OR);
        auto datalist = list[2].split(";");
        m_selectSafeVar = var;
        for (auto c : m_selectSafeVar->listConditions)
          YDProjectManage::deleteSafeVariableCondition(
              m_selectSafeVar->variable_id, c->condition_id);
        m_selectSafeVar->listConditions.clear();
        int index = 0;
        for (const QString &s : datalist) {
          if (!s.isEmpty()) {
            yd::lg::Condition *condition = nullptr;
            YDProjectManage::createSafeVariableCondition(
                m_selectSafeVar->variable_id, condition);
            QStringList strlist = s.split("@");
            uint64 id = YDProjectManage::getVarId(strlist[0]);
            if (0 == id) continue;

            condition->parameter_id = id;
            condition->compare_operator = YDHelper::getCompareIndex(strlist[1]);
            condition->judge_value = QSTRTSTR(strlist[2]);
            condition->allow_error = strlist[3].toStdString();
            bool b = strlist[4] == YDModule::tr("是") ? true : false;
            condition->not_operator = b;
            condition->judge_order = ++index;
          }
        }
        YDLogger::info(MainWindow::tr("创建安全变量: %1 成功").arg(list[0]));
        updateSafeVarModel();
      }
    }
  }
}

void MainWindow::slotUpdateSafeVar() {
  if (m_addSafeVarDlg->result() == QDialog::Accepted) {
    auto list = m_addSafeVarDlg->textList();
    if (!list.isEmpty()) {
      if (m_selectSafeVar) {
        m_selectSafeVar->variable_name =
            std::string(list[0].toLocal8Bit().data());
        m_selectSafeVar->logic_operator =
            (list[1].toUInt() == 0 ? LOGIC_OPERATOR_AND : LOGIC_OPERATOR_OR);
        auto datalist = list[2].split(";");
        for (auto c : m_selectSafeVar->listConditions)
          YDProjectManage::deleteSafeVariableCondition(
              m_selectSafeVar->variable_id, c->condition_id);
        m_selectSafeVar->listConditions.clear();
        int index = 0;
        for (auto s : datalist) {
          if (!s.isEmpty()) {
            yd::lg::Condition *condition = nullptr;
            YDProjectManage::createSafeVariableCondition(
                m_selectSafeVar->variable_id, condition);
            QStringList strlist = s.split("@");
            uint64 id = YDProjectManage::getVarId(strlist[0]);
            if (0 == id) continue;

            condition->parameter_id = id;
            condition->compare_operator = YDHelper::getCompareIndex(strlist[1]);
            condition->judge_value = QSTRTSTR(strlist[2]);
            condition->allow_error = strlist[3].toStdString();
            bool b = strlist[4] == YDModule::tr("是") ? true : false;
            condition->not_operator = b;
            condition->judge_order = ++index;
          }
        }
        YDLogger::info(MainWindow::tr("修改安全变量: %1 成功").arg(list[0]));
        updateSafeVarModel();
      }
    }
  }
}

void MainWindow::on_GasAdd_clicked() {
  if (m_addCylinderDlg) delete m_addCylinderDlg;
  m_addCylinderDlg = new YDAddCylinderDialog(this);
  connect(m_addCylinderDlg, &YDAddCylinderDialog::finished, this,
          &MainWindow::slotAddCylinderFinished);
  m_addCylinderDlg->open();
}

void MainWindow::slotAddCylinderFinished() {
  if (m_addCylinderDlg->result() == QDialog::Accepted) {
    auto types = YDProjectManage::getPredefinedDeviceTypes();
    auto infos = m_addCylinderDlg->textList();
    int i = 0;
    for (; i < types.size(); ++i)
      if (types[i]->id == DEVICE_TYPE_ID_CYLINDER) break;

    auto type = types[i];
    std::string name = QSTRTSTR(infos[0]);
    yd::dev::Cylinder *cyl = nullptr;

    if (YDProjectManage::createCylinder(name, type, cyl)) {
      qDebug() << "Cylinder create sucessfule!";
      updateCylinderInfos(cyl, infos);
      ui->CylinderInfo->setTextList(infos);
      YDLogger::info(MainWindow::tr("创建气油缸: %1 成功").arg(infos[0]));
    }
  }
}

void MainWindow::slotChangeCylinderFinished() {
  if (m_addCylinderDlg->result() == QDialog::Accepted) {
    if (m_cylinderIndex.isValid()) {
      int row = m_cylinderIndex.row();
      auto list = YDProjectManage::getCylinders();
      auto cyl = list[row];
      auto infos = m_addCylinderDlg->textList();
      updateCylinderInfos(cyl, infos);
      ui->CylinderInfo->setTextList(infos);
      YDLogger::info(MainWindow::tr("修改气油缸: %1 成功").arg(infos[0]));
    }
  }
}

void MainWindow::slotCylinderItemSingleClick(const QModelIndex &index) {
  int row = index.row();
  auto list = YDProjectManage::getCylinders();
  if (row < list.size()) {
    m_cylinderIndex = index;
    auto cyl = list[row];
    QStringList infos = getCylinderInfos(cyl);
    ui->CylinderInfo->setTextList(infos);
  }
}

void MainWindow::slotCylinderItemDoubleClick(const QModelIndex &index) {
  int row = index.row();
  auto list = YDProjectManage::getCylinders();
  if (row < list.size()) {
    m_cylinderIndex = index;
    auto cyl = list[row];
    QStringList infos = getCylinderInfos(cyl);

    if (m_addCylinderDlg) delete m_addCylinderDlg;
    m_addCylinderDlg = new YDAddCylinderDialog(this);
    connect(m_addCylinderDlg, &QDialog::finished, this,
            &MainWindow::slotChangeCylinderFinished);
    m_addCylinderDlg->setTextList(infos);
    m_addCylinderDlg->open();
  }
}

void MainWindow::slotVarGroupClick(const QModelIndex &index) {
  m_varIndex = index;
  YDVariable *var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var) {
    if (var->parent() == YDProjectManage::getVarRoot()) {
      ui->addVar->setDisabled(true);
      ui->DelVar->setDisabled(true);
    } else if (!YDProjectManage::IsOnlineDebugOpened()) {
      ui->addVar->setDisabled(false);
      ui->DelVar->setDisabled(false);
    }

    m_variablModel->setGroupId(var->groupId());
  }
}

void MainWindow::slotReciVarGroupClick(const QModelIndex &index) {
  m_reciVarIndex = index;
  YDVariable *var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var) {
    if (var->parent() == YDProjectManage::getVarRoot()) {
      ui->addVar_2->setDisabled(true);
      ui->DelVa_2->setDisabled(true);
    } else if (!YDProjectManage::IsOnlineDebugOpened()) {
      ui->addVar_2->setDisabled(false);
      ui->DelVa_2->setDisabled(false);
    }

    m_reciVarModel->setGroupId(var->groupId());
  }
}

void MainWindow::slotTempVarGroupClick(const QModelIndex &index) {
  m_tempVarIndex = index;
  YDVariable *var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var) {
    if (var->parent() == YDProjectManage::getVarRoot()) {
      ui->addVar_4->setDisabled(true);
      ui->DelVar_4->setDisabled(true);
    } else if (!YDProjectManage::IsOnlineDebugOpened()) {
      ui->addVar_4->setDisabled(false);
      ui->DelVar_4->setDisabled(false);
    }

    m_tempVarModel->setGroupId(var->groupId());
  }
}

void MainWindow::slotVarGroupDoubleClick(const QModelIndex &) {}

void MainWindow::slotVarViewDoubleClick(const QModelIndex &index) {
  YDVariable *vg = reinterpret_cast<YDVariable *>(m_varIndex.internalPointer());
  int row = index.row();
  auto list = YDProjectManage::GetGroupedGlobalVars(vg->groupId());

  if (row < list.size()) {
    m_varViewIndex = index;
    auto var = list[row];
    QStringList infos;
    infos << STRTQSTR(var->variable_name);
    switch (var->value_type) {
      case DATA_TYPE_BOOL: {
        infos << "0";
        QString boolstr = (var->init_value == "0" ? "False" : "True");
        infos << boolstr;
      } break;
      case DATA_TYPE_INT8:
      case DATA_TYPE_UINT8:
      case DATA_TYPE_INT16:
      case DATA_TYPE_UINT16:
      case DATA_TYPE_INT32:
      case DATA_TYPE_UINT32:
      case DATA_TYPE_INT64:
      case DATA_TYPE_UINT64: {
        infos << "1";
        infos << STRTQSTR(var->init_value.c_str());
        infos << STRTQSTR(var->min_value.c_str());
        infos << STRTQSTR(var->max_value.c_str());
      } break;
      case DATA_TYPE_FLOAT:
      case DATA_TYPE_DOUBLE: {
        infos << "2";
        infos << STRTQSTR(var->init_value.c_str());
        infos << STRTQSTR(var->min_value.c_str());
        infos << STRTQSTR(var->max_value.c_str());
      } break;
      case DATA_TYPE_STRING: {
        infos << "3";
        infos << STRTQSTR(var->init_value.c_str());
      } break;
      case DATA_TYPE_AXIS_COORD: {
        infos << "4";
        memset(&m_coords, 0, sizeof(yd::COORDS));
        yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &m_coords);
        QString axstr;
        for (int i = 0; i < m_coords.ucNumber; ++i) {
          axstr += QString("%1,").arg(
              YDHelper::CoorData2QStr(m_coords.arrCoords[i]));
        }
        infos << axstr;
      } break;
      default:
        break;
    }

    if (m_addVarDlg) delete m_addVarDlg;
    m_addVarDlg = new YDAddVariableDialog(this);
    m_addVarDlg->setTextList(infos);
    connect(m_addVarDlg, &YDAddVariableDialog::finished, this,
            &MainWindow::slotUpdateVar);
    m_addVarDlg->setUpdateParam(m_varIndex, m_varViewIndex, true);
    m_addVarDlg->open();
  }
}

void MainWindow::slotReciVarViewDoubleClick(const QModelIndex &index) {
  YDVariable *vg =
      reinterpret_cast<YDVariable *>(m_reciVarIndex.internalPointer());
  int row = index.row();
  auto list = YDProjectManage::GetGroupedReciVars(vg->groupId());

  if (row < list.size()) {
    m_reciViewIndex = index;
    auto var = list[row];
    QStringList infos;
    infos << STRTQSTR(var->variable_name);
    switch (var->value_type) {
      case DATA_TYPE_BOOL: {
        infos << "0";
        QString boolstr = (var->current_value == "0" ? "False" : "True");
        infos << boolstr;
      } break;
      case DATA_TYPE_INT8:
      case DATA_TYPE_UINT8:
      case DATA_TYPE_INT16:
      case DATA_TYPE_UINT16:
      case DATA_TYPE_INT32:
      case DATA_TYPE_UINT32:
      case DATA_TYPE_INT64:
      case DATA_TYPE_UINT64: {
        infos << "1";
        infos << STRTQSTR(var->current_value.c_str());
        infos << STRTQSTR(var->min_value.c_str());
        infos << STRTQSTR(var->max_value.c_str());
      } break;
      case DATA_TYPE_FLOAT:
      case DATA_TYPE_DOUBLE: {
        infos << "2";
        infos << STRTQSTR(var->current_value.c_str());
        infos << STRTQSTR(var->min_value.c_str());
        infos << STRTQSTR(var->max_value.c_str());
      } break;
      case DATA_TYPE_STRING: {
        infos << "3";
        infos << STRTQSTR(var->current_value.c_str());
      } break;
      case DATA_TYPE_AXIS_COORD: {
        infos << "4";
        memset(&m_coords, 0, sizeof(yd::COORDS));
        yd::CRapidJsonHelper::Json2AxisCoords(var->current_value, &m_coords);
        QString axstr;
        for (int i = 0; i < m_coords.ucNumber; ++i) {
          axstr += QString("%1,").arg(
              YDHelper::CoorData2QStr(m_coords.arrCoords[i]));
        }
        infos << axstr;
      } break;
      default:
        break;
    }

    if (m_addReciVarDlg) delete m_addReciVarDlg;
    m_addReciVarDlg = new YDAddReciVarDialog(this);
    m_addReciVarDlg->setTextList(infos);
    connect(m_addReciVarDlg, &YDAddReciVarDialog::finished, this,
            &MainWindow::slotUpdateReciVar);
    m_addReciVarDlg->setUpdateParam(m_reciVarIndex, m_reciViewIndex, true);
    m_addReciVarDlg->open();
  }
}

void MainWindow::slotTempVarViewDoubleClick(const QModelIndex &index) {
  YDVariable *vg =
      reinterpret_cast<YDVariable *>(m_tempVarIndex.internalPointer());
  int row = index.row();
  auto list = YDProjectManage::GetGroupedTempVars(vg->groupId());

  if (row < list.size()) {
    m_tempViewIndex = index;
    auto var = list[row];
    QStringList infos;
    infos << STRTQSTR(var->variable_name);
    switch (var->value_type) {
      case DATA_TYPE_BOOL: {
        infos << "0";
        QString boolstr = (var->init_value == "0" ? "False" : "True");
        infos << boolstr;
      } break;
      case DATA_TYPE_INT8:
      case DATA_TYPE_UINT8:
      case DATA_TYPE_INT16:
      case DATA_TYPE_UINT16:
      case DATA_TYPE_INT32:
      case DATA_TYPE_UINT32:
      case DATA_TYPE_INT64:
      case DATA_TYPE_UINT64: {
        infos << "1";
        infos << STRTQSTR(var->init_value.c_str());
        infos << STRTQSTR(var->min_value.c_str());
        infos << STRTQSTR(var->max_value.c_str());
      } break;
      case DATA_TYPE_FLOAT:
      case DATA_TYPE_DOUBLE: {
        infos << "2";
        infos << STRTQSTR(var->init_value.c_str());
        infos << STRTQSTR(var->min_value.c_str());
        infos << STRTQSTR(var->max_value.c_str());
      } break;
      case DATA_TYPE_STRING: {
        infos << "3";
        infos << STRTQSTR(var->init_value.c_str());
      } break;
      case DATA_TYPE_AXIS_COORD: {
        infos << "4";
        memset(&m_coords, 0, sizeof(yd::COORDS));
        yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &m_coords);
        QString axstr;
        for (int i = 0; i < m_coords.ucNumber; ++i) {
          axstr += QString("%1,").arg(
              YDHelper::CoorData2QStr(m_coords.arrCoords[i]));
        }
        infos << axstr;
      } break;
      default:
        break;
    }

    if (m_addTempVarDlg) delete m_addTempVarDlg;
    m_addTempVarDlg = new YDAddTempVarDialog(this);
    m_addTempVarDlg->setTextList(infos);
    connect(m_addTempVarDlg, &YDAddTempVarDialog::finished, this,
            &MainWindow::slotUpdateTempVar);
    m_addTempVarDlg->setUpdateParam(m_tempVarIndex, m_tempViewIndex, true);
    m_addTempVarDlg->open();
  }
}

void MainWindow::slotSafeGroupClick(const QModelIndex &index) {
  m_safeVarIndex = index;
  YDVariable *var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var->parent() == YDProjectManage::getVarRoot()) {
    ui->addSafeVar->setDisabled(true);
    ui->DelSafeVar->setDisabled(true);
  } else if (!YDProjectManage::IsOnlineDebugOpened()) {
    ui->addSafeVar->setDisabled(false);
    ui->DelSafeVar->setDisabled(false);
  }

  m_safeVarModel->setGroupId(var->groupId());
}

void MainWindow::slotSafeGroupDoubleClick(const QModelIndex &index) {
  YDVariable *var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var) {
    m_safeVarModel->setGroupId(var->groupId());
  }
}

void MainWindow::slotSafeVarDoubleClick(const QModelIndex &index) {
  int row = index.row();
  YDVariable *vg =
      reinterpret_cast<YDVariable *>(m_safeVarIndex.internalPointer());
  std::vector<yd::vr::SafeVariable *> list;
  YDProjectManage::getGroupedSafeVariables(vg->groupId(), list);
  if (row < list.size()) {
    m_safeVarViewIndex = index;
    auto var = list[row];
    m_selectSafeVar = var;
    QStringList textList;
    textList << STRTQSTR(var->variable_name.c_str());
    textList << (var->logic_operator == LOGIC_OPERATOR_AND ? "0" : "1");

    auto condlist = var->listConditions;
    QString text;
    if (condlist.size() > 0) {
      for (auto c : condlist) {
        QString str;
        auto name = YDProjectManage::getVarName(c->parameter_id);
        if (name.isEmpty()) continue;
        str += QString("%1@").arg(name);
        str += QString("%1@").arg(YDHelper::getCompareStr(c->compare_operator));
        str += QString("%1@").arg(QString::fromStdString(c->judge_value));
        str += QString("%1@").arg(QString::fromStdString(c->allow_error));
        bool b = c->not_operator;
        str += QString("%1@").arg(b ? YDModule::tr("是") : YDModule::tr("否"));
        text += QString("%1;").arg(str);
      }
    }
    textList << text;

    if (m_addSafeVarDlg) delete m_addSafeVarDlg;
    m_addSafeVarDlg = new YDAddSafeVarDialog(this);
    m_addSafeVarDlg->setWindowTitle(YDAddSafeVarDialog::tr("修改安全变量"));
    m_addSafeVarDlg->setTextList(textList);
    connect(m_addSafeVarDlg, &YDAddSafeVarDialog::finished, this,
            &MainWindow::slotUpdateSafeVar);
    m_addSafeVarDlg->setUpdateParam(m_safeVarIndex, m_safeVarViewIndex, true);
    m_addSafeVarDlg->open();
  }
}

void MainWindow::slotDeviceSetDlgFinished() {}

void MainWindow::slotNetSetFinished() {
  if (m_netSetDlg->result() == QDialog::Accepted) {
    auto ip = m_netSetDlg->getIP();
    auto time = m_netSetDlg->getTime();
    uint16 port = m_netSetDlg->getPort().toUShort();

    YDProjectManage::SetDataGateway(QSTRTSTR(ip), port, time.toInt());
    YDLogger::info(
        MainWindow::tr("设置后台数据网关 地址: %1 端口: %2 超时时间: %3")
            .arg(ip, QString::number(port), time));
    //    if (m_debugDlg) delete m_debugDlg;
    //    m_debugDlg = new YDDebugDialog(this);
    //    connect(m_debugDlg, &QDialog::finished, this,
    //            &MainWindow::slotDialogFinished);

    //    YDProjectManage::setTabWNull();
    //    YDHelper::setDebugMode(true);
    //    YDLogger::info(MainWindow::tr("IP连接(%1)成功").arg(ip));
    //    m_debugDlg->open();
  }
}

void MainWindow::slotDialogFinished() {
  YDProjectManage::setTabWNull();
  YDHelper::setDebugMode(false);
  m_debugDlg->stopThread();
}

void MainWindow::slotCodeDiaFinish() {}

void MainWindow::slotCratePFinished() {
  if (QDialog::Accepted == m_createPDlg->result()) {
    YDProjectManage::closeProject();
    auto name = QSTRTSTR(m_createPDlg->getName());
    setBtnState(true);
    YDProjectManage::CreateProject(name);
    bool result = YDProjectManage::openProject(name);
    if (result) {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("新建项目:"),
                                           m_createPDlg->getName(),
                                           MainWindow::tr("成功!")));
      initOpenMenu();
    } else {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("新建项目:"),
                                           m_createPDlg->getName(),
                                           MainWindow::tr("失败!")));
    }
  }
}

void MainWindow::slotChangeNFinished() {
  if (QDialog::Accepted == m_changeDlg->result()) {
    auto name = QSTRTSTR(m_changeDlg->getName());
    bool result = YDProjectManage::renameProject(name);
    if (result) {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("重命名项目:"),
                                           m_changeDlg->getName(),
                                           MainWindow::tr("成功!")));
      initOpenMenu();
    } else {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("重命名项目:"),
                                           m_changeDlg->getName(),
                                           MainWindow::tr("失败!")));
    }
  }
}

void MainWindow::slotSaveasFinished() {
  if (QDialog::Accepted == m_saveasDlg->result()) {
    auto name = QSTRTSTR(m_saveasDlg->getName());
    bool result = YDProjectManage::saveProjectAs(name);
    if (result) {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("保存项目:"),
                                           m_saveasDlg->getName(),
                                           MainWindow::tr("成功!")));
      initOpenMenu();
    } else {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("保存项目:"),
                                           m_saveasDlg->getName(),
                                           MainWindow::tr("失败!")));
    }
  }
}

void MainWindow::slotActionTriggered(bool) {
  QAction *ac = qobject_cast<QAction *>(sender());
  auto name = QSTRTSTR(ac->text());
  YDProjectManage::closeProject();
  setBtnState(true);
  bool result = YDProjectManage::openProject(name);

  if (result) {
    YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("打开项目:"),
                                         ac->text(), MainWindow::tr("成功.")));
    initOpenMenu();
  } else {
    YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("打开项目:"),
                                         ac->text(), MainWindow::tr("失败.")));
  }
}

void MainWindow::slotWayActionTriggered(bool) {
  QAction *ac = qobject_cast<QAction *>(sender());
  auto name = QSTRTSTR(ac->text());
  bool result = YDProjectManage::openRecipe(name);
  if (result) {
    YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("打开配方:"),
                                         ac->text(), MainWindow::tr("成功.")));

    initReciWidget();
    initOpenWayMenu();
    m_reciVarModel->updateData();
  } else {
    YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("打开配方:"),
                                         ac->text(), MainWindow::tr("失败.")));
  }
}

void MainWindow::slotDelActionTriggered(bool) {
  QAction *ac = qobject_cast<QAction *>(sender());
  auto name = QSTRTSTR(ac->text());
  auto rb = QMessageBox::information(
      this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
      MainWindow::tr("确认"), MainWindow::tr("取消"));

  if (0 == rb) {
    bool result = YDProjectManage::deleteProject(name);
    if (result) {
      YDLogger::info(QString("%1%2%3").arg(
          MainWindow::tr("删除项目:"), ac->text(), MainWindow::tr("成功.")));
      initOpenMenu();
    } else {
      YDLogger::info(QString("%1%2%3").arg(
          MainWindow::tr("删除项目:"), ac->text(), MainWindow::tr("失败.")));
    }
  }
}

void MainWindow::slotDelWayActionTriggered(bool) {
  QAction *ac = qobject_cast<QAction *>(sender());
  auto name = QSTRTSTR(ac->text());
  auto rb = QMessageBox::information(
      this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
      MainWindow::tr("确认"), MainWindow::tr("取消"));

  if (0 == rb) {
    bool result = YDProjectManage::deleteRecipe(name);
    if (result) {
      YDLogger::info(QString("%1%2%3").arg(
          MainWindow::tr("删除配方:"), ac->text(), MainWindow::tr("成功.")));
      initOpenWayMenu();
    } else {
      YDLogger::info(QString("%1%2%3").arg(
          MainWindow::tr("删除配方:"), ac->text(), MainWindow::tr("失败.")));
    }
  }
}

void MainWindow::slotCreateReciFinished() {
  if (QDialog::Accepted == m_createReciDlg->result()) {
    auto name = QSTRTSTR(m_createReciDlg->getName());
    YDProjectManage::createRecipe(name);
    bool result = YDProjectManage::openRecipe(name);
    if (result) {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("新建配方:"),
                                           m_createReciDlg->getName(),
                                           MainWindow::tr("成功.")));
      initOpenMenu();
    } else {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("新建配方:"),
                                           m_createReciDlg->getName(),
                                           MainWindow::tr("失败.")));
    }
  }
}

void MainWindow::slotChangeReciFinished() {
  if (QDialog::Accepted == m_changeReciDlg->result()) {
    auto name = QSTRTSTR(m_changeReciDlg->getName());
    bool result = YDProjectManage::renameRecipe(name);
    if (result) {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("重命名配方:"),
                                           m_changeReciDlg->getName(),
                                           MainWindow::tr("成功.")));

      initOpenWayMenu();
    } else {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("重命名配方:"),
                                           m_changeReciDlg->getName(),
                                           MainWindow::tr("失败.")));
    }
  }
}

void MainWindow::slotSaveasReciFinished() {
  if (QDialog::Accepted == m_saveasReciDlg->result()) {
    auto name = QSTRTSTR(m_saveasReciDlg->getName());
    bool result = YDProjectManage::saveRecipeAs(name);
    if (result) {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("另存为配方:"),
                                           m_saveasReciDlg->getName(),
                                           MainWindow::tr("成功.")));
      initOpenWayMenu();
    } else {
      YDLogger::info(QString("%1%2%3").arg(MainWindow::tr("另存为配方:"),
                                           m_saveasReciDlg->getName(),
                                           MainWindow::tr("失败.")));
    }
  }
}

void MainWindow::slotDebugTrigger(bool) {}

void MainWindow::slotBPDialogFinished() {
  if (QDialog::Accepted == m_backPDlg->result()) {
    auto type = m_backPDlg->getType();
    YDProjectManage::SetHomeMoveScriptType(type);
    m_bpCodeManage->resize(1400, 900);
    m_bpCodeManage->setScript();
    m_bpCodeManage->open();
  }
}

void MainWindow::slotTabClosed() {
  if (m_curTabIndex >= 0) {
    ui->tabWidget->tabBar()->setTabButton(m_curTabIndex, QTabBar::RightSide,
                                          nullptr);
    m_curTabIndex = m_curTabIndex + 1;
    ui->tabWidget->removeTab(m_curTabIndex - 1);
  }
}

void MainWindow::slotDebugFinished() { m_debugWindowType = -1; }

void MainWindow::showHardConfig() {
  if (YDProjectManage::IsOnlineDebugOpened()) {
    m_deviceSetDlg->setControlEnabled(false);
  } else {
    m_deviceSetDlg->setControlEnabled(true);
  }
  m_deviceSetDlg->open();
}

void MainWindow::showVarConfig(int type) {
  switch (type) {
    case 0:
      ui->VarDock->raise();
      break;
    case 1:
      ui->PeiFVarDock->raise();
      break;
    case 2:
      ui->TempVarDock->raise();
      break;
    case 3:
      ui->SafeVarDock->raise();
      break;
    default:
      break;
  }
}

void MainWindow::showZeroScript(int type) {
  switch (type) {
    case 0: {
      auto type = YDProjectManage::GetHomeMoveScriptType();
      m_backPDlg->setType(type);
      m_backPDlg->open();
    } break;
    default:
      break;
  }
}

void MainWindow::slotScriptMenu(const QPoint &pos) {
  QModelIndex curIndex = m_scriptView->indexAt(pos);
  if (curIndex.isValid()) {
    m_scriptMenu2->exec(QCursor::pos());
  } else {
    m_scriptMenu1->exec(QCursor::pos());
  }
}

void MainWindow::slotAddScript(bool) {
  m_scriptProp->setAddOrUpdate(true);
  m_scriptProp->open();
}

void MainWindow::slotEditScriptProp(bool) {
  auto index = m_scriptView->currentIndex();
  if (index.isValid()) {
    auto list = YDProjectManage::getScripts();
    auto script = list[index.row()];
    m_scriptProp->setScritp(script);
    m_scriptProp->setAddOrUpdate(false);
    m_scriptProp->open();
  }
}

void MainWindow::slotRemoveScript(bool) {
  auto index = m_scriptView->currentIndex();
  if (index.isValid()) {
    auto list = YDProjectManage::getScripts();
    auto script = list[index.row()];
    auto rb = QMessageBox::information(
        this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
        MainWindow::tr("确认"), MainWindow::tr("取消"));
    if (0 == rb) {
      YDProjectManage::deleteScript(script->script_name);
      YDLogger::info(MainWindow::tr("删除脚本: %1 成功")
                         .arg(STRTQSTR(script->script_name)));
    }
  }
}

void MainWindow::slotScriptItemClicked(const QModelIndex &index) {
  m_scriptIndex = index;
  auto list = YDProjectManage::getScripts();
  auto script = list[index.row()];
  m_codeManage->setScript(script);
  m_codeManage->setWindowTitle("自定义脚本 - " + STRTQSTR(script->script_name));
  m_codeManage->open();
}

void MainWindow::slotScriptItemDBClicked(const QModelIndex &) {
  //  auto list = YDProjectManage::getScripts();
  //  auto script = list[index.row()];
  //  m_scriptProp->setScritp(script);
  //  m_scriptProp->open();
}

void MainWindow::slotScriptPropClose() { m_scriptModel->updatedata(); }

void MainWindow::showCusModule(int type) {
  switch (type) {
    case 0:
      ui->CylinderDock->raise();
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    default:
      break;
  }
}

void MainWindow::slotWidgetAction(bool b) {
  QAction *ac = qobject_cast<QAction *>(sender());

  if (ui->a_wpromg == ac) {
    if (b) {
      ui->MenuDock->show();
    } else {
      ui->MenuDock->hide();
    }
  } else if (ui->a_property == ac) {
    if (b) {
      ui->PropertyDock->show();
    } else {
      ui->PropertyDock->hide();
    }
  } else if (ui->a_wgbvar == ac) {
    if (b) {
      ui->VarDock->show();
    } else {
      ui->VarDock->hide();
    }
  } else if (ui->a_wwyvar == ac) {
    if (b) {
      ui->PeiFVarDock->show();
    } else {
      ui->PeiFVarDock->hide();
    }
  } else if (ui->a_wtpvar == ac) {
    if (b) {
      ui->TempVarDock->show();
    } else {
      ui->TempVarDock->hide();
    }
  } else if (ui->a_wsfvar == ac) {
    if (b) {
      ui->SafeVarDock->show();
    } else {
      ui->SafeVarDock->hide();
    }
  } else if (ui->a_wcylinder == ac) {
    if (b) {
      ui->CylinderDock->show();
    } else {
      ui->CylinderDock->hide();
    }
  } else if (ui->a_wfeida == ac) {
    if (b) {
    } else {
    }
  } else if (ui->a_wtrayp == ac) {
    if (b) {
    } else {
    }
  } else if (ui->a_wdanjia == ac) {
    if (b) {
    } else {
    }
  } else if (ui->a_logOut == ac) {
    if (b) {
      ui->InputDock->show();
    } else {
      ui->InputDock->hide();
    }
  } else if (ui->a_debugInfo == ac) {
    if (b) {
      ui->DebugDock->show();
    } else {
      ui->DebugDock->hide();
    }
  }
}

/**
 * @brief 运动监控子项显示
 */
void MainWindow::showMotionMonitoring(int type) {
  if (YDHelper::isDebugMode() && judgeAxisEnabled()) {
    m_debugWindowType = type;
    switch (type) {
      case 0: {  //轴控制
        if (m_axisWidget) delete m_axisWidget;
        m_axisWidget = new YDDAxisControl(this);
        m_axisWidget->setWindowFlags(Qt::Dialog);
        m_axisWidget->setWindowModality(Qt::ApplicationModal);
        m_axisWidget->resize(1100, 760);
        connect(m_axisWidget, &YDDAxisControl::finished, this,
                &MainWindow::slotDebugFinished);
        m_axisWidget->open();
      } break;

      case 1: {  //气油缸控制
        if (m_cylinderWidget) delete m_cylinderWidget;
        m_cylinderWidget = new YDDCylinderWidget(this);
        m_cylinderWidget->setWindowFlags(Qt::Dialog);
        m_cylinderWidget->setWindowModality(Qt::ApplicationModal);
        m_cylinderWidget->resize(1100, 760);
        connect(m_cylinderWidget, &YDDCylinderWidget::toclose, this,
                &MainWindow::slotDebugFinished);
        m_cylinderWidget->show();
      } break;

      case 2: {  //输入状态
        if (m_inputWidget) delete m_inputWidget;
        m_inputWidget = new YDDInputWidget(this);
        m_inputWidget->setWindowFlags(Qt::Dialog);
        m_inputWidget->setWindowModality(Qt::ApplicationModal);
        m_inputWidget->resize(1100, 760);
        connect(m_inputWidget, &YDDInputWidget::toclose, this,
                &MainWindow::slotDebugFinished);
        m_inputWidget->show();
      } break;

      case 3: {  //输出状态
        if (m_outputWidget) delete m_outputWidget;
        m_outputWidget = new YDDOutputWidget(this);
        m_outputWidget->setWindowFlags(Qt::Dialog);
        m_outputWidget->setWindowModality(Qt::ApplicationModal);
        m_outputWidget->resize(1100, 760);
        connect(m_outputWidget, &YDDOutputWidget::toclose, this,
                &MainWindow::slotDebugFinished);
        m_outputWidget->show();
      } break;
      case 4: {
        if (m_varWidget) delete m_varWidget;
        m_varWidget = new YDDVarWidget(this);
        m_varWidget->setWindowFlags(Qt::Dialog);
        m_varWidget->setWindowModality(Qt::ApplicationModal);
        m_varWidget->resize(1300, 760);
        connect(m_varWidget, &YDDVarWidget::finished, this,
                &MainWindow::slotDebugFinished);
        m_varWidget->open();
      } break;
      default:
        break;
    }
  }
}

void MainWindow::slotTabChanged(int index) {
  QCoreApplication::removePostedEvents(m_tabButton);
  if (!YDHelper::getTestStart()) {
    if (index >= 0 && (m_curTabIndex != index)) {
      auto tabwb = ui->tabWidget->tabBar();
      auto count = ui->tabWidget->count();
      if (m_curTabIndex >= 0 && (m_curTabIndex < count))
        tabwb->setTabButton(m_curTabIndex, QTabBar::RightSide, nullptr);
      tabwb->setTabButton(index, QTabBar::RightSide, m_tabButton);
    }
    m_curTabIndex = index;
  }
}

//菜单栏

void MainWindow::on_a_new_triggered() {
  m_createPDlg->clear();
  m_createPDlg->setWindowTitle(YDNameDialog::tr("新建项目"));
  m_createPDlg->open();
}

void MainWindow::on_a_close_triggered() {
  bool result = YDProjectManage::closeProject();
  if (result) {
    YDLogger::info(MainWindow::tr("关闭项目成功."));

    setBtnState(false);
    ui->a_new->setEnabled(true);
    ui->a_open->setEnabled(true);

    initOpenMenu();
  } else {
    YDLogger::info(MainWindow::tr("关闭项目失败."));
  }
}

void MainWindow::on_a_rename_triggered() {
  m_changeDlg->clear();
  m_changeDlg->setWindowTitle(YDNameDialog::tr("重命名项目"));
  m_changeDlg->open();
}

void MainWindow::on_a_save_triggered() {
  setFocus();
  YDProjectManage::saveProject();
  // screenShot();
}

void MainWindow::on_a_saveall_triggered() {
  setFocus();
  YDProjectManage::saveProject();
}

void MainWindow::on_a_saveoth_triggered() {
  m_saveasDlg->setWindowTitle(YDNameDialog::tr("项目另存为"));
  m_saveasDlg->open();
}

void MainWindow::on_a_exit_triggered() { exit(0); }

void MainWindow::on_a_newway_triggered() {
  m_createReciDlg->open();
  m_createReciDlg->setWindowTitle(YDNameDialog::tr("新建配方"));
  initReciWidget();
}

void MainWindow::on_a_changeWay_triggered() {
  m_changeReciDlg->open();
  m_changeReciDlg->setWindowTitle(YDNameDialog::tr("重命名配方"));
}

void MainWindow::on_a_saveway_triggered() {
  m_saveasReciDlg->open();
  m_saveasReciDlg->setWindowTitle(YDNameDialog::tr("配方另存为"));
}

void MainWindow::on_a_saveow_triggered() {
  bool result = YDProjectManage::saveRecipe();
  if (result) {
    YDLogger::info(MainWindow::tr("保存配方成功."));
    initOpenMenu();
  } else {
    YDLogger::info(MainWindow::tr("保存配方失败."));
  }
}

void MainWindow::on_a_dupload_triggered() {}

void MainWindow::on_a_ddownload_triggered() {}

void MainWindow::on_a_dstartz_triggered() { YDDgHelper::ExecuteHomeMove(); }

void MainWindow::on_a_dstartm_triggered() { YDDgHelper::StartMainLogicTask(); }

void MainWindow::on_a_dpausem_triggered() {
  YDDgHelper::SuspendMainLogicTask();
}

void MainWindow::on_a_dstopm_triggered() { YDDgHelper::StopMainLogicTask(); }

void MainWindow::on_a_ttalkset_triggered() { m_netSetDlg->open(); }

void MainWindow::on_DelVar_clicked() {
  YDVariable *vg = reinterpret_cast<YDVariable *>(m_varIndex.internalPointer());
  auto index = ui->VarView->currentIndex();
  if (index.isValid()) {
    int row = index.row();
    auto list = YDProjectManage::GetGroupedGlobalVars(vg->groupId());

    if (row < list.size()) {
      auto var = list[row];
      auto rb = QMessageBox::information(
          this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
          MainWindow::tr("确认"), MainWindow::tr("取消"));

      if (0 == rb) {
        if (YDProjectManage::DeleteGlobalVar(var->variable_id))
          YDLogger::info(MainWindow::tr("删除全局变量: %1 成功")
                             .arg(STRTQSTR(var->variable_name.c_str())));

        m_variablModel->setGroupId(vg->groupId());
      }
    }
  } else {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("请选择要删除的变量!"));
  }
}

void MainWindow::on_DelSafeVar_clicked() {
  YDVariable *vg =
      reinterpret_cast<YDVariable *>(m_safeVarIndex.internalPointer());
  auto index = ui->SafeVarView->currentIndex();
  if (index.isValid()) {
    int row = index.row();
    auto list = YDProjectManage::getGroupedSafeVariables(vg->groupId());

    if (row < list.size()) {
      auto var = list[row];
      auto rb = QMessageBox::information(
          this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
          MainWindow::tr("确认"), MainWindow::tr("取消"));

      if (0 == rb) {
        if (YDProjectManage::DeleteSafeVar(var->variable_id))
          YDLogger::info(MainWindow::tr("删除安全变量: %1 成功")
                             .arg(STRTQSTR(var->variable_name.c_str())));
        m_safeVarModel->setGroupId(vg->groupId());
      }
    }
  } else {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("请选择要删除的变量!"));
  }
}

void MainWindow::on_DelVa_2_clicked() {
  YDVariable *vg =
      reinterpret_cast<YDVariable *>(m_reciVarIndex.internalPointer());
  auto index = ui->VarView_2->currentIndex();
  if (index.isValid()) {
    int row = index.row();
    auto list = YDProjectManage::GetGroupedReciVars(vg->groupId());

    if (row < list.size()) {
      auto var = list[row];
      auto rb = QMessageBox::information(
          this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
          MainWindow::tr("确认"), MainWindow::tr("取消"));

      if (0 == rb) {
        if (YDProjectManage::DeleteReciVar(var->variable_id))
          YDLogger::info(MainWindow::tr("删除配方变量: %1 成功")
                             .arg(STRTQSTR(var->variable_name.c_str())));
        m_reciVarModel->setGroupId(vg->groupId());
      }
    }
  } else {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("请选择要删除的变量!"));
  }
}

void MainWindow::on_DelVar_4_clicked() {
  YDVariable *vg =
      reinterpret_cast<YDVariable *>(m_tempVarIndex.internalPointer());
  auto index = ui->VarView_4->currentIndex();
  if (index.isValid()) {
    int row = index.row();
    auto list = YDProjectManage::GetGroupedTempVars(vg->groupId());

    if (row < list.size()) {
      auto var = list[row];
      auto rb = QMessageBox::information(
          this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
          MainWindow::tr("确认"), MainWindow::tr("取消"));

      if (0 == rb) {
        if (YDProjectManage::DeleteTempVar(var->variable_id))
          YDLogger::info(MainWindow::tr("删除临时变量"
                                        ": %1 成功")
                             .arg(STRTQSTR(var->variable_name.c_str())));
        m_tempVarModel->setGroupId(vg->groupId());
      }
    }
  } else {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("请选择要删除的变量!"));
  }
}

/**
 * @brief 启动调试
 */
void MainWindow::on_a_startDebug_triggered() {
  if (judgeNetWorkEmpty()) {
    return;
  }
  ui->a_doldebug->setChecked(true);
  ui->a_startDebug->setEnabled(false);
  ui->a_closeDebug->setEnabled(true);
  initDebugActionEnable(true);
  YDProjectManage::OpenOnlineDebug(true);
  YDLogger::info(MainWindow::tr("启动在线调试."));
  emit start();
}

void MainWindow::on_a_closeDebug_triggered() {
  ui->a_doldebug->setChecked(false);
  ui->a_startDebug->setEnabled(true);
  ui->a_closeDebug->setEnabled(false);
  initDebugActionEnable(false);
  YDProjectManage::OpenOnlineDebug(false);
  if (YDDgHelper::Disconnect()) YDLogger::info(MainWindow::tr("关闭在线调试."));
  emit stop();
}

/**
 * @brief 在线调试
 * @param checked
 */
void MainWindow::on_a_doldebug_triggered(bool checked) {
  if (judgeNetWorkEmpty()) {
    ui->a_doldebug->setChecked(false);
    return;
  }
  initDebugActionEnable(checked);
  YDProjectManage::OpenOnlineDebug(checked);
  if (checked) {
    ui->a_startDebug->setEnabled(false);
    ui->a_closeDebug->setEnabled(true);
    YDLogger::info(MainWindow::tr("启动在线调试."));
    emit start();
  } else {
    ui->a_startDebug->setEnabled(true);
    ui->a_closeDebug->setEnabled(false);
    YDLogger::info(MainWindow::tr("关闭在线调试."));
    emit stop();
  }
}

void MainWindow::on_a_LogicStart_triggered() {
  //  ui->a_LogicStart->setEnabled(false);
  //  ui->a_LogicStop->setEnabled(true);
  uint8 ucStatus = 0, ucMode = 0;
  YDDgHelper::getLogicControllerStatus(ucStatus, ucMode);

  switch (ucStatus) {
    case SYSTEM_STATUS_RUNNING:
    case SYSTEM_STATUS_RESTORED:
      break;
    case SYSTEM_STATUS_STOPED:
      QMessageBox::information(nullptr, MainWindow::tr("提示"),
                               MainWindow::tr("服务器状态:已停止"));
      return;
    case SYSTEM_STATUS_SUSPENDED:
      QMessageBox::information(nullptr, MainWindow::tr("提示"),
                               MainWindow::tr("服务器状态:已挂起"));
      return;
    default:
      QMessageBox::information(nullptr, MainWindow::tr("提示"),
                               MainWindow::tr("服务器状态:未知"));
      return;
  }
  m_logicStart->setEnabled(false);
  m_logicStop->setEnabled(true);

  YDHelper::setTestStart(true);
  m_isLogicTaskStart = true;
  auto index = ui->tabWidget->currentIndex();
  if (index >= 0) {
    auto w = static_cast<YDTabWidget *>(ui->tabWidget->widget(index));
    YDTask *o = w->getTask();
    if (o) {
      std::string xmlstr;
      m_taskId = o->id();

      updateTaskData();
      emit updateTask(1000, m_taskId);
      YDProjectManage::getTaskXmlizedProcesses(m_taskId, xmlstr);
      YDDgHelper::startLogicTaskDebug(m_taskId, xmlstr);
    }
  }
}

void MainWindow::on_a_LogicStop_triggered() {
  //  ui->a_LogicStart->setEnabled(true);
  //  ui->a_LogicStop->setEnabled(false);
  m_logicStart->setEnabled(true);
  m_logicStop->setEnabled(false);
  YDHelper::setTestStart(false);

  m_isLogicTaskStart = false;
  YDDgHelper::stopLogicTaskDebug(m_taskId);
}

void MainWindow::SlotTimingSave() {
  YDLogger::info(QObject::tr("自动保存中!"));
  YDProjectManage::saveProject();
}

void MainWindow::SlotTaskState(quint8 state) {
  if (m_isLogicTaskStart) {
    if (YDProjectManage::IsOnlineDebugOpened()) {
      if (state != DEBUG_STATE_IN_PROCESSING && state != DEBUG_STATE_STOPPED) {
        emit stopTask();
        on_a_LogicStop_triggered();
      }
    } else {
      emit stopTask();
    }
  }
}

void MainWindow::on_a_notSave_triggered() {
  setSelectTime(0);
  emit stopTiming();
  YDLogger::info(MainWindow::tr("关闭定时保存."));
}

void MainWindow::on_a_save5_triggered() {
  setSelectTime(1);
  emit updateTiming(5 * 60 * 1000);
  YDLogger::info(MainWindow::tr("打开定时保存:5分钟."));
}

void MainWindow::on_a_save10_triggered() {
  setSelectTime(2);
  emit updateTiming(10 * 60 * 1000);
  YDLogger::info(MainWindow::tr("打开定时保存:10分钟."));
}

void MainWindow::on_a_save20_triggered() {
  setSelectTime(3);
  emit updateTiming(20 * 60 * 1000);
  YDLogger::info(MainWindow::tr("打开定时保存:20分钟."));
}

void MainWindow::on_a_save30_triggered() {
  setSelectTime(4);
  emit updateTiming(30 * 60 * 1000);
  YDLogger::info(MainWindow::tr("关闭定时保存:30分钟."));
}

void MainWindow::on_a_habout_triggered() { m_aboutDlg->open(); }

void MainWindow::on_m_save_triggered() {
  setFocus();
  YDProjectManage::saveProject();
}

void MainWindow::on_GasDel_clicked() {
  if (m_cylinderIndex.isValid()) {
    auto rb = QMessageBox::information(
        this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
        MainWindow::tr("确认"), MainWindow::tr("取消"));
    if (0 == rb) {
      QMap map = m_cylinderModel->itemData(m_cylinderIndex);
      QVariant tmpName = map.begin().value();
      YDProjectManage::deleteCylinder(QSTRTSTR(tmpName.toString()));
      m_cylinderModel->updateModel();
    }
  } else {
    QMessageBox::warning(nullptr, MainWindow::tr("提示"),
                         MainWindow::tr("请选择要删除的气油缸!"));
  }
}
