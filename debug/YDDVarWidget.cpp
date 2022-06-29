#include "YDDVarWidget.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "YDDAxisVarWidget.h"
#include "YDDVariableWidget.h"
#include "common/YDHelper.h"
#include "debug/YDAXisListView.h"
#include "widget/YDNameLineEdit.h"

YDDVarWidget::YDDVarWidget(QWidget *parent)
    : QDialog{parent},
      m_menuTree{new QTreeWidget(this)},
      m_widget{new QWidget(this)},
      m_varW{new YDDVariableWidget(this)},
      m_axisVarW{new YDDAxisVarWidget(this)} {
  this->setWindowTitle(YDDVarWidget::tr("轴控制"));

  initUi();

  initTree();

  m_varW->hide();
  m_axisVarW->hide();
}

YDDVarWidget::~YDDVarWidget() {}

void YDDVarWidget::updateData() {
  switch (m_type) {
    case 0:
      m_varW->updateData();
      break;
    case 1:
      m_axisVarW->updateData();
      break;
    default:
      break;
  }
}

void YDDVarWidget::slotTreeDooubleClick(const QModelIndex &index) {
  auto item = m_menuTree->itemFromIndex(index);
  if (m_smi == item)
    showWidget(0);
  else if (m_ssi == item)
    showWidget(1);
}

void YDDVarWidget::initUi() {
  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_menuTree);
  hlay->addWidget(m_widget);
  m_menuTree->setFixedWidth(240);
}

void YDDVarWidget::initTree() {
  m_menuTree->header()->hide();

  auto item1 = new QTreeWidgetItem(m_menuTree);
  auto item2 = item1;
  item1->setText(0, YDDVarWidget::tr("变量监测"));
  m_smi = new QTreeWidgetItem(item2);
  m_smi->setText(0, YDDVarWidget::tr("普通变量监测"));

  m_ssi = new QTreeWidgetItem(item2);
  m_ssi->setText(0, YDDVarWidget::tr("坐标变量监测"));

  connect(m_menuTree, &QTreeWidget::doubleClicked, this,
          &YDDVarWidget::slotTreeDooubleClick);
}

void YDDVarWidget::showWidget(int type) {
  m_varW->hide();
  m_axisVarW->hide();

  delete layout();

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_menuTree);

  m_type = type;

  switch (type) {
    case 0:
      m_varW->show();
      hlay->addWidget(m_varW);
      break;
    case 1:
      m_axisVarW->show();
      hlay->addWidget(m_axisVarW);
      break;
  }
}
