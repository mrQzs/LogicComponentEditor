#include "YDAddAxisWaitDialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QValidator>

#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDAddAxisWaitDialog::YDAddAxisWaitDialog(QWidget* parent)
    : QDialog{parent},
      m_axisLab{new QLabel(this)},
      m_axisBox{new QComboBox(this)},
      m_wayLab{new QLabel(this)},
      m_wayBox{new QComboBox(this)},
      m_valueLab{new QLabel(this)},
      m_valueEdit{new QLineEdit(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)} {
  setWindowTitle(YDAddAxisWaitDialog::tr("添加轴等待配置"));
  auto glay = new QGridLayout;
  glay->addWidget(m_axisLab, 0, 0, 1, 1);
  glay->addWidget(m_axisBox, 0, 1, 1, 1);
  glay->addWidget(m_wayLab, 1, 0, 1, 1);
  glay->addWidget(m_wayBox, 1, 1, 1, 1);
  glay->addWidget(m_valueLab, 2, 0, 1, 1);
  glay->addWidget(m_valueEdit, 2, 1, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_okBtn);
  hlay->addWidget(m_cancelBtn);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(glay);
  vlay->addLayout(hlay);

  m_axisLab->setText(YDAddAxisWaitDialog::tr("运动轴号"));
  m_wayLab->setText(YDAddAxisWaitDialog::tr("等待类型"));
  m_valueLab->setText(YDAddAxisWaitDialog::tr("等待数值"));
  m_okBtn->setText(YDAddAxisWaitDialog::tr("确定"));
  m_cancelBtn->setText(YDAddAxisWaitDialog::tr("取消"));

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDAddAxisWaitDialog::slotOkBtnClicked);
  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDAddAxisWaitDialog::slotCancelBtnClicked);

  QStringList list;
  auto vars = YDProjectManage::getAxisList();
  for (auto v : vars)
    list << QString("%1").arg(QString::fromLocal8Bit(v->axis_name.c_str()));
  m_axisBox->addItems(list);

  QStringList waittype;
  waittype << YDAddAxisWaitDialog::tr("不等待")
           << YDAddAxisWaitDialog::tr("规划运动停止")
           << YDAddAxisWaitDialog::tr("默认误差带")
           << YDAddAxisWaitDialog::tr("自定义误差带");
  m_wayBox->addItems(waittype);

  connect(m_wayBox, &QComboBox::currentIndexChanged, this,
          &YDAddAxisWaitDialog::slotWayChanged);

  m_valueLab->hide();
  m_valueEdit->hide();
}

QString YDAddAxisWaitDialog::text() {
  QString str;
  str += m_axisBox->currentText() + "@";
  str += m_wayBox->currentText() + "@";
  if (m_wayBox->currentIndex() == 3) {
    str += m_valueEdit->text();
  } else
    str += "";
  return str;
}

void YDAddAxisWaitDialog::setText(const QString& str) {
  auto list = str.split('@');
  m_axisBox->setCurrentText(list[0]);
  m_wayBox->setCurrentText(list[1]);
  if (m_wayBox->currentIndex() != 3) {
    m_valueLab->hide();
    m_valueEdit->hide();
  } else {
    m_valueLab->show();
    m_valueEdit->show();
    m_valueEdit->setText(list[2]);
  }
}

void YDAddAxisWaitDialog::slotOkBtnClicked() {
  if (3 == m_wayBox->currentIndex() && m_valueEdit->text().isEmpty()) {
    QMessageBox::warning(this, YDAddAxisWaitDialog::tr("错误"),
                         YDAddAxisWaitDialog::tr("值不能为空!"));
  } else
    accept();
}

void YDAddAxisWaitDialog::slotCancelBtnClicked() { reject(); }

void YDAddAxisWaitDialog::slotWayChanged(int index) {
  if (index == 3) {
    m_valueLab->show();
    m_valueEdit->show();
  } else {
    m_valueLab->hide();
    m_valueEdit->hide();
  }
}
