#include "YDSpeedSetWidget.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "YDAXisListView.h"
#include "YDAxisListModel.h"
#include "YDDgHelper.h"
#include "core/YDProjectManage.h"
#include "widget/YDLoadingDialog.h"
#include "widget/YDNameLineEdit.h"

YDSpeedSetWidget::YDSpeedSetWidget(QWidget *parent)
    : QWidget{parent},
      m_view{new YDAXisListView(this)},
      m_model{new YDAxisListModel(this)},
      m_loading{new YDLoadingDialog(this)},
      m_lab1{new QLabel(this)},
      m_edit1{new QLineEdit(this)},
      m_lab2{new QLabel(this)},
      m_edit2{new QLineEdit(this)},
      m_lab3{new QLabel(this)},
      m_edit3{new QLineEdit(this)},
      m_lab4{new QLabel(this)},
      m_edit4{new QLineEdit(this)},
      m_lab5{new QLabel(this)},
      m_edit5{new QLineEdit(this)},
      m_lab6{new QLabel(this)},
      m_edit6{new QLineEdit(this)},
      m_lab7{new QLabel(this)},
      m_edit7{new QLineEdit(this)},
      m_btn{new QPushButton(this)},
      m_btn1(new QPushButton(this)),
      m_state{new QLabel(this)} {
  m_view->setFixedWidth(200);
  m_view->setModel(m_model);

  auto grid = new QGridLayout;
  grid->setSpacing(10);
  grid->addWidget(m_lab1, 0, 0, 1, 3);
  grid->addWidget(m_edit1, 0, 3, 1, 1);
  grid->addWidget(m_lab2, 0, 4, 1, 3);
  grid->addWidget(m_edit2, 0, 7, 1, 1);

  grid->addWidget(m_lab3, 1, 0, 1, 3);
  grid->addWidget(m_edit3, 1, 3, 1, 1);
  grid->addWidget(m_lab4, 1, 4, 1, 3);
  grid->addWidget(m_edit4, 1, 7, 1, 1);

  grid->addWidget(m_lab5, 2, 0, 1, 3);
  grid->addWidget(m_edit5, 2, 3, 1, 1);

  grid->addWidget(m_lab6, 3, 0, 1, 3);
  grid->addWidget(m_edit6, 3, 3, 1, 1);
  grid->addWidget(m_lab7, 3, 4, 1, 3);
  grid->addWidget(m_edit7, 3, 7, 1, 1);

  m_lab1->setAlignment(Qt::AlignRight);
  m_lab2->setAlignment(Qt::AlignRight);
  m_lab3->setAlignment(Qt::AlignRight);
  m_lab4->setAlignment(Qt::AlignRight);
  m_lab5->setAlignment(Qt::AlignRight);
  m_lab6->setAlignment(Qt::AlignRight);
  m_lab7->setAlignment(Qt::AlignRight);

  auto hlay = new QHBoxLayout;
  hlay->setSpacing(40);
  hlay->addStretch();
  hlay->addWidget(m_btn);
  hlay->addWidget(m_btn1);
  hlay->addStretch();
  m_btn->setMinimumWidth(120);
  m_btn1->setMinimumWidth(120);

  auto vlay = new QVBoxLayout;
  vlay->setContentsMargins(20, 20, 20, 100);
  vlay->addLayout(grid);
  vlay->addSpacing(30);
  vlay->addLayout(hlay);
  vlay->addStretch();
  vlay->addWidget(m_state, 0, Qt::AlignBottom);
  vlay->addStretch();

  m_state->setAlignment(Qt::AlignCenter);
  m_state->setFont(QFont("Microsoft YaHei", 16, 75));

  auto hlay3 = new QHBoxLayout(this);
  hlay3->setContentsMargins(0, 0, 0, 0);
  hlay3->setSpacing(10);
  hlay3->addWidget(m_view);
  hlay3->addLayout(vlay);

  m_lab1->setText(YDSpeedSetWidget::tr("最大自动运动速度(毫米/秒)"));
  m_lab2->setText(YDSpeedSetWidget::tr("最大手动运动速度(毫米/秒)"));
  m_lab3->setText(YDSpeedSetWidget::tr("最大自动加速度(毫米/秒平方"));
  m_lab4->setText(YDSpeedSetWidget::tr("最大自动减速度(毫米/秒平方"));
  m_lab5->setText(YDSpeedSetWidget::tr("最大自动起跳速度(毫米/秒"));
  m_lab6->setText(YDSpeedSetWidget::tr("平滑时间"));
  m_lab7->setText(YDSpeedSetWidget::tr("平滑系数"));
  m_btn->setText(YDSpeedSetWidget::tr("获取数据"));
  m_btn1->setText(YDSpeedSetWidget::tr("更新数据"));

  slotupdateData();

  connect(m_btn, &QPushButton::clicked, this,
          &YDSpeedSetWidget::slotBtnClicked);

  connect(m_btn1, &QPushButton::clicked, this,
          &YDSpeedSetWidget::slotBtn1Clicked);

  connect(m_view, &YDAXisListView::clicked, this,
          &YDSpeedSetWidget::slotItemClicked);
}

void YDSpeedSetWidget::updateData() {}

void YDSpeedSetWidget::clearStateInfo() { m_state->clear(); }

void YDSpeedSetWidget::setReturnState(qint32 code, const QString &name) {
  m_loading->close();
  switch (code) {
    case PROJECT_ERROR_NONE:
      m_state->setText(name + YDSpeedSetWidget::tr(": 成功"));
      break;
    default:
      m_state->setText(name + YDSpeedSetWidget::tr(": 失败"));
      break;
  }
}

void YDSpeedSetWidget::slotItemClicked(const QModelIndex &) {
  slotupdateData();
}

void YDSpeedSetWidget::slotBtnClicked(bool) { slotupdateData(); }

void YDSpeedSetWidget::slotBtn1Clicked(bool) {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) row = 0;
  auto axis = axisList[row];

  std::vector<yd::dev::MCAxisMoveSetup *> list;
  YDProjectManage::getMotionAxisMoveSetups(list);

  dev::MCAxisMoveSetup *movesetup = nullptr;
  for (auto ms : list) {
    if (ms->device_id == axis->device_id &&
        ms->axis_index == axis->axis_index) {
      movesetup = ms;
      break;
    }
  }

  movesetup->max_velocity = m_edit1->text().toDouble();
  movesetup->max_manual_velocity = m_edit2->text().toDouble();
  movesetup->max_acceleration = m_edit3->text().toDouble();
  movesetup->max_deceleration = m_edit4->text().toDouble();
  movesetup->takeoff_velocity = m_edit5->text().toDouble();
  movesetup->smooth_time = m_edit6->text().toUInt();
  movesetup->smooth_factor = m_edit7->text().toDouble();
  m_loading->show();
  int32 code = YDDgHelper::setAxisVelocities(axis->device_id, axis->axis_index,
                                             movesetup);
  slotupdateData();
  setReturnState(code, YDSpeedSetWidget::tr("更新数据"));
}

void YDSpeedSetWidget::slotupdateData() {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) row = 0;
  auto axis = axisList[row];

  std::vector<yd::dev::MCAxisMoveSetup *> list;
  m_loading->show();
  YDProjectManage::getMotionAxisMoveSetups(list);

  dev::MCAxisMoveSetup *movesetup = nullptr;
  for (auto ms : list) {
    if (ms->device_id == axis->device_id &&
        ms->axis_index == axis->axis_index) {
      movesetup = ms;
      break;
    }
  }

  if (movesetup) {
    m_edit1->setText(QString::number(movesetup->max_velocity));
    m_edit2->setText(QString::number(movesetup->max_manual_velocity));
    m_edit3->setText(QString::number(movesetup->max_acceleration));
    m_edit4->setText(QString::number(movesetup->max_deceleration));
    m_edit5->setText(QString::number(movesetup->takeoff_velocity));
    m_edit6->setText(QString::number(movesetup->smooth_time));
    m_edit7->setText(QString::number(movesetup->smooth_factor));
    setReturnState(0, YDSpeedSetWidget::tr("获取数据"));
  } else {
    setReturnState(1, YDSpeedSetWidget::tr("获取数据"));
  }
}
