#include "MainWindow.h"

#include <QAbstractItemView>
#include <QAction>
#include <QDebug>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>

#include "RapidJsonHelper.h"
#include "common/YDHelper.h"
#include "common/YDLogger.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "core/YDVariable.h"
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
#include "widget/YDCodeManage.h"
#include "widget/YDDeviceSetDialog.h"
#include "widget/YDMenu.h"
#include "widget/YDMenuHead.h"
#include "widget/YDMenuItem.h"
#include "widget/YDNameDialog.h"
#include "widget/YDScriptPropDialog.h"
#include "widget/YDShowMessage.h"
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
      m_infoDlg{new YDShowMessage(this)} {
  ui->setupUi(this);
  m_menuModel = new YDMenuModel(YDProjectManage::getYDTaskRoot(), this);

  m_varGroupModel =
      new YDVariableGroupModel(YDProjectManage::getVarRoot(), this);

  YDHelper::setMainW(this);
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

void MainWindow::slotRemoveVarGroup(bool) {
  auto rb = QMessageBox::information(
      this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
      MainWindow::tr("确认"), MainWindow::tr("取消"));
  if (0 == rb) {
    m_varGroupModel->removeTree(m_varIndex);
    m_varIndex = QModelIndex();
    ui->VarGroupView->setCurrentIndex(m_varIndex);
  }
}

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

void MainWindow::slotRemoveSafeVarGroup(bool) {
  auto rb = QMessageBox::information(
      this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
      MainWindow::tr("确认"), MainWindow::tr("取消"));

  if (0 == rb) {
    m_varGroupModel->removeTree(m_safeVarIndex);
    m_safeVarIndex = QModelIndex();
    ui->SafeGroupView->setCurrentIndex(m_safeVarIndex);
  }
}

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

void MainWindow::slotRemoveReciVarGroup(bool) {
  auto rb = QMessageBox::information(
      this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
      MainWindow::tr("确认"), MainWindow::tr("取消"));

  if (0 == rb) {
    m_varGroupModel->removeTree(m_reciVarIndex);
    m_reciVarIndex = QModelIndex();
    ui->VarGroupView_2->setCurrentIndex(m_reciVarIndex);
  }
}

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

void MainWindow::slotRemoveTempVarGroup(bool) {
  auto rb = QMessageBox::information(
      this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
      MainWindow::tr("确认"), MainWindow::tr("取消"));

  if (0 == rb) {
    m_varGroupModel->removeTree(m_tempVarIndex);
    m_tempVarIndex = QModelIndex();
    ui->VarGroupView_4->setCurrentIndex(m_tempVarIndex);
  }
}

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
  m_varGroupModel->removeTree(m_varIndex);
  m_varIndex = QModelIndex();
  ui->VarGroupView->setCurrentIndex(m_varIndex);
}

void MainWindow::on_AddSafeVarG_clicked() {
  m_varGroupModel->addTree(m_safeVarIndex);
  ui->SafeGroupView->expand(m_safeVarIndex);
}

void MainWindow::on_DelSafeVarG_clicked() {
  m_varGroupModel->removeTree(m_safeVarIndex);
  m_safeVarIndex = QModelIndex();
  ui->SafeGroupView->setCurrentIndex(m_safeVarIndex);
}

void MainWindow::on_AddVarG_2_clicked() {
  m_varGroupModel->addTree(m_reciVarIndex);
  ui->VarGroupView_2->expand(m_reciVarIndex);
}

void MainWindow::on_DelVarG_2_clicked() {
  m_varGroupModel->removeTree(m_reciVarIndex);
  m_reciVarIndex = QModelIndex();
  ui->VarGroupView_2->setCurrentIndex(m_reciVarIndex);
}

void MainWindow::on_AddVarG_4_clicked() {
  m_varGroupModel->addTree(m_tempVarIndex);
  ui->VarGroupView_4->expand(m_tempVarIndex);
}

void MainWindow::on_DelVarG_4_clicked() {
  m_varGroupModel->removeTree(m_tempVarIndex);
  m_tempVarIndex = QModelIndex();
  ui->VarGroupView_4->setCurrentIndex(m_tempVarIndex);
}

void MainWindow::slotTaskItemClick(const QModelIndex &index) {
  m_taskIndex = index;
}

void MainWindow::slotTaskItemDoubleClick(const QModelIndex &index) {
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
  tabW->addTab(w, name);
  tabW->setCurrentWidget(w);
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
  t->setAlternatingRowColors(true);
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

  ui->VarView_2->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);

  ui->VarView_4->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->VarView_4->setModel(m_tempVarModel);

  ui->SafeVarView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->SafeVarView->setModel(m_safeVarModel);

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
  ui->addSafeVar->setDisabled(true);

  ui->AddVarG_2->setDisabled(true);
  ui->DelVarG_2->setDisabled(true);

  ui->addVar_2->setDisabled(true);
  ui->addVar_4->setDisabled(true);

  m_codeManage->resize(1744, 970);
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
    auto str = QString::fromLocal8Bit(v.c_str());
    if (str == name) continue;
    auto a = m->addAction(str);
    connect(a, &QAction::triggered, this, &MainWindow::slotActionTriggered);

    auto b = dm->addAction(str);
    connect(b, &QAction::triggered, this, &MainWindow::slotDelActionTriggered);
    m_files.push_back(a);
    m_delFiles.push_back(b);
  }

  updateProjectName();
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
    auto str = QString::fromLocal8Bit(v.c_str());
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
    ui->VarGroupView_2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->VarGroupView_2, &QTreeView::customContextMenuRequested, this,
            &MainWindow::slotReciVarMenu);

    ui->AddVarG_2->setEnabled(true);
    ui->DelVarG_2->setEnabled(true);
  }
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
      if (QString::fromLocal8Bit(v->io_name.c_str()) == infos[4]) {
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
      auto name = QString::fromLocal8Bit(v->io_name.c_str());
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
      if (QString::fromLocal8Bit(v->axis_name.c_str()) == infos[index + 1]) {
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
      if (QString::fromLocal8Bit(v->io_name.c_str()) == infos[index + 1]) {
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
      if (QString::fromLocal8Bit(v->axis_name.c_str()) == infos[index + 1]) {
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
      if (QString::fromLocal8Bit(v->io_name.c_str()) == infos[index + 1]) {
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
  infos << QString::fromLocal8Bit(cyl->base.name.c_str());
  infos << QString::fromLocal8Bit(cyl->direction1_name.c_str());
  infos << QString::fromLocal8Bit(cyl->direction2_name.c_str());
  if ((cyl->direction1_control.refer_device_id ==
       cyl->direction2_control.refer_device_id) &&
      (cyl->direction1_control.refer_index ==
       cyl->direction2_control.refer_index)) {
    infos << "single";
    QString doName;
    for (auto d : DOVars) {
      if (d->device_id == cyl->direction1_control.refer_device_id &&
          d->io_index == cyl->direction1_control.refer_index) {
        doName = QString::fromLocal8Bit(d->io_name.c_str());
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
        doName1 = QString::fromLocal8Bit(d->io_name.c_str());
        break;
      }
    }
    infos << doName1;

    QString doName2;
    for (auto d : DOVars) {
      if (d->device_id == cyl->direction2_control.refer_device_id &&
          d->io_index == cyl->direction2_control.refer_index) {
        doName2 = QString::fromLocal8Bit(d->io_name.c_str());
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
          diName = QString::fromLocal8Bit(d->io_name.c_str());
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
          diName = QString::fromLocal8Bit(d->io_name.c_str());
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
          axName = QString::fromLocal8Bit(ax->axis_name);
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
          diname = QString::fromLocal8Bit(d->io_name.c_str());
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
          diname = QString::fromLocal8Bit(d->io_name.c_str());
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
          axName = QString::fromLocal8Bit(ax->axis_name);
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

void MainWindow::updateProjectName() {
  auto pName = QString("%1: %2").arg(MainWindow::tr("工程"),
                                     YDProjectManage::getCurrentProject());
  auto name = QString("%1  ---  %2")
                  .arg(MainWindow::tr("业务逻辑编辑软件 v:1.1.0"), pName);
  setWindowTitle(name);
}

void MainWindow::updateRecipName() {
  auto rname = YDProjectManage::getCurrentRecipe();
  auto name = QString("%1 - %2").arg(MainWindow::tr("配方变量"), rname);
  ui->PeiFVarDock->setWindowTitle(name);
}

void MainWindow::addVar(int type, const QStringList &list,
                        yd::vr::SystemVariable *var) {
  if (var) {
    YDLogger::info(MainWindow::tr("创建变量: %1 成功")
                       .arg(QString::fromLocal8Bit(var->variable_name)));

    // INFO("TEST:{} {} {} {}", a, str, "adf", 2222);

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
      m_reciVarModel->setGroupId(subvg->groupId());
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

      addVar(type, list, var);
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
    auto vars = YDProjectManage::getAllVariables(vg->groupId());

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

      m_variablModel->setGroupId(vg->groupId());
    }
  }
}

void MainWindow::slotUpdateReciVar() {
  if (m_addReciVarDlg->result() == QDialog::Accepted) {
    auto list = m_addReciVarDlg->textList();
    YDVariable *vg =
        reinterpret_cast<YDVariable *>(m_reciVarIndex.internalPointer());
    int row = m_reciVarIndex.row();
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

      m_reciVarModel->setGroupId(vg->groupId());
    }
  }
}

void MainWindow::slotUpdateTempVar() {
  if (m_addTempVarDlg->result() == QDialog::Accepted) {
    auto list = m_addTempVarDlg->textList();
    YDVariable *vg =
        reinterpret_cast<YDVariable *>(m_tempVarIndex.internalPointer());
    int row = m_varViewIndex.row();
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

      m_tempVarModel->setGroupId(vg->groupId());
    }
  }
}

void MainWindow::on_addSafeVar_clicked() {
  if (m_addSafeVarDlg) delete m_addSafeVarDlg;
  m_addSafeVarDlg = new YDAddSafeVarDialog(this);
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
    if (var->parent() == YDProjectManage::getVarRoot())
      ui->addVar->setDisabled(true);
    else
      ui->addVar->setDisabled(false);

    m_variablModel->setGroupId(var->groupId());
  }
}

void MainWindow::slotReciVarGroupClick(const QModelIndex &index) {
  m_reciVarIndex = index;
  YDVariable *var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var) {
    if (var->parent() == YDProjectManage::getVarRoot())
      ui->addVar_2->setDisabled(true);
    else
      ui->addVar_2->setDisabled(false);

    m_reciVarModel->setGroupId(var->groupId());
  }
}

void MainWindow::slotTempVarGroupClick(const QModelIndex &index) {
  m_tempVarIndex = index;
  YDVariable *var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var) {
    if (var->parent() == YDProjectManage::getVarRoot())
      ui->addVar_4->setDisabled(true);
    else
      ui->addVar_4->setDisabled(false);

    m_tempVarModel->setGroupId(var->groupId());
  }
}

void MainWindow::slotVarGroupDoubleClick(const QModelIndex &) {}

void MainWindow::slotVarViewDoubleClick(const QModelIndex &index) {
  YDVariable *vg = reinterpret_cast<YDVariable *>(m_varIndex.internalPointer());
  int row = index.row();
  auto list = YDProjectManage::getAllVariables(vg->groupId());

  if (row < list.size()) {
    m_varViewIndex = index;
    auto var = list[row];
    QStringList infos;
    infos << QString::fromLocal8Bit(var->variable_name);
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
        infos << QString::fromLocal8Bit(var->init_value.c_str());
        infos << QString::fromLocal8Bit(var->min_value.c_str());
        infos << QString::fromLocal8Bit(var->max_value.c_str());
      } break;
      case DATA_TYPE_FLOAT:
      case DATA_TYPE_DOUBLE: {
        infos << "2";
        infos << QString::fromLocal8Bit(var->init_value.c_str());
        infos << QString::fromLocal8Bit(var->min_value.c_str());
        infos << QString::fromLocal8Bit(var->max_value.c_str());
      } break;
      case DATA_TYPE_STRING: {
        infos << "3";
        infos << QString::fromLocal8Bit(var->init_value.c_str());
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
    m_addVarDlg->open();
  }
}

void MainWindow::slotReciVarViewDoubleClick(const QModelIndex &index) {
  YDVariable *vg =
      reinterpret_cast<YDVariable *>(m_reciVarIndex.internalPointer());
  int row = index.row();
  auto list = YDProjectManage::GetGroupedReciVars(vg->groupId());

  if (row < list.size()) {
    m_varViewIndex = index;
    auto var = list[row];
    QStringList infos;
    infos << QString::fromLocal8Bit(var->variable_name);
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
        infos << QString::fromLocal8Bit(var->init_value.c_str());
        infos << QString::fromLocal8Bit(var->min_value.c_str());
        infos << QString::fromLocal8Bit(var->max_value.c_str());
      } break;
      case DATA_TYPE_FLOAT:
      case DATA_TYPE_DOUBLE: {
        infos << "2";
        infos << QString::fromLocal8Bit(var->init_value.c_str());
        infos << QString::fromLocal8Bit(var->min_value.c_str());
        infos << QString::fromLocal8Bit(var->max_value.c_str());
      } break;
      case DATA_TYPE_STRING: {
        infos << "3";
        infos << QString::fromLocal8Bit(var->init_value.c_str());
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

    if (m_addReciVarDlg) delete m_addReciVarDlg;
    m_addReciVarDlg = new YDAddReciVarDialog(this);
    m_addReciVarDlg->setTextList(infos);
    connect(m_addVarDlg, &YDAddReciVarDialog::finished, this,
            &MainWindow::slotUpdateReciVar);
    m_addReciVarDlg->open();
  }
}

void MainWindow::slotTempVarViewDoubleClick(const QModelIndex &index) {
  YDVariable *vg =
      reinterpret_cast<YDVariable *>(m_tempVarIndex.internalPointer());
  int row = index.row();
  auto list = YDProjectManage::GetGroupedTempVars(vg->groupId());

  if (row < list.size()) {
    m_varViewIndex = index;
    auto var = list[row];
    QStringList infos;
    infos << QString::fromLocal8Bit(var->variable_name);
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
        infos << QString::fromLocal8Bit(var->init_value.c_str());
        infos << QString::fromLocal8Bit(var->min_value.c_str());
        infos << QString::fromLocal8Bit(var->max_value.c_str());
      } break;
      case DATA_TYPE_FLOAT:
      case DATA_TYPE_DOUBLE: {
        infos << "2";
        infos << QString::fromLocal8Bit(var->init_value.c_str());
        infos << QString::fromLocal8Bit(var->min_value.c_str());
        infos << QString::fromLocal8Bit(var->max_value.c_str());
      } break;
      case DATA_TYPE_STRING: {
        infos << "3";
        infos << QString::fromLocal8Bit(var->init_value.c_str());
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
    m_addTempVarDlg->open();
  }
}

void MainWindow::slotSafeGroupClick(const QModelIndex &index) {
  m_safeVarIndex = index;
  YDVariable *var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var->parent() == YDProjectManage::getVarRoot())
    ui->addSafeVar->setDisabled(true);
  else
    ui->addSafeVar->setDisabled(false);
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
    auto var = list[row];
    m_selectSafeVar = var;
    QStringList textList;
    textList << QString::fromLocal8Bit(var->variable_name.c_str());
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
    m_addSafeVarDlg->setTextList(textList);
    connect(m_addSafeVarDlg, &YDAddSafeVarDialog::finished, this,
            &MainWindow::slotUpdateSafeVar);
    m_addSafeVarDlg->open();
  }
}

void MainWindow::slotDeviceSetDlgFinished() {}

void MainWindow::slotNetSetFinished() {
  if (m_netSetDlg->result() == QDialog::Accepted) {
    if (!YDDgHelper::createInstance()) return;

    auto filename = YDProjectManage::getFileName();
    auto ip = m_netSetDlg->getIP();
    auto time = m_netSetDlg->getTime();
    uint16 port = m_netSetDlg->getPort().toUShort();

    if (!YDDgHelper::isInitialized(filename, ip, port)) return;

    if (!YDDgHelper::getIProtocolClient()) return;

    if (!YDDgHelper::connect(3)) return;

    if (m_debugDlg) delete m_debugDlg;
    m_debugDlg = new YDDebugDialog(this);
    connect(m_debugDlg, &QDialog::finished, this,
            &MainWindow::slotDialogFinished);

    YDProjectManage::setTabWNull();
    YDHelper::setDebugMode(true);
    m_debugDlg->open();
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
    YDProjectManage::CreateProject(name);
    YDProjectManage::openProject(name);
    initOpenMenu();
    m_menuModel->updateModel();
  }
}

void MainWindow::slotChangeNFinished() {
  if (QDialog::Accepted == m_changeDlg->result()) {
    auto name = QSTRTSTR(m_changeDlg->getName());
    YDProjectManage::renameProject(name);
    initOpenMenu();
  }
}

void MainWindow::slotSaveasFinished() {
  if (QDialog::Accepted == m_saveasDlg->result()) {
    auto name = QSTRTSTR(m_saveasDlg->getName());
    YDProjectManage::saveProjectAs(name);
    initOpenMenu();
  }
}

void MainWindow::slotActionTriggered(bool) {
  QAction *ac = qobject_cast<QAction *>(sender());
  auto name = QSTRTSTR(ac->text());
  YDProjectManage::closeProject();
  YDProjectManage::openProject(name);
  m_menuModel->updateModel();

  initOpenMenu();
}

void MainWindow::slotWayActionTriggered(bool) {
  QAction *ac = qobject_cast<QAction *>(sender());
  auto name = QSTRTSTR(ac->text());
  YDProjectManage::openRecipe(name);
  initReciWidget();
  initOpenWayMenu();
}

void MainWindow::slotDelActionTriggered(bool) {
  QAction *ac = qobject_cast<QAction *>(sender());
  auto name = QSTRTSTR(ac->text());
  auto rb = QMessageBox::information(
      this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
      MainWindow::tr("确认"), MainWindow::tr("取消"));

  if (0 == rb) {
    YDProjectManage::deleteProject(name);
  }
  initOpenMenu();
}

void MainWindow::slotDelWayActionTriggered(bool) {
  QAction *ac = qobject_cast<QAction *>(sender());
  auto name = QSTRTSTR(ac->text());
  auto rb = QMessageBox::information(
      this, MainWindow::tr("提示"), MainWindow::tr("是否删除?"),
      MainWindow::tr("确认"), MainWindow::tr("取消"));

  if (0 == rb) {
    YDProjectManage::deleteRecipe(name);
  }
  initOpenWayMenu();
}

void MainWindow::slotCreateReciFinished() {
  if (QDialog::Accepted == m_createReciDlg->result()) {
    auto name = QSTRTSTR(m_createReciDlg->getName());
    YDProjectManage::createRecipe(name);
    YDProjectManage::openRecipe(name);
    initOpenWayMenu();
  }
}

void MainWindow::slotChangeReciFinished() {
  if (QDialog::Accepted == m_changeReciDlg->result()) {
    auto name = QSTRTSTR(m_changeReciDlg->getName());
    YDProjectManage::renameRecipe(name);
    initOpenWayMenu();
  }
}

void MainWindow::slotSaveasReciFinished() {
  if (QDialog::Accepted == m_saveasReciDlg->result()) {
    auto name = QSTRTSTR(m_saveasReciDlg->getName());
    YDProjectManage::saveRecipeAs(name);
    initOpenWayMenu();
  }
}

void MainWindow::slotDebugTrigger(bool) {}

void MainWindow::showHardConfig() { m_deviceSetDlg->open(); }

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
    case 0:
      break;
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
  auto name = YDHelper::genarateName();
  auto sname = QSTRTSTR(name);
  adv::ExtendScript *esc = nullptr;
  YDProjectManage::createScript(sname, esc);
  Q_ASSERT(esc);
  esc->script_type = SCRIPT_TYPE_VB_NET;
  m_scriptModel->updatedata();
}

void MainWindow::slotEditScriptProp(bool) {
  auto index = m_scriptView->currentIndex();
  if (index.isValid()) {
    auto list = YDProjectManage::getScripts();
    auto script = list[index.row()];
    m_scriptProp->setScritp(script);
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
    }
  }
}

void MainWindow::slotScriptItemClicked(const QModelIndex &index) {
  m_scriptIndex = index;
  auto list = YDProjectManage::getScripts();
  auto script = list[index.row()];
  m_codeManage->setScript(script);
  m_codeManage->open();
}

void MainWindow::slotScriptItemDBClicked(const QModelIndex &) {
  //  auto list = YDProjectManage::getScripts();
  //  auto script = list[index.row()];
  //  m_scriptProp->setScritp(script);
  //  m_scriptProp->open();
}

void MainWindow::slotScriptPropClose() {}

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
  }
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
    vlay3->addWidget(item);
    connect(item, &YDMenuItem::sigClicked, this, &MainWindow::showZeroScript);
  }

  m_scriptViewW->setStyleSheet("background:white;");
  auto hlay3 = new QHBoxLayout(m_scriptViewW);
  hlay3->setContentsMargins(0, 0, 0, 0);
  hlay3->setSpacing(0);
  hlay3->addSpacing(26);
  hlay3->addWidget(m_scriptView);

  m_cusScriptW->setIcon(":/Icon/Debug.png");
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
            << MainWindow::tr("输入状态") << MainWindow::tr("输出状态");

  for (int i = 0; i < watchlist.size(); ++i) {
    auto item = new YDMenuItem(i, m_moveSysW);
    item->setText(watchlist[i]);
    vlay5->addWidget(item);
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
  ui->a_wgbvar->setChecked(true);
  ui->a_wwyvar->setChecked(true);
  ui->a_wtpvar->setChecked(true);
  ui->a_wsfvar->setChecked(true);
  ui->a_wcylinder->setChecked(true);
  ui->a_wfeida->setChecked(true);
  ui->a_wtrayp->setChecked(true);
  ui->a_wdanjia->setChecked(true);

  connect(ui->a_wpromg, &QAction::triggered, this,
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

  connect(ui->a_doldebug, &QAction::triggered, this,
          &MainWindow::slotDebugTrigger);
}

// void ::on_addTask_clicked() {
//   m_menuModel->addTree(m_taskIndex);
//   m_logicTree->expand(m_taskIndex);
// }

// void MainWindow::on_delTask_clicked() {
//   m_menuModel->removeTree(m_taskIndex);
//   m_taskIndex = QModelIndex();
//   m_logicTree->setCurrentIndex(m_taskIndex);
// }

//菜单栏

void MainWindow::on_a_new_triggered() {
  m_createPDlg->clear();
  m_createPDlg->open();
}

void MainWindow::on_a_close_triggered() { YDProjectManage::closeProject(); }

void MainWindow::on_a_rename_triggered() {
  m_changeDlg->clear();
  m_changeDlg->open();
}

void MainWindow::on_a_save_triggered() {
  setFocus();
  YDProjectManage::saveProject();
}

void MainWindow::on_a_saveall_triggered() {
  setFocus();
  YDProjectManage::saveProject();
}

void MainWindow::on_a_saveoth_triggered() { m_saveasDlg->open(); }

void MainWindow::on_a_exit_triggered() { exit(0); }

void MainWindow::on_a_newway_triggered() {
  m_createReciDlg->open();
  initReciWidget();
}

void MainWindow::on_a_changeWay_triggered() { m_changeReciDlg->open(); }

void MainWindow::on_a_saveway_triggered() { m_saveasReciDlg->open(); }

void MainWindow::on_a_saveow_triggered() { YDProjectManage::saveRecipe(); }

void MainWindow::on_a_dupload_triggered() {}

void MainWindow::on_a_ddownload_triggered() {}

void MainWindow::on_a_doldebug_triggered() {}

void MainWindow::on_a_dstartz_triggered() {}

void MainWindow::on_a_dstartm_triggered() {}

void MainWindow::on_a_dpausem_triggered() {}

void MainWindow::on_a_dstopm_triggered() {}

void MainWindow::on_a_ttalkset_triggered() { m_netSetDlg->open(); }
