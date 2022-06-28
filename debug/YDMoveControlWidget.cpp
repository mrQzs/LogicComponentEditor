#include "YDMoveControlWidget.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSlider>

#include "YDAXisListView.h"
#include "YDAxisListModel.h"
#include "YDJogButton.h"
#include "YDState.h"
#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDMoveControlWidget::YDMoveControlWidget(QWidget *parent)
    : QWidget{parent},
      m_view{new YDAXisListView(this)},
      m_model{new YDAxisListModel(this)},
      m_lab1{new QLabel(this)},
      m_cbox1{new QCheckBox(this)},
      m_cbox2{new QCheckBox(this)},
      m_lab2{new QLabel(this)},
      m_sliderLab{new QLabel(this)},
      m_slider{new QSlider(Qt::Horizontal, this)},
      m_lab3{new QLabel(this)},
      m_edit3{new QLineEdit(this)},
      m_lab4{new QLabel(this)},
      m_lab5{new QLabel(this)},
      m_edit5{new QLineEdit(this)},
      m_lab6{new QLabel(this)},
      m_edit6{new QLineEdit(this)},
      m_lab7{new QLabel(this)},
      m_lab8{new YDState(this)},
      m_lab9{new YDState(this)},
      m_lab10{new YDState(this)},
      m_lab11{new QLabel(this)},
      m_btn1{new YDJogButton(this)},
      m_btn2{new YDJogButton(this)},
      m_axis{nullptr},
      m_move{nullptr} {
  m_view->setFixedWidth(200);
  m_view->setModel(m_model);

  auto grid = new QGridLayout;
  grid->addWidget(m_lab1, 0, 0, 1, 1);
  grid->addWidget(m_cbox1, 0, 1, 1, 1);
  grid->addWidget(m_cbox2, 0, 2, 1, 1);

  auto hhlay = new QHBoxLayout;
  hhlay->setContentsMargins(0, 0, 0, 0);
  hhlay->setSpacing(5);
  hhlay->addWidget(m_slider);
  hhlay->addWidget(m_sliderLab);

  grid->addWidget(m_lab2, 1, 0, 1, 1);
  grid->addLayout(hhlay, 1, 1, 1, 3);

  grid->addWidget(m_lab3, 2, 0, 1, 1);
  grid->addWidget(m_edit3, 2, 1, 1, 1);
  grid->addWidget(m_lab4, 2, 2, 1, 1);

  grid->addWidget(m_lab5, 3, 0, 1, 1);
  grid->addWidget(m_edit5, 3, 1, 1, 1);
  grid->addWidget(m_lab6, 3, 2, 1, 1);
  grid->addWidget(m_edit6, 3, 3, 1, 1);

  grid->addWidget(m_lab7, 4, 0, 1, 1);
  grid->addWidget(m_lab8, 4, 1, 1, 1);
  grid->addWidget(m_lab9, 4, 2, 1, 1);
  grid->addWidget(m_lab10, 4, 3, 1, 1);

  grid->addWidget(m_lab11, 5, 0, 1, 1);
  grid->addWidget(m_btn1, 5, 1, 1, 1);
  grid->addWidget(m_btn2, 5, 2, 1, 1);

  auto hlay3 = new QHBoxLayout;
  hlay3->addLayout(grid);
  hlay3->addStretch();

  auto vlay = new QVBoxLayout;
  vlay->addLayout(hlay3);
  vlay->addStretch();

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(10);
  hlay->addWidget(m_view);
  hlay->addLayout(vlay);

  m_lab1->setFixedWidth(120);
  m_lab2->setFixedWidth(120);
  m_lab3->setFixedWidth(120);
  m_lab4->setFixedWidth(120);
  m_lab5->setFixedWidth(120);
  m_lab6->setFixedWidth(120);
  m_lab7->setFixedWidth(120);
  m_lab8->setFixedWidth(120);

  m_edit3->setFixedWidth(120);
  m_edit5->setFixedWidth(120);
  m_edit6->setFixedWidth(120);
  m_btn1->setFixedWidth(120);

  m_lab1->setText(YDMoveControlWidget::tr("运动类型:"));
  m_cbox1->setText(YDMoveControlWidget::tr("Jog运动"));
  m_cbox2->setText(YDMoveControlWidget::tr("相对运动"));
  m_lab2->setText(YDMoveControlWidget::tr("运动速度:"));
  m_lab3->setText(YDMoveControlWidget::tr("运动距离:"));
  m_lab4->setText(YDMoveControlWidget::tr("毫米"));
  m_lab5->setText(YDMoveControlWidget::tr("规划位置:"));
  m_lab6->setText(YDMoveControlWidget::tr("编码器位置:"));

  m_lab7->setText(YDMoveControlWidget::tr("轴状态:"));

  m_lab8->setMidText(YDMoveControlWidget::tr("正限位"));
  m_lab9->setMidText(YDMoveControlWidget::tr("负限位"));
  m_lab10->setMidText(YDMoveControlWidget::tr("原点"));

  m_lab11->setText(YDMoveControlWidget::tr("运动控制:"));
  m_btn1->setText(YDMoveControlWidget::tr("正向"));
  m_btn2->setText(YDMoveControlWidget::tr("反向"));

  m_cbox1->setChecked(true);
  m_cbox2->setChecked(false);

  connect(m_cbox1, &QCheckBox::clicked, this,
          &YDMoveControlWidget::box1checked);

  connect(m_cbox2, &QCheckBox::clicked, this,
          &YDMoveControlWidget::box2checked);

  m_slider->setMinimum(1);
  m_slider->setMaximum(100);

  m_sliderLab->setText(QString("%1%").arg(QString::number(m_slider->value())));

  connect(m_slider, &QSlider::valueChanged, this,
          &YDMoveControlWidget::sliderchanged);

  connect(m_edit3, &QLineEdit::textChanged, this,
          &YDMoveControlWidget::textChanged);

  int count = m_view->model()->rowCount(QModelIndex());
  for (int i = 0; i < count; ++i) m_slideMap[i] = 1;

  m_edit5->setDisabled(true);
  m_edit6->setDisabled(true);

  connect(m_btn1, &YDJogButton::sigStart, this,
          &YDMoveControlWidget::slotJogStart);

  connect(m_btn1, &YDJogButton::sigStop, this,
          &YDMoveControlWidget::slotJogStop);

  connect(m_btn2, &YDJogButton::sigStart, this,
          &YDMoveControlWidget::slotDJogStart);

  connect(m_btn2, &YDJogButton::sigStop, this,
          &YDMoveControlWidget::slotDJogStop);

  connect(m_view, &YDAXisListView::clicked, this,
          &YDMoveControlWidget::slotViewClicked);
}

void YDMoveControlWidget::updateData() {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) return;
  qDebug() << "Row: " << row;
  auto axis = axisList[row];
  yd::proto::AxisState axisState;
  YDDgHelper::getAxisState(axis->device_id, axis->axis_index, &axisState);

  m_edit5->setText(QString::number(axisState.profile_position));
  m_edit6->setText(QString::number(axisState.encoder_position));

  m_lab8->setState(axisState.positive_limit);
  m_lab9->setState(axisState.negative_limit);
  m_lab10->setState(axisState.home_signal);

  m_slider->setValue(m_slideMap[row]);
  m_sliderLab->setText(QString("%1%").arg(QString::number(m_slider->value())));

  update();
}

int YDMoveControlWidget::getSliderValue(int row) const {
  return m_slideMap[row];
}

double YDMoveControlWidget::getDistance(int row) const {
  return m_distanceMap[row];
}

void YDMoveControlWidget::box1checked(bool b) {
  m_cbox1->setChecked(b);
  m_cbox2->setChecked(!b);
}

void YDMoveControlWidget::box2checked(bool b) {
  m_cbox1->setChecked(!b);
  m_cbox2->setChecked(b);
}

void YDMoveControlWidget::sliderchanged(int value) {
  m_sliderLab->setText(QString("%1%").arg(QString::number(value)));
  auto row = m_view->currentIndex().row();
  if (row < 0) return;
  m_slideMap[row] = value;
}

void YDMoveControlWidget::slotViewClicked(const QModelIndex &index) {
  qDebug() << index.row();
  updateData();
}

void YDMoveControlWidget::slotJogStart() {
  if (m_cbox1->checkState() == Qt::Checked) {
    if (!setData()) return;

    double value = (m_slider->value() * 1.0) / 100.0;
    value = value * m_move->max_manual_velocity;
    std::string speed = QString::number(value).toUtf8().toStdString();
    YDDgHelper::startJogMove(m_axis->device_id, m_axis->axis_index, false,
                             speed, 1);
  }
}

void YDMoveControlWidget::slotJogStop() {
  if (m_cbox1->checkState() == Qt::Checked) {
    YDDgHelper::stopAxisMove(m_axis->device_id, m_axis->axis_index, true);
  } else {
    if (m_edit3->text().isEmpty()) {
      QMessageBox::warning(nullptr, QObject::tr("错误"),
                           QObject::tr("运动距离不能为空!"));
      return;
    }
    if (!setData()) return;

    std::string val = m_edit3->text().toUtf8().toStdString();
    double value = (m_slider->value() * 1.0) / 100.0;
    value = value * m_move->max_manual_velocity;
    std::string speed = QString::number(value).toUtf8().toStdString();

    YDDgHelper::startRelativeMove(m_axis->device_id, m_axis->axis_index, false,
                                  val, false, speed, 1);
  }
}

void YDMoveControlWidget::slotDJogStart() {
  if (m_cbox1->checkState() == Qt::Checked) {
    if (!setData()) return;

    double value = (m_slider->value() * 1.0) / 100.0;
    value = value * m_move->max_manual_velocity;
    std::string speed = QString::number(value).toUtf8().toStdString();
    YDDgHelper::startJogMove(m_axis->device_id, m_axis->axis_index, false,
                             speed, 2);
  }
}

void YDMoveControlWidget::slotDJogStop() {
  if (m_cbox1->checkState() == Qt::Checked) {
    YDDgHelper::stopAxisMove(m_axis->device_id, m_axis->axis_index, true);
  } else {
    if (m_edit3->text().isEmpty()) {
      QMessageBox::warning(nullptr, QObject::tr("错误"),
                           QObject::tr("运动距离不能为空!"));
      return;
    }

    if (!setData()) return;

    std::string val = m_edit3->text().toUtf8().toStdString();
    double value = (m_slider->value() * 1.0) / 100.0;
    value = value * m_move->max_manual_velocity;
    std::string speed = QString::number(value).toUtf8().toStdString();

    YDDgHelper::startRelativeMove(m_axis->device_id, m_axis->axis_index, false,
                                  val, false, speed, 2);
  }
}

void YDMoveControlWidget::textChanged(const QString &str) {}

bool YDMoveControlWidget::setData() {
  auto row = m_view->currentIndex().row();
  auto axisList = YDProjectManage::getAxisList();
  if (row < 0 && row >= axisList.size()) return false;
  m_axis = axisList[row];

  std::vector<yd::dev::MCAxisMoveSetup *> list;
  YDProjectManage::getMotionAxisMoveSetups(list);

  for (auto ms : list) {
    if (ms->device_id == m_axis->device_id &&
        ms->axis_index == m_axis->axis_index) {
      m_move = ms;
      return true;
    }
  }
  return false;
}
