#include "YDAddDelayTimeDialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "widget/YDIntVarComboBox.h"
#include "widget/YDNameLineEdit.h"

YDAddDelayTimeDialog::YDAddDelayTimeDialog(QWidget *parent)
    : YDDialog{parent},
      m_wayLab{new QLabel(this)},
      m_wayBox{new QComboBox(this)},
      m_valueLab1{new QLabel(this)},
      m_valueEdit{new QLineEdit(this)},
      m_valueLab2{new QLabel(this)},
      m_valueBox{new YDIntVarComboBox(this)},
      m_ok{new QPushButton(this)},
      m_cancel{new QPushButton(this)} {
  auto grid = new QGridLayout;
  grid->addWidget(m_wayLab, 0, 0, 1, 1);
  grid->addWidget(m_wayBox, 0, 1, 1, 1);
  grid->addWidget(m_valueLab1, 1, 0, 1, 1);
  grid->addWidget(m_valueEdit, 1, 1, 1, 1);
  grid->addWidget(m_valueLab2, 2, 0, 1, 1);
  grid->addWidget(m_valueBox, 2, 1, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_ok);
  hlay->addWidget(m_cancel);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(grid);
  vlay->addLayout(hlay);

  m_wayLab->setText(YDAddDelayTimeDialog::tr("延时方式:"));
  m_valueLab1->setText(YDAddDelayTimeDialog::tr("延时时间:"));
  m_valueLab2->setText(YDAddDelayTimeDialog::tr("延时方式:"));
}

QStringList YDAddDelayTimeDialog::textList() const {
  QStringList list;
  return list;
}

void YDAddDelayTimeDialog::setTextList(const QStringList &) {}
