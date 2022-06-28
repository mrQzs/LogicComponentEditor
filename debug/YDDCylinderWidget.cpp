#include "YDDCylinderWidget.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "YDDCylinderView.h"
#include "YDDgHelper.h"
#include "YDState.h"
#include "core/YDProjectManage.h"
#include "model/YDCylinderModel.h"

YDDCylinderWidget::YDDCylinderWidget(QWidget *parent)
    : QWidget{parent},
      m_view{new YDDCylinderView(this)},
      m_model{new YDCylinderModel(this)},
      m_lab1{new QLabel(this)},
      m_state1{new YDState(this)},
      m_lab2{new QLabel(this)},
      m_state2{new YDState(this)},
      m_lab3{new QLabel(this)},
      m_state3{new YDState(this)},
      m_lab4{new QLabel(this)},
      m_state4{new YDState(this)},
      m_lab5{new QLabel(this)},
      m_state5{new YDState(this)},
      m_lab6{new QLabel(this)},
      m_state6{new YDState(this)},
      m_forwardBtn{new QPushButton(this)},
      m_backBtn{new QPushButton(this)} {
  auto grid = new QGridLayout;
  grid->addWidget(m_lab1, 0, 0, 1, 1);
  grid->addWidget(m_state1, 0, 1, 1, 1);
  grid->addWidget(m_lab2, 0, 2, 1, 1);
  grid->addWidget(m_state2, 0, 3, 1, 1);
  grid->addWidget(m_lab3, 1, 0, 1, 1);
  grid->addWidget(m_state3, 1, 1, 1, 1);
  grid->addWidget(m_lab4, 1, 2, 1, 1);
  grid->addWidget(m_state4, 1, 3, 1, 1);
  grid->addWidget(m_lab5, 2, 0, 1, 1);
  grid->addWidget(m_state5, 2, 1, 1, 1);
  grid->addWidget(m_lab6, 2, 2, 1, 1);
  grid->addWidget(m_state6, 2, 3, 1, 1);

  auto hhlay = new QHBoxLayout;
  hhlay->addStretch();
  hhlay->addWidget(m_forwardBtn);
  hhlay->addStretch();
  hhlay->addWidget(m_backBtn);
  hhlay->addStretch();

  auto vlay = new QVBoxLayout;
  vlay->addLayout(grid);
  vlay->addLayout(hhlay);
  vlay->addStretch();

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 400, 0);
  hlay->setSpacing(10);
  hlay->addWidget(m_view);
  hlay->addLayout(vlay);

  m_lab1->setText(YDDCylinderWidget::tr("方向一 关联DI状态"));
  m_lab2->setText(YDDCylinderWidget::tr("方向二 关联DI状态"));
  m_lab3->setText(YDDCylinderWidget::tr("方向一 运动控制"));
  m_lab4->setText(YDDCylinderWidget::tr("方向二 运动控制"));
  m_lab5->setText(YDDCylinderWidget::tr("方向一 报警触发"));
  m_lab6->setText(YDDCylinderWidget::tr("方向二 报警触发"));

  m_forwardBtn->setText(YDDCylinderWidget::tr("前进"));
  m_backBtn->setText(YDDCylinderWidget::tr("后退"));

  m_lab1->setAlignment(Qt::AlignRight);
  m_lab2->setAlignment(Qt::AlignRight);
  m_lab3->setAlignment(Qt::AlignRight);
  m_lab4->setAlignment(Qt::AlignRight);
  m_lab5->setAlignment(Qt::AlignRight);
  m_lab6->setAlignment(Qt::AlignRight);

  m_view->setFixedWidth(200);
  m_state1->setFixedWidth(120);
  m_state2->setFixedWidth(120);
  m_state3->setFixedWidth(120);
  m_state4->setFixedWidth(120);
  m_state5->setFixedWidth(120);
  m_state6->setFixedWidth(120);

  m_view->setModel(m_model);

  connect(m_forwardBtn, &QPushButton::clicked, this,
          &YDDCylinderWidget::slotForward);

  connect(m_backBtn, &QPushButton::clicked, this, &YDDCylinderWidget::slotBack);

  connect(m_view, &YDDCylinderView::clicked, this,
          &YDDCylinderWidget::slotItemClicked);
}

void YDDCylinderWidget::slotItemClicked(const QModelIndex &index) {
  updateData();
}

void YDDCylinderWidget::updateData() {
  auto index = m_view->currentIndex();
  int row = index.row();
  auto list = YDProjectManage::getCylinders();
  if (row < list.size()) {
    auto cyl = list[row];
    yd::proto::DirectionState state1;
    yd::proto::DirectionState state2;
    YDDgHelper::getCylinderState(cyl->base.id, &state1, &state2);

    m_state1->setState(state1.refer_di);
    m_state2->setState(state2.refer_di);
    m_state3->setState(state1.arrived);
    m_state4->setState(state2.arrived);
    m_state5->setState(state1.alarmed);
    m_state6->setState(state2.alarmed);
  }
  update();
}

void YDDCylinderWidget::slotForward(bool) {
  auto index = m_view->currentIndex();
  int row = index.row();
  auto list = YDProjectManage::getCylinders();
  if (row < list.size()) {
    auto cyl = list[row];
    YDDgHelper::controlCylinder(cyl->base.id, 1);
  }
}

void YDDCylinderWidget::slotBack(bool) {
  auto index = m_view->currentIndex();
  int row = index.row();
  auto list = YDProjectManage::getCylinders();
  if (row < list.size()) {
    auto cyl = list[row];
    YDDgHelper::controlCylinder(cyl->base.id, 2);
  }
}
