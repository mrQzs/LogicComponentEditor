#include "YDDebugDialog.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QThread>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "YDAXisListView.h"
#include "YDDAxisVarWidget.h"
#include "YDDCylinderWidget.h"
#include "YDDInputWidget.h"
#include "YDDOutputWidget.h"
#include "YDDTaskWidget.h"
#include "YDDVariableWidget.h"
#include "YDMoveControlWidget.h"
#include "YDSpeedSetWidget.h"
#include "YDState.h"
#include "YDStateWidget.h"
#include "common/YDHelper.h"
#include "core/thread/YDThreads.h"
#include "widget/YDNameLineEdit.h"

YDDebugDialog::YDDebugDialog(QWidget *parent)
    : QDialog{parent},
      m_menuTree{new QTreeWidget(this)},
      m_widget{new QWidget(this)},
      m_view{new YDAXisListView(this)},
      m_inputW{new YDDInputWidget(this)},
      m_outputW{new YDDOutputWidget(this)},
      m_stateW{new YDStateWidget(m_view, this)},
      m_speedSetW{new YDSpeedSetWidget(this)},
      m_moveconW{new YDMoveControlWidget(this)},
      m_varW{new YDDVariableWidget(this)},
      m_axisVarW{new YDDAxisVarWidget(this)},
      m_cylinderW{new YDDCylinderWidget(this)},
      m_taskW{new YDDTaskWidget(this)},
      m_topW{new QWidget(this)},
      m_state{new QLabel(m_topW)},
      m_state1{new QLabel(m_topW)},
      m_start{new QPushButton(m_topW)},
      m_stop{new QPushButton(m_topW)},
      m_pause{new QPushButton(m_topW)},
      m_resume{new QPushButton(m_topW)},
      m_timeLab{new QLabel(this)},
      m_timeEdit{new QLineEdit(this)},
      m_timeBtn{new QPushButton(this)},
      m_mode{new QLabel(m_topW)},
      m_modeLab{new QLabel(m_topW)},
      m_auto{new QPushButton(m_topW)},
      m_manu{new QPushButton(m_topW)},
      m_line{new QFrame(m_topW)},
      m_pProtocolClient{nullptr},
      m_type{-1},
      m_timerThread{new QThread},
      m_timer{new YDTimer} {
  this->setWindowTitle(YDDebugDialog::tr("调试窗口"));

  initUi();

  initTree();

  m_state->setText(YDDebugDialog::tr("状态:"));
  m_start->setText(YDDebugDialog::tr("启动"));
  m_stop->setText(YDDebugDialog::tr("停止"));
  m_pause->setText(YDDebugDialog::tr("暂停"));
  m_resume->setText(YDDebugDialog::tr("恢复"));

  m_timeLab->setText(YDDebugDialog::tr("定时刷新(ms)"));
  m_timeEdit->setText("500");
  m_timeBtn->setText(YDDebugDialog::tr("设置"));

  m_mode->setText(YDDebugDialog::tr("模式:"));
  m_auto->setText(YDDebugDialog::tr("自动"));
  m_manu->setText(YDDebugDialog::tr("手动"));

  m_view->hide();
  m_inputW->hide();
  m_outputW->hide();
  m_stateW->hide();
  m_speedSetW->hide();
  m_moveconW->hide();
  m_varW->hide();
  m_axisVarW->hide();
  m_cylinderW->hide();
  m_taskW->hide();

  m_state1->setFixedWidth(100);
  m_modeLab->setFixedWidth(100);
  m_topW->setFixedHeight(60);

  connect(m_start, &QPushButton::clicked, this, &YDDebugDialog::slotStart);
  connect(m_stop, &QPushButton::clicked, this, &YDDebugDialog::slotStop);
  connect(m_pause, &QPushButton::clicked, this, &YDDebugDialog::slotPause);
  connect(m_resume, &QPushButton::clicked, this, &YDDebugDialog::slotResume);
  connect(m_auto, &QPushButton::clicked, this, &YDDebugDialog::slotAuto);
  connect(m_manu, &QPushButton::clicked, this, &YDDebugDialog::slotManu);

  m_timer->moveToThread(m_timerThread);
  QObject::connect(m_timer, &YDTimer::timeout, this,
                   &YDDebugDialog::updateData);

  QObject::connect(this, &YDDebugDialog::start, m_timer, &YDTimer::startrun);
  QObject::connect(this, &YDDebugDialog::stop, m_timer, &YDTimer::stop);
  QObject::connect(this, &YDDebugDialog::updateTime, m_timer,
                   &YDTimer::setTime);

  connect(m_timeBtn, &QPushButton::clicked, this,
          &YDDebugDialog::slotUpdateTime);

  m_timerThread->start();

  updateData();
  emit start();
}

YDDebugDialog::~YDDebugDialog() {
  emit stop();
  m_timerThread->requestInterruption();
  m_timerThread->exit(0);
  m_timerThread->wait();
  delete m_timer;
  delete m_timerThread;
}

void YDDebugDialog::stopThread() { emit stop(); }

void YDDebugDialog::slotTreeDooubleClick(const QModelIndex &index) {
  auto item = m_menuTree->itemFromIndex(index);
  if (m_ini == item)
    showWidget(0);
  else if (m_opi == item)
    showWidget(1);
  else if (m_smi == item)
    showWidget(2);
  else if (m_ssi == item)
    showWidget(3);
  else if (m_mci == item)
    showWidget(4);
  else if (m_nvi == item)
    showWidget(5);
  else if (m_avi == item)
    showWidget(6);
  else if (m_cyi == item)
    showWidget(7);
  else if (m_tvi == item)
    showWidget(8);
}

void YDDebugDialog::initUi() {
  m_line->setFrameShape(QFrame::HLine);
  m_line->setFrameShadow(QFrame::Sunken);

  auto grid = new QGridLayout;
  grid->setHorizontalSpacing(15);
  grid->setVerticalSpacing(3);
  grid->addWidget(m_state, 0, 0, 1, 1);
  grid->addWidget(m_state1, 0, 1, 1, 1);
  grid->addWidget(m_start, 0, 2, 1, 1);
  grid->addWidget(m_stop, 0, 3, 1, 1);
  grid->addWidget(m_pause, 0, 4, 1, 1);
  grid->addWidget(m_resume, 0, 5, 1, 1);

  grid->addWidget(m_mode, 1, 0, 1, 1);
  grid->addWidget(m_modeLab, 1, 1, 1, 1);
  grid->addWidget(m_auto, 1, 2, 1, 1);
  grid->addWidget(m_manu, 1, 3, 1, 1);
  grid->addWidget(m_timeLab, 1, 5, 1, 1);
  grid->addWidget(m_timeEdit, 1, 6, 1, 1);
  grid->addWidget(m_timeBtn, 1, 7, 1, 1);

  auto hhlay = new QHBoxLayout;
  hhlay->addStretch();
  hhlay->addLayout(grid);
  hhlay->addStretch();

  auto vlay = new QVBoxLayout(m_topW);
  vlay->setContentsMargins(0, 0, 0, 0);
  vlay->setSpacing(0);
  vlay->addLayout(hhlay);
  vlay->addWidget(m_line);

  auto vvlay = new QVBoxLayout;
  vvlay->addWidget(m_topW);
  vvlay->addWidget(m_widget);

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_menuTree);
  hlay->addLayout(vvlay);

  m_menuTree->setFixedWidth(220);
  setFixedSize(1920, 1080);
}

void YDDebugDialog::initTree() {
  auto head = m_menuTree->headerItem();
  head->setText(0, YDDebugDialog::tr("调式功能栏"));

  auto item1 = new QTreeWidgetItem(m_menuTree);
  auto item0 = item1;
  item1->setText(0, YDDebugDialog::tr("IO监控"));
  m_ini = new QTreeWidgetItem(item0);
  m_ini->setText(0, YDDebugDialog::tr("输入状态"));

  m_opi = new QTreeWidgetItem(item0);
  m_opi->setText(0, YDDebugDialog::tr("输出监控"));

  item1 = new QTreeWidgetItem(m_menuTree);
  auto item2 = item1;
  item1->setText(0, YDDebugDialog::tr("运动监控"));
  m_smi = new QTreeWidgetItem(item2);
  m_smi->setText(0, YDDebugDialog::tr("状态监控"));

  m_ssi = new QTreeWidgetItem(item2);
  m_ssi->setText(0, YDDebugDialog::tr("速度设定"));

  m_mci = new QTreeWidgetItem(item2);
  m_mci->setText(0, YDDebugDialog::tr("运动控制"));

  item1 = new QTreeWidgetItem(m_menuTree);
  auto item3 = item1;
  item1->setText(0, YDDebugDialog::tr("变量监控"));

  m_nvi = new QTreeWidgetItem(item3);
  m_nvi->setText(0, YDDebugDialog::tr("普通变量"));

  m_avi = new QTreeWidgetItem(item3);
  m_avi->setText(0, YDDebugDialog::tr("坐标变量"));

  m_cyi = new QTreeWidgetItem(m_menuTree);
  m_cyi->setText(0, YDDebugDialog::tr("气油缸监控"));

  m_tvi = new QTreeWidgetItem(m_menuTree);
  m_tvi->setText(0, YDDebugDialog::tr("逻辑调试"));

  connect(m_menuTree, &QTreeWidget::clicked, this,
          &YDDebugDialog::slotTreeDooubleClick);
}

void YDDebugDialog::showWidget(int type) {
  m_view->hide();
  m_inputW->hide();
  m_outputW->hide();
  m_stateW->hide();
  m_speedSetW->hide();
  m_moveconW->hide();
  m_varW->hide();
  m_axisVarW->hide();
  m_cylinderW->hide();
  m_taskW->hide();

  delete layout();

  auto vlay = new QVBoxLayout;
  vlay->setContentsMargins(0, 0, 0, 0);
  vlay->setSpacing(0);
  vlay->addWidget(m_topW);

  m_type = type;
  switch (m_type) {
    case 0:
      m_inputW->show();
      vlay->addWidget(m_inputW);
      break;
    case 1:
      m_outputW->show();
      vlay->addWidget(m_outputW);
      break;
    case 2:
      m_stateW->show();
      vlay->addWidget(m_stateW);
      break;
    case 3:
      m_speedSetW->show();
      vlay->addWidget(m_speedSetW);
      break;
    case 4:
      m_moveconW->show();
      vlay->addWidget(m_moveconW);
      break;
    case 5:
      m_varW->show();
      vlay->addWidget(m_varW);
      break;
    case 6:
      m_axisVarW->show();
      vlay->addWidget(m_axisVarW);
      break;
    case 7:
      m_cylinderW->show();
      vlay->addWidget(m_cylinderW);
      break;
    case 8:
      m_taskW->show();
      vlay->addWidget(m_taskW);
      break;
    default:
      break;
  }

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_menuTree);
  hlay->addLayout(vlay);
}

void YDDebugDialog::slotStart(bool) {
  YDDgHelper::startLogicController();
  updateServer();
}

void YDDebugDialog::slotStop(bool) {
  YDDgHelper::stopLogicController();
  updateServer();
}

void YDDebugDialog::slotPause(bool) {
  YDDgHelper::suspendLogicController();
  updateServer();
}

void YDDebugDialog::slotResume(bool) {
  YDDgHelper::restoreLogicController();
  updateServer();
}

void YDDebugDialog::slotAuto(bool) {
  YDDgHelper::logicControllerSwitchToAutoMode();
  updateServer();
}

void YDDebugDialog::slotManu(bool) {
  YDDgHelper::logicControllerSwitchToManualMode();
  updateServer();
}

void YDDebugDialog::updateData() {
  switch (m_type) {
    case 0:
      m_inputW->updateData();
      break;
    case 1:
      m_outputW->updateData();
      break;
    case 2:
      m_stateW->updateData();
      break;
    case 3:
      m_speedSetW->updateData();
      break;
    case 4:
      m_moveconW->updateData();
      break;
    case 5:
      m_varW->updateData();
      break;
    case 6:
      // m_axisVarW->updateData();
      break;
    case 7:
      m_cylinderW->updateData();
      break;
    case 8:
      m_taskW->updateDate();
      break;
    default:
      break;
  }
  updateServer();
}

void YDDebugDialog::updateServer() {
  uint8 ucStatus = 0, ucMode = 0;
  YDDgHelper::getLogicControllerStatus(ucStatus, ucMode);

  m_runing = (SYSTEM_STATUS_RUNNING == ucStatus);
  m_automode = (CONTROLLER_MODE_AUTOMATIC == ucMode);

  QString strStatus;
  switch (ucStatus) {
    case SYSTEM_STATUS_RUNNING:
      strStatus = YDDebugDialog::tr("运行中");
      break;
    case SYSTEM_STATUS_STOPED:
      strStatus = YDDebugDialog::tr("已停止");
      break;
    case SYSTEM_STATUS_SUSPENDED:
      strStatus = YDDebugDialog::tr("已挂起");
      break;
    case SYSTEM_STATUS_RESTORED:
      strStatus = YDDebugDialog::tr("已恢复");
      break;
    default:
      strStatus = YDDebugDialog::tr("未知");
      break;
  }

  QString strMode;
  switch (ucMode) {
    case CONTROLLER_MODE_MANUAL:
      strMode = YDDebugDialog::tr("手动");
      break;
    case CONTROLLER_MODE_AUTOMATIC:
      strMode = YDDebugDialog::tr("自动");
      break;
  }

  m_state1->setText(strStatus);
  m_modeLab->setText(strMode);

  m_start->setEnabled(!m_runing);
  m_stop->setEnabled(m_runing);
  m_pause->setEnabled(m_runing);
  m_resume->setEnabled(!m_runing);

  m_auto->setEnabled(!m_automode);
  m_manu->setEnabled(m_automode);
}

void YDDebugDialog::slotUpdateTime(bool) {
  auto time = m_timeEdit->text().toUInt();
  emit updateTime(time);
}
