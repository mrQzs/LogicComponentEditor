#include "YDCylinderInfo.h"

#include <QComboBox.h>

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>

#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDCylinderInfo::YDCylinderInfo(QWidget *parent)
    : QWidget{parent},
      m_nameLab{new QLabel(this)},
      m_nameEdit{new YDNameLineEdit(this)},
      m_dirName1{new QLabel(this)},
      m_dirEdit1{new QLineEdit(this)},
      m_dirName2{new QLabel(this)},
      m_dirEdit2{new QLineEdit(this)},
      m_typeLab{new QLabel(this)},
      m_typeCombo{new QComboBox(this)},
      m_single{new QCheckBox(this)},
      m_elec1Combo{new QComboBox(this)},
      m_double{new QCheckBox(this)},
      m_elec2Combo{new QComboBox(this)},
      m_tabWidget(new QTabWidget(this)) {
  setWindowTitle(YDCylinderInfo::tr("修改气油缸"));

  init();

  QString deviceName;
  auto dtypes = YDProjectManage::getPredefinedDeviceTypes();
  for (auto d : dtypes) {
    if (d->id == DEVICE_TYPE_ID_CYLINDER)
      deviceName = QString("%1 %2").arg(QString::fromLocal8Bit(d->vendor),
                                        QString::fromLocal8Bit(d->model));
  }

  m_typeCombo->addItem(deviceName);

  auto glay = new QGridLayout;
  glay->addWidget(m_nameLab, 0, 0, 1, 1);
  glay->addWidget(m_nameEdit, 0, 1, 1, 1);
  glay->addWidget(m_dirName1, 1, 0, 1, 1);
  glay->addWidget(m_dirEdit1, 1, 1, 1, 1);
  glay->addWidget(m_dirName2, 2, 0, 1, 1);
  glay->addWidget(m_dirEdit2, 2, 1, 1, 1);
  glay->addWidget(m_typeLab, 3, 0, 1, 1);
  glay->addWidget(m_typeCombo, 3, 1, 1, 1);
  glay->addWidget(m_single, 4, 0, 1, 1);
  glay->addWidget(m_elec1Combo, 4, 1, 1, 1);
  glay->addWidget(m_double, 5, 0, 1, 1);
  glay->addWidget(m_elec2Combo, 5, 1, 1, 1);

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(glay);
  vlay->addWidget(m_tabWidget);
  vlay->addStretch();

  vlay->setStretch(0, 1);
  vlay->setStretch(1, 1);
  vlay->setStretch(2, 2);

  m_nameLab->setText(YDCylinderInfo::tr("名称"));
  m_typeLab->setText(YDCylinderInfo::tr("设备类型"));
  m_single->setText(YDCylinderInfo::tr("单线圈电磁阀"));
  m_double->setText(YDCylinderInfo::tr("双线圈电磁阀"));

  m_dirName1->setText(YDCylinderInfo::tr("运动方向1"));
  m_dirName2->setText(YDCylinderInfo::tr("运动方向2"));

  m_dirEdit1->setText(YDCylinderInfo::tr("前进"));
  m_dirEdit2->setText(YDCylinderInfo::tr("后退"));

  updateData();

  m_elec2Combo->hide();

  m_single->setChecked(true);

  connect(m_single, &QCheckBox::clicked, this,
          &YDCylinderInfo::slotSingleCheck);
  connect(m_double, &QCheckBox::clicked, this,
          &YDCylinderInfo::slotDoubleCheck);

  connect(m_dirEdit1, &QLineEdit::textChanged, this,
          &YDCylinderInfo::slotDirName1Changed);

  connect(m_dirEdit2, &QLineEdit::textChanged, this,
          &YDCylinderInfo::slotDirName2Changed);

  setdis();
}

QStringList YDCylinderInfo::textList() const {
  QStringList list;
  list << m_nameEdit->text() << m_dirEdit1->text() << m_dirEdit2->text();
  if (m_single->isChecked())
    list << "single" << m_elec1Combo->currentText();
  else
    list << "double" << m_elec1Combo->currentText()
         << m_elec2Combo->currentText();

  list << QString::number(m_wayComboF->currentIndex());
  list << m_inputComboF->currentText();
  list << m_delayEditF->text();
  list << m_alarmEditF->text();

  list << QString::number(m_wayComboB->currentIndex());
  list << m_inputComboB->currentText();
  list << m_delayEditB->text();
  list << m_alarmEditB->text();
  return list;
}

void YDCylinderInfo::setTextList(const QStringList &infos) {
  updateData();
  m_nameEdit->setText(infos[0]);
  m_dirEdit1->setText(infos[1]);
  m_dirEdit2->setText(infos[2]);
  int index = 5;
  if (infos[3] == "single") {
    m_single->setChecked(true);
    m_double->setChecked(false);
    slotSingleCheck(true);
    m_elec1Combo->setCurrentText(infos[4]);
  } else {
    index = 6;
    m_single->setChecked(false);
    m_double->setChecked(true);
    slotDoubleCheck(true);
    m_elec1Combo->setCurrentText(infos[4]);
    m_elec2Combo->setCurrentText(infos[5]);
  }

  int tindex = infos[index].toUInt();
  switch (tindex) {
    case 0:
      m_wayComboF->setCurrentIndex(0);
      m_delayEditF->setText(infos[index + 2]);
      break;
    case 1:
      m_wayComboF->setCurrentIndex(1);
      m_inputComboF->setCurrentText(infos[index + 1]);
      m_delayEditF->setText("0");
      break;
    case 2:
      m_wayComboF->setCurrentIndex(2);
      m_inputComboF->setCurrentText(infos[index + 1]);
      m_delayEditF->setText(infos[index + 2]);
      break;
    case 3:
      m_wayComboF->setCurrentIndex(3);
      m_inputComboF->setCurrentText(infos[index + 1]);
      m_delayEditF->setText(infos[index + 2]);
      break;
    default:
      break;
  }
  m_alarmEditF->setText(infos[index + 3]);
  index += 4;

  tindex = infos[index].toUInt();
  switch (tindex) {
    case 0:
      m_wayComboB->setCurrentIndex(0);
      m_delayEditB->setText(infos[index + 2]);
      break;
    case 1:
      m_wayComboB->setCurrentIndex(1);
      m_inputComboB->setCurrentText(infos[index + 1]);
      m_delayEditB->setText("0");
      break;
    case 2:
      m_wayComboB->setCurrentIndex(2);
      m_inputComboB->setCurrentText(infos[index + 1]);
      m_delayEditB->setText(infos[index + 2]);
      break;
    case 3:
      m_wayComboB->setCurrentIndex(3);
      m_inputComboB->setCurrentText(infos[index + 1]);
      m_delayEditB->setText(infos[index + 2]);
      break;
    default:
      break;
  }
  m_alarmEditB->setText(infos[index + 3]);
  setdis();
}

void YDCylinderInfo::slotSingleCheck(bool b) {
  if (b) {
    m_elec2Combo->hide();
    m_double->setChecked(false);
  } else
    m_single->setChecked(true);
}

void YDCylinderInfo::slotDoubleCheck(bool b) {
  if (b) {
    m_elec2Combo->show();
    m_single->setChecked(false);
  } else
    m_double->setChecked(true);
}

void YDCylinderInfo::slotWayFSelect(int index) {
  if (0 == index) {
    m_inputComboF->setDisabled(true);
  } else {
    m_inputComboF->setEnabled(true);
  }

  QStringList list;
  list << "";
  m_inputComboF->clear();

  if (3 == index) {
    m_inputLabF->setText(YDCylinderInfo::tr("轴"));
    auto axisList = YDProjectManage::getAxisList();
    for (auto a : axisList) {
      QString name = QString::fromLocal8Bit(a->axis_name.c_str());
      list << name;
    }
    m_delayLabF->setText(YDCylinderInfo::tr("编码器值(mm)"));
    m_delayEditF->setText("0");
  } else {
    m_inputLabF->setText(YDCylinderInfo::tr("输入"));
    auto varList = YDProjectManage::getDIInfos();
    for (auto a : varList) {
      QString name = QString::fromLocal8Bit(a->io_name.c_str());
      list << name;
    }
    m_delayLabF->setText(YDCylinderInfo::tr("延迟时间(ms)"));
  }
  m_inputComboF->addItems(list);
  setdis();
}

void YDCylinderInfo::slotWayBSelect(int index) {
  if (0 == index) {
    m_inputComboB->setDisabled(true);
  } else {
    m_inputComboB->setEnabled(true);
  }

  QStringList list;
  list << "";
  m_inputComboB->clear();

  if (3 == index) {
    m_inputLabB->setText(YDCylinderInfo::tr("轴"));
    auto axisList = YDProjectManage::getAxisList();
    for (auto a : axisList) {
      QString name = QString::fromLocal8Bit(a->axis_name.c_str());
      list << name;
    }
    m_delayLabB->setText(YDCylinderInfo::tr("编码器值(mm)"));
    m_delayEditB->setText("0");
  } else {
    m_inputLabB->setText(YDCylinderInfo::tr("输入"));
    auto varList = YDProjectManage::getDIInfos();
    for (auto a : varList) {
      QString name = QString::fromLocal8Bit(a->io_name.c_str());
      list << name;
    }
    m_delayLabB->setText(YDCylinderInfo::tr("延迟时间(ms)"));
  }
  m_inputComboB->addItems(list);
  setdis();
}

void YDCylinderInfo::slotDirName1Changed(const QString &str) {
  m_tabWidget->setTabText(0, str);
}

void YDCylinderInfo::slotDirName2Changed(const QString &str) {
  m_tabWidget->setTabText(1, str);
}

void YDCylinderInfo::init() {
  auto w1 = new QWidget(this);
  m_wayLabF = new QLabel(w1);
  m_wayComboF = new QComboBox(w1);
  m_inputLabF = new QLabel(w1);
  m_inputComboF = new QComboBox(w1);
  m_delayLabF = new QLabel(w1);
  m_delayEditF = new QLineEdit(w1);
  m_alarmLabF = new QLabel(w1);
  m_alarmEditF = new QLineEdit(w1);

  auto glay = new QGridLayout(w1);
  glay->addWidget(m_wayLabF, 0, 0, 1, 1);
  glay->addWidget(m_wayComboF, 0, 1, 1, 1);
  glay->addWidget(m_inputLabF, 1, 0, 1, 1);
  glay->addWidget(m_inputComboF, 1, 1, 1, 1);
  glay->addWidget(m_delayLabF, 2, 0, 1, 1);
  glay->addWidget(m_delayEditF, 2, 1, 1, 1);
  glay->addWidget(m_alarmLabF, 3, 0, 1, 1);
  glay->addWidget(m_alarmEditF, 3, 1, 1, 1);

  m_wayLabF->setText(YDCylinderInfo::tr("到位方式"));
  m_inputLabF->setText(YDCylinderInfo::tr("输入"));
  m_delayLabF->setText(YDCylinderInfo::tr("延迟时间(ms)"));
  m_alarmLabF->setText(YDCylinderInfo::tr("报警时间(ms)"));

  auto w2 = new QWidget(this);
  m_wayLabB = new QLabel(w2);
  m_wayComboB = new QComboBox(w2);
  m_inputLabB = new QLabel(w2);
  m_inputComboB = new QComboBox(w2);
  m_delayLabB = new QLabel(w2);
  m_delayEditB = new QLineEdit(w2);
  m_alarmLabB = new QLabel(w2);
  m_alarmEditB = new QLineEdit(w2);

  auto glay2 = new QGridLayout(w2);
  glay2->addWidget(m_wayLabB, 0, 0, 1, 1);
  glay2->addWidget(m_wayComboB, 0, 1, 1, 1);
  glay2->addWidget(m_inputLabB, 1, 0, 1, 1);
  glay2->addWidget(m_inputComboB, 1, 1, 1, 1);
  glay2->addWidget(m_delayLabB, 2, 0, 1, 1);
  glay2->addWidget(m_delayEditB, 2, 1, 1, 1);
  glay2->addWidget(m_alarmLabB, 3, 0, 1, 1);
  glay2->addWidget(m_alarmEditB, 3, 1, 1, 1);

  m_wayLabB->setText(YDCylinderInfo::tr("到位方式"));
  m_inputLabB->setText(YDCylinderInfo::tr("输入"));
  m_delayLabB->setText(YDCylinderInfo::tr("延迟时间(ms)"));
  m_alarmLabB->setText(YDCylinderInfo::tr("报警时间(ms)"));

  QStringList ways;
  ways << YDCylinderInfo::tr("延迟等待") << YDCylinderInfo::tr("DI有效到位")
       << YDCylinderInfo::tr("DI有效+延迟等待到位")
       << YDCylinderInfo::tr("编码器到位");

  m_wayComboF->addItems(ways);
  m_wayComboB->addItems(ways);

  m_delayEditF->setText("5000");
  m_alarmEditF->setText("20000");

  m_delayEditB->setText("5000");
  m_alarmEditB->setText("20000");

  m_inputComboF->setDisabled(true);
  m_inputComboB->setDisabled(true);

  m_tabWidget->addTab(w1, YDCylinderInfo::tr("前进"));
  m_tabWidget->addTab(w2, YDCylinderInfo::tr("后退"));

  connect(m_wayComboF, &QComboBox::currentIndexChanged, this,
          &YDCylinderInfo::slotWayFSelect);
  connect(m_wayComboB, &QComboBox::currentIndexChanged, this,
          &YDCylinderInfo::slotWayBSelect);
}

void YDCylinderInfo::setdis() {
  m_nameEdit->setDisabled(true);
  m_dirEdit1->setDisabled(true);
  m_dirEdit2->setDisabled(true);
  m_typeCombo->setDisabled(true);
  m_single->setDisabled(true);
  m_elec1Combo->setDisabled(true);
  m_double->setDisabled(true);
  m_elec2Combo->setDisabled(true);
  m_wayComboF->setDisabled(true);
  m_inputComboF->setDisabled(true);
  m_delayEditF->setDisabled(true);
  m_alarmEditF->setDisabled(true);

  m_wayComboB->setDisabled(true);
  m_inputComboB->setDisabled(true);
  m_delayEditB->setDisabled(true);
  m_alarmEditB->setDisabled(true);
}

void YDCylinderInfo::updateData() {
  m_elec1Combo->clear();
  m_elec2Combo->clear();
  QStringList list;
  list << "";
  auto varList = YDProjectManage::getDOInfos();
  for (auto a : varList) {
    QString name = QString::fromLocal8Bit(a->io_name.c_str());
    list << name;
  }

  m_elec1Combo->addItems(list);
  m_elec2Combo->addItems(list);

  m_inputComboF->clear();
  m_inputComboB->clear();

  list.clear();
  list << "";
  varList = YDProjectManage::getDIInfos();
  for (auto a : varList) {
    QString name = QString::fromLocal8Bit(a->io_name.c_str());
    list << name;
  }

  m_inputComboF->addItems(list);
  m_inputComboB->addItems(list);
}
