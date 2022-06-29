#include "YDAboutDialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

YDAboutDialog::YDAboutDialog(QWidget *parent)
    : QDialog{parent},
      m_versionLabel{new QLabel("软件版本: 1.1.0", this)},
      m_confirmBtn{new QPushButton(YDAboutDialog::tr("确认"), this)} {
  auto vLayout = new QVBoxLayout(this);
  auto hLayout1 = new QHBoxLayout;
  auto hLayout2 = new QHBoxLayout;
  hLayout1->addStretch();
  hLayout1->addWidget(m_versionLabel);
  hLayout1->addStretch();
  hLayout2->addStretch();
  hLayout2->addWidget(m_confirmBtn);
  vLayout->addLayout(hLayout1);
  vLayout->addLayout(hLayout2);
  vLayout->setSpacing(20);
  vLayout->setContentsMargins(5, 20, 5, 10);

  setWindowTitle(YDAboutDialog::tr("关于软件"));
  connect(m_confirmBtn, &QPushButton::clicked, this,
          &YDAboutDialog::SlotConfirmClicked);
}

void YDAboutDialog::SlotConfirmClicked() { close(); }
