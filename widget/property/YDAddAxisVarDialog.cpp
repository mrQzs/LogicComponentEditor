#include "YDAddAxisVarDialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDAddAxisVarDialog::YDAddAxisVarDialog(QWidget *parent)
    : QDialog{parent},
      m_axisLab{new QLabel(this)},
      m_axisBox{new QComboBox(this)},
      m_typeLab{new QLabel(this)},
      m_typeCombo{new QComboBox(this)},
      m_targetLab{new QLabel(this)},
      m_targetEdit{new QLineEdit(this)},
      m_speedLab{new QLabel(this)},
      m_speedBox{new QComboBox(this)},
      m_speedLab2{new QLabel(this)},
      m_speedBox2{new QComboBox(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)} {
  setWindowTitle(YDAddAxisVarDialog::tr("运动坐标属性"));

  auto glay = new QGridLayout;
  glay->addWidget(m_axisLab, 0, 0, 1, 1);
  glay->addWidget(m_axisBox, 0, 1, 1, 1);
  glay->addWidget(m_typeLab, 1, 0, 1, 1);
  glay->addWidget(m_typeCombo, 1, 1, 1, 1);
  glay->addWidget(m_targetLab, 2, 0, 1, 1);
  glay->addWidget(m_targetEdit, 2, 1, 1, 1);
  glay->addWidget(m_speedLab, 3, 0, 1, 1);
  glay->addWidget(m_speedBox, 3, 1, 1, 1);
  glay->addWidget(m_speedLab2, 4, 0, 1, 1);
  glay->addWidget(m_speedBox2, 4, 1, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_okBtn);
  hlay->addStretch();
  hlay->addWidget(m_cancelBtn);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(glay);
  vlay->addLayout(hlay);

  m_axisLab->setText(YDAddAxisVarDialog::tr("运动轴号"));
  m_typeLab->setText(YDAddAxisVarDialog::tr("运动类型"));
  m_targetLab->setText(YDAddAxisVarDialog::tr("目标位置"));
  m_speedLab->setText(YDAddAxisVarDialog::tr("运动速度方式"));
  m_speedLab2->setText(YDAddAxisVarDialog::tr("运动速度"));

  m_okBtn->setText(YDAddAxisVarDialog::tr("确认"));
  m_cancelBtn->setText(YDAddAxisVarDialog::tr("取消"));

  m_speedBox->addItem(YDAddAxisVarDialog::tr("百分比"));
  m_speedBox->addItem(YDAddAxisVarDialog::tr("变量"));

  QStringList list;
  list << YDAddAxisVarDialog::tr("绝对运动")
       << YDAddAxisVarDialog::tr("相对运动")
       << YDAddAxisVarDialog::tr("Jog运动");

  m_typeCombo->addItems(list);
  m_typeCombo->setCurrentIndex(0);
  m_typeCombo->setDisabled(true);

  QStringList axlist;
  auto vars = YDProjectManage::getAxisList();
  for (auto v : vars)
    axlist << QString("%1").arg(QString::fromLocal8Bit(v->axis_name.c_str()));
  m_axisBox->addItems(axlist);

  m_enum << "0%"
         << "5%"
         << "10%"
         << "15%"
         << "20%"
         << "25%"
         << "30%"
         << "35%"
         << "40%"
         << "45%"
         << "50%"
         << "55%"
         << "60%"
         << "65%"
         << "70%"
         << "75%"
         << "80%"
         << "85%"
         << "90%"
         << "95%"
         << "100%";

  m_speedBox2->addItems(m_enum);

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDAddAxisVarDialog::slotOkBtnClicked);

  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDAddAxisVarDialog::slotCancelBtnClicked);

  connect(m_speedBox, &QComboBox::currentIndexChanged, this,
          &YDAddAxisVarDialog::slotWayChanged);

  resize(340, 120);
}

QString YDAddAxisVarDialog::text() {
  QString str;
  str += QString("%1@").arg(m_axisBox->currentText());
  str += QString("%1@").arg(m_typeCombo->currentText());
  str += QString("%1@").arg(m_targetEdit->text());
  str += QString("%1@").arg(m_speedBox->currentText());
  str += QString("%1").arg(m_speedBox2->currentText());
  return str;
}

void YDAddAxisVarDialog::setText(const QString &str) {
  auto list = str.split('@');
  m_axisBox->setCurrentText(list[0]);
  m_typeCombo->setCurrentText(list[1]);
  m_targetEdit->setText(list[2]);
  int index = m_speedBox->findText(list[3]);
  if (index < 0) index = 0;
  m_speedBox->setCurrentIndex(index);
  slotWayChanged(index);
  m_speedBox2->setCurrentText(list[4]);
}

void YDAddAxisVarDialog::slotOkBtnClicked() { accept(); }

void YDAddAxisVarDialog::slotCancelBtnClicked() { reject(); }

void YDAddAxisVarDialog::slotWayChanged(int index) {
  m_enum.clear();
  if (0 == index) {
    m_enum << "0%"
           << "5%"
           << "10%"
           << "15%"
           << "20%"
           << "25%"
           << "30%"
           << "35%"
           << "40%"
           << "45%"
           << "50%"
           << "55%"
           << "60%"
           << "65%"
           << "70%"
           << "75%"
           << "80%"
           << "85%"
           << "90%"
           << "95%"
           << "100%";
  } else {
    m_enum << "";
    auto varList = YDProjectManage::getAllVirtualVariables();
    for (auto a : varList) {
      QString name = QString::fromLocal8Bit(a->variable_name.c_str(),
                                            a->variable_name.size());
      m_enum << name;
    }
  }

  m_speedBox2->clear();
  m_speedBox2->addItems(m_enum);
}
