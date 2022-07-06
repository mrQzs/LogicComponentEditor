#include "YDDAxisControl.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "YDMoveControlWidget.h"
#include "YDSpeedSetWidget.h"
#include "YDState.h"
#include "YDStateWidget.h"
#include "common/YDHelper.h"
#include "debug/YDAXisListView.h"
#include "widget/YDNameLineEdit.h"

YDDAxisControl::YDDAxisControl(QWidget *parent)
    : QDialog{parent},
      m_menuTree{new QTreeWidget(this)},
      m_view{new YDAXisListView(this)},
      m_widget{new QWidget(this)},
      m_stateW{new YDStateWidget(m_view, this)},
      m_speedSetW{new YDSpeedSetWidget(this)},
      m_moveconW{new YDMoveControlWidget(this)},
      m_type{-1} {
  this->setWindowTitle(YDDAxisControl::tr("轴控制"));

  initUi();

  initTree();

  m_view->hide();
  m_stateW->hide();
  m_speedSetW->hide();
  m_moveconW->hide();
}

YDDAxisControl::~YDDAxisControl() {}

void YDDAxisControl::updateData() {
  switch (m_type) {
    case 0:
      m_stateW->updateData();
      break;
    case 1:
      m_speedSetW->updateData();
      break;
    case 2:
      m_moveconW->updateData();
      break;
    default:
      break;
  }
}

void YDDAxisControl::slotTreeDooubleClick(const QModelIndex &index) {
  auto item = m_menuTree->itemFromIndex(index);
  if (m_smi == item)
    showWidget(0);
  else if (m_ssi == item)
    showWidget(1);
  else if (m_mci == item)
    showWidget(2);
}

void YDDAxisControl::initUi() {
  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_menuTree);
  hlay->addWidget(m_widget);
  m_menuTree->setFixedWidth(220);
}

void YDDAxisControl::initTree() {
  m_menuTree->header()->hide();

  auto item1 = new QTreeWidgetItem(m_menuTree);
  auto item2 = item1;
  item1->setText(0, YDDAxisControl::tr("运动监控"));
  m_smi = new QTreeWidgetItem(item2);
  m_smi->setText(0, YDDAxisControl::tr("状态监控"));

  m_ssi = new QTreeWidgetItem(item2);
  m_ssi->setText(0, YDDAxisControl::tr("速度设定"));

  m_mci = new QTreeWidgetItem(item2);
  m_mci->setText(0, YDDAxisControl::tr("运动控制"));

  connect(m_menuTree, &QTreeWidget::clicked, this,
          &YDDAxisControl::slotTreeDooubleClick);
}

void YDDAxisControl::showWidget(int type) {
  m_view->hide();
  m_stateW->hide();
  m_speedSetW->hide();
  m_moveconW->hide();

  delete layout();

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_menuTree);

  m_type = type;

  switch (type) {
    case 0:
      m_stateW->show();
      m_stateW->clearStateInfo();
      hlay->addWidget(m_stateW);
      break;
    case 1:
      m_speedSetW->show();
      m_speedSetW->clearStateInfo();
      hlay->addWidget(m_speedSetW);
      break;
    case 2:
      m_moveconW->show();
      m_moveconW->clearStateInfo();
      hlay->addWidget(m_moveconW);
      break;
  }
}
