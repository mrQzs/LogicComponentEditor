#include "YDBackPointDialog.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

YDBackPointDialog::YDBackPointDialog(QWidget *parent)
    : QDialog{parent},
      m_platLab{new QLabel(this)},
      m_platBox{new QComboBox(this)},
      m_ok{new QPushButton(this)},
      m_cancel{new QPushButton(this)} {
  auto hlay1 = new QHBoxLayout;
  hlay1->addWidget(m_platLab);
  hlay1->addWidget(m_platBox);

  auto hlay2 = new QHBoxLayout;
  hlay2->addWidget(m_ok);
  hlay2->addWidget(m_cancel);

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(10, 10, 10, 10);
  vlay->setSpacing(10);
  vlay->addLayout(hlay1);
  vlay->addLayout(hlay2);

  setWindowTitle(YDBackPointDialog::tr("回原点脚本"));
  m_platLab->setText(YDBackPointDialog::tr("脚本类型"));
  m_ok->setText(YDBackPointDialog::tr("确认"));
  m_cancel->setText(YDBackPointDialog::tr("取消"));

  QStringList list;
  list << "VB.NET"
       << "C#.NET";
  m_platBox->addItems(list);

  resize(200, 70);

  connect(m_ok, &QPushButton::clicked, this, &YDBackPointDialog::slotOkClicked);
  connect(m_cancel, &QPushButton::clicked, this,
          &YDBackPointDialog::slotCancelClicked);
}

void YDBackPointDialog::setType(uint8 type) {
  if (SCRIPT_TYPE_VB_NET == type)
    m_platBox->setCurrentIndex(0);
  else
    m_platBox->setCurrentIndex(1);
}

uint8 YDBackPointDialog::getType() {
  if (0 == m_platBox->currentIndex())
    return SCRIPT_TYPE_VB_NET;
  else
    return SCRIPT_TYPE_CSHARP_NET;
}

void YDBackPointDialog::slotOkClicked() { accept(); }

void YDBackPointDialog::slotCancelClicked() { reject(); }
