#include "YDAddDeviceDialog.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "widget/YDDeviceTypeComboBox.h"
#include "widget/YDNameLineEdit.h"

YDAddDeviceDialog::YDAddDeviceDialog(const QString &title, QWidget *parent)
    : YDDialog{parent},
      m_nameLab{new QLabel(this)},
      m_nameEdit{new YDNameLineEdit(this)},
      m_cardLab{new QLabel(this)},
      m_cardEdit{new QLineEdit(this)},
      m_typeLab{new QLabel(this)},
      m_typeCombo{new YDDeviceTypeComboBox(this)},
      m_configLab{new QLabel(this)},
      m_configEdit{new QLineEdit(this)},
      m_configBtn{new QPushButton(this)},
      m_remarkLab{new QLabel(this)},
      m_remarkEdit{new QLineEdit(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)} {
  setWindowTitle(title);

  auto glay = new QGridLayout;
  glay->addWidget(m_nameLab, 0, 0, 1, 1);
  glay->addWidget(m_nameEdit, 0, 1, 1, 1);
  glay->addWidget(m_cardLab, 1, 0, 1, 1);
  glay->addWidget(m_cardEdit, 1, 1, 1, 1);
  glay->addWidget(m_typeLab, 2, 0, 1, 1);
  glay->addWidget(m_typeCombo, 2, 1, 1, 1);
  glay->addWidget(m_configLab, 3, 0, 1, 1);
  glay->addWidget(m_remarkLab, 4, 0, 1, 1);
  glay->addWidget(m_remarkEdit, 4, 1, 1, 1);

  auto hlay1 = new QHBoxLayout;
  hlay1->addWidget(m_configEdit);
  hlay1->addWidget(m_configBtn);
  glay->addLayout(hlay1, 3, 1, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_okBtn);
  hlay->addStretch();
  hlay->addWidget(m_cancelBtn);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(glay);
  vlay->addLayout(hlay);

  m_nameLab->setText(YDAddDeviceDialog::tr("名称"));
  m_cardLab->setText(YDAddDeviceDialog::tr("卡号"));
  m_typeLab->setText(YDAddDeviceDialog::tr("硬件类型"));
  m_configLab->setText(YDAddDeviceDialog::tr("配置文件"));
  m_configBtn->setText(YDAddDeviceDialog::tr("选择"));
  m_remarkLab->setText(YDAddDeviceDialog::tr("备注"));

  m_okBtn->setText(YDAddDeviceDialog::tr("确认"));
  m_cancelBtn->setText(YDAddDeviceDialog::tr("取消"));

  m_configEdit->setText("configs/GTS800.cfg");

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDAddDeviceDialog::slotOkBtnClicked);

  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDAddDeviceDialog::slotCancelBtnClicked);
}

QStringList YDAddDeviceDialog::textList() const {
  QStringList list;
  list << m_nameEdit->text() << m_cardEdit->text() << m_typeCombo->currentText()
       << m_configEdit->text() << m_remarkEdit->text();
  return list;
}

void YDAddDeviceDialog::setTextList(const QStringList &infos) {
  m_nameEdit->setText(infos[0]);
  m_cardEdit->setText(infos[1]);
  auto index = m_typeCombo->findText(infos[2]);
  if (index >= 0) m_typeCombo->setCurrentIndex(index);
  m_typeCombo->setDisabled(true);

  m_configEdit->setText(infos[3]);
  m_remarkEdit->setText(infos[4]);
}

void YDAddDeviceDialog::slotOkBtnClicked() { accept(); }

void YDAddDeviceDialog::slotCancelBtnClicked() { reject(); }
