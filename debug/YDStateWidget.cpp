#include "YDStateWidget.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "YDAXisListView.h"
#include "YDAxisListModel.h"
#include "YDDgHelper.h"
#include "YDState.h"
#include "core/YDProjectManage.h"
#include "widget/YDLoadingDialog.h"
#include "widget/YDNameLineEdit.h"

YDStateWidget::YDStateWidget(YDAXisListView *view, QWidget *parent)
    : QWidget{parent},
      m_view{new YDAXisListView(this)},
      m_model{new YDAxisListModel(this)},
      m_loading{new YDLoadingDialog(this)},
      m_lab1{new QLabel(this)},
      m_zero{new YDState(this)},
      m_lab2{new QLabel(this)},
      m_enable{new YDState(this)},
      m_lab3{new QLabel(this)},
      m_drive{new YDState(this)},
      m_lab4{new QLabel(this)},
      m_motion{new YDState(this)},
      m_lab5{new QLabel(this)},
      m_plus{new YDState(this)},
      m_lab6{new QLabel(this)},
      m_nagetive{new YDState(this)},
      m_lab7{new QLabel(this)},
      m_point{new YDState(this)},
      m_lab8{new QLabel(this)},
      m_emerg{new YDState(this)},
      m_lab11{new QLabel(this)},
      m_edit1{new QLineEdit(this)},
      m_lab12{new QLabel(this)},
      m_edit2{new QLineEdit(this)},
      m_lab13{new QLabel(this)},
      m_edit3{new QLineEdit(this)},
      m_lab14{new QLabel(this)},
      m_edit4{new QLineEdit(this)},
      m_btn1{new QPushButton(this)},
      m_btn2{new QPushButton(this)},
      m_btn3{new QPushButton(this)},
      m_btn4{new QPushButton(this)},
      m_btn5{new QPushButton(this)},
      m_state{new QLabel(this)} {
  m_view->setFixedWidth(200);
  m_view->setModel(m_model);

  auto grid = new QGridLayout;
  grid->setSpacing(10);
  grid->addWidget(m_lab1, 0, 0, 1, 1);
  grid->addWidget(m_zero, 0, 1, 1, 2);
  grid->addWidget(m_lab2, 0, 3, 1, 1);
  grid->addWidget(m_enable, 0, 4, 1, 2);

  grid->addWidget(m_lab3, 1, 0, 1, 1);
  grid->addWidget(m_drive, 1, 1, 1, 2);
  grid->addWidget(m_lab4, 1, 3, 1, 1);
  grid->addWidget(m_motion, 1, 4, 1, 2);

  grid->addWidget(m_lab5, 2, 0, 1, 1);
  grid->addWidget(m_plus, 2, 1, 1, 2);
  grid->addWidget(m_lab11, 2, 3, 1, 1);
  grid->addWidget(m_edit1, 2, 4, 1, 2);

  grid->addWidget(m_lab6, 3, 0, 1, 1);
  grid->addWidget(m_nagetive, 3, 1, 1, 2);
  grid->addWidget(m_lab12, 3, 3, 1, 1);
  grid->addWidget(m_edit2, 3, 4, 1, 2);

  grid->addWidget(m_lab7, 4, 0, 1, 1);
  grid->addWidget(m_point, 4, 1, 1, 2);
  grid->addWidget(m_lab13, 4, 3, 1, 1);
  grid->addWidget(m_edit3, 4, 4, 1, 2);

  grid->addWidget(m_lab8, 5, 0, 1, 1);
  grid->addWidget(m_emerg, 5, 1, 1, 2);
  grid->addWidget(m_lab14, 5, 3, 1, 1);
  grid->addWidget(m_edit4, 5, 4, 1, 2);

  m_lab1->setAlignment(Qt::AlignCenter);
  m_lab2->setAlignment(Qt::AlignCenter);
  m_lab3->setAlignment(Qt::AlignCenter);
  m_lab4->setAlignment(Qt::AlignCenter);
  m_lab5->setAlignment(Qt::AlignCenter);
  m_lab6->setAlignment(Qt::AlignCenter);
  m_lab7->setAlignment(Qt::AlignCenter);
  m_lab8->setAlignment(Qt::AlignCenter);
  m_lab11->setAlignment(Qt::AlignCenter);
  m_lab12->setAlignment(Qt::AlignCenter);
  m_lab13->setAlignment(Qt::AlignCenter);
  m_lab14->setAlignment(Qt::AlignCenter);

  auto hlay2 = new QHBoxLayout;
  hlay2->setSpacing(20);
  hlay2->addStretch();
  hlay2->addWidget(m_btn1);
  hlay2->addWidget(m_btn2);
  hlay2->addWidget(m_btn3);
  hlay2->addWidget(m_btn4);
  hlay2->addWidget(m_btn5);
  hlay2->addStretch();

  m_btn1->setMinimumWidth(120);
  m_btn2->setMinimumWidth(120);
  m_btn3->setMinimumWidth(120);
  m_btn4->setMinimumWidth(120);
  m_btn5->setMinimumWidth(120);

  auto vlay = new QVBoxLayout;
  vlay->setContentsMargins(20, 20, 0, 100);
  vlay->addLayout(grid);
  vlay->addSpacing(30);
  vlay->addLayout(hlay2);
  vlay->addStretch();
  vlay->addWidget(m_state, 0, Qt::AlignBottom);
  vlay->addStretch();

  m_state->setAlignment(Qt::AlignCenter);
  m_state->setFont(QFont("Microsoft YaHei", 16, 75));

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 10, 0);
  hlay->setSpacing(10);
  hlay->addWidget(m_view);
  hlay->addLayout(vlay);

  m_lab1->setText(YDStateWidget::tr("回零状态"));
  m_lab2->setText(YDStateWidget::tr("使能状态"));
  m_lab3->setText(YDStateWidget::tr("驱动报警"));
  m_lab4->setText(YDStateWidget::tr("运动状态"));
  m_lab5->setText(YDStateWidget::tr("正向限位"));
  m_lab6->setText(YDStateWidget::tr("负向限位"));
  m_lab7->setText(YDStateWidget::tr("原点信号"));
  m_lab8->setText(YDStateWidget::tr("紧急停止"));
  m_lab11->setText(YDStateWidget::tr("目标位置"));
  m_lab12->setText(YDStateWidget::tr("规划位置"));
  m_lab13->setText(YDStateWidget::tr("反馈位置"));
  m_lab14->setText(YDStateWidget::tr("规划速度"));

  m_btn1->setText(YDStateWidget::tr("打开使能"));
  m_btn2->setText(YDStateWidget::tr("关闭使能"));
  m_btn3->setText(YDStateWidget::tr("状态清除"));
  m_btn4->setText(YDStateWidget::tr("位置清零"));
  m_btn5->setText(YDStateWidget::tr("回零"));

  m_btn5->setVisible(false);  //暂时隐藏

  m_edit1->setDisabled(true);
  m_edit2->setDisabled(true);
  m_edit3->setDisabled(true);
  m_edit4->setDisabled(true);

  connect(m_btn1, &QPushButton::clicked, this, &YDStateWidget::slotbtn1Clicked);
  connect(m_btn2, &QPushButton::clicked, this, &YDStateWidget::slotbtn2Clicked);
  connect(m_btn3, &QPushButton::clicked, this, &YDStateWidget::slotbtn3Clicked);
  connect(m_btn4, &QPushButton::clicked, this, &YDStateWidget::slotbtn4Clicked);
  connect(m_btn5, &QPushButton::clicked, this, &YDStateWidget::slotbtn5Clicked);
}

void YDStateWidget::updateData() {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) row = 0;
  auto axis = axisList[row];
  yd::proto::AxisState axisState;
  YDDgHelper::getAxisState(axis->device_id, axis->axis_index, &axisState);

  m_zero->setState(axisState.home_moved);
  m_enable->setState(axisState.driver_enable);
  m_drive->setState(axisState.driver_alarm);
  m_motion->setState(axisState.profile_move);
  m_plus->setState(axisState.positive_limit);
  m_nagetive->setState(axisState.negative_limit);
  m_point->setState(axisState.home_signal);
  m_emerg->setState(axisState.urgent_stop);

  m_edit1->setText(QString::number(axisState.target_position));
  m_edit2->setText(QString::number(axisState.profile_position));
  m_edit3->setText(QString::number(axisState.encoder_position));
  m_edit4->setText(QString::number(axisState.profile_velocity));

  update();
}

void YDStateWidget::clearStateInfo() { m_state->clear(); }

void YDStateWidget::setReturnState(qint32 code, const QString &name) {
  m_loading->close();
  switch (code) {
    case PROJECT_ERROR_NONE:
      m_state->setText(name + YDStateWidget::tr(": 成功"));
      break;
    default:
      m_state->setText(name + YDStateWidget::tr(": 失败"));
      break;
  }
}

void YDStateWidget::slotbtn1Clicked(bool) {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) row = 0;
  auto axis = axisList[row];
  m_loading->show();
  int32 code = YDDgHelper::enableAxis(axis->device_id, axis->axis_index, true);

  setReturnState(code, YDStateWidget::tr("打开使能"));
  updateData();
}

void YDStateWidget::slotbtn2Clicked(bool) {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) row = 0;
  auto axis = axisList[row];
  m_loading->show();
  int32 code = YDDgHelper::enableAxis(axis->device_id, axis->axis_index, false);

  setReturnState(code, YDStateWidget::tr("关闭使能"));
  updateData();
}

void YDStateWidget::slotbtn3Clicked(bool) {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) row = 0;
  auto axis = axisList[row];
  m_loading->show();
  int32 code = YDDgHelper::clearAxisStatus(axis->device_id, axis->axis_index);

  setReturnState(code, YDStateWidget::tr("状态清除"));
  updateData();
}

void YDStateWidget::slotbtn4Clicked(bool) {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) row = 0;
  auto axis = axisList[row];
  m_loading->show();
  int32 code = YDDgHelper::zeroAxisPosition(axis->device_id, axis->axis_index);

  setReturnState(code, YDStateWidget::tr("位置清零"));
  updateData();
}

void YDStateWidget::slotbtn5Clicked(bool) {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) row = 0;
  auto axis = axisList[row];
  YDDgHelper::startHomeMove(axis->device_id, axis->axis_index);

  updateData();
}
