#include "YDNetSetDialog.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"
#include "widget/base/YDIPLineEdit.h"
#include "widget/base/YDIntLineEdit.h"

YDNetSetDialog::YDNetSetDialog(QWidget *parent)
    : QDialog{parent},
      m_ipLab{new QLabel(this)},
      m_ipEdit{new YDIPLineEdit(this)},
      m_portLab{new QLabel(this)},
      m_portEdit{new YDIntLineEdit(this)},
      m_timeLab{new QLabel(this)},
      m_timeEdit{new YDIntLineEdit(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)} {
  setWindowTitle(YDNetSetDialog::tr("后台数据网关"));

  auto grid = new QGridLayout;
  grid->addWidget(m_ipLab, 0, 0, 1, 1);
  grid->addWidget(m_ipEdit, 0, 1, 1, 1);
  grid->addWidget(m_portLab, 1, 0, 1, 1);
  grid->addWidget(m_portEdit, 1, 1, 1, 1);
  grid->addWidget(m_timeLab, 2, 0, 1, 1);
  grid->addWidget(m_timeEdit, 2, 1, 1, 1);

  QHBoxLayout *hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_okBtn);
  hlay->addWidget(m_cancelBtn);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(grid);
  vlay->addLayout(hlay);

  m_ipLab->setText(YDNetSetDialog::tr("网关地址:"));
  m_portLab->setText(YDNetSetDialog::tr("网关端口:"));
  m_timeLab->setText(YDNetSetDialog::tr("超时时间:"));

  m_okBtn->setText(YDNetSetDialog::tr("确定"));
  m_cancelBtn->setText(YDNetSetDialog::tr("取消"));

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDNetSetDialog::slotOkBtnClicked);
  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDNetSetDialog::slotCancelBtnclicked);

  std::string strAddress = "";
  uint16 usPort = 0;
  uint32 uiTimeout = 0;
  YDProjectManage::GetDataGateway(strAddress, usPort, uiTimeout);

  if (strAddress.empty()) {
    m_ipEdit->setText("127.0.0.1");
    m_portEdit->setText("40001");
    m_timeEdit->setText("1000");
  } else {
    m_ipEdit->setText(STRTQSTR(strAddress));
    m_portEdit->setText(QString::number(usPort));
    m_timeEdit->setText(QString::number(uiTimeout));
  }
}

QString YDNetSetDialog::getIP() const { return m_ipEdit->text(); }

QString YDNetSetDialog::getPort() const { return m_portEdit->text(); }

QString YDNetSetDialog::getTime() const { return m_timeEdit->text(); }

void YDNetSetDialog::slotOkBtnClicked(bool) {
  if (m_ipEdit->text().isEmpty() || m_portEdit->text().isEmpty() ||
      m_timeEdit->text().isEmpty()) {
    QMessageBox::warning(this, YDNetSetDialog::tr("错误"),
                         YDNetSetDialog::tr("值不能为空!"));
  } else
    accept();
}

void YDNetSetDialog::slotCancelBtnclicked(bool) { reject(); }
