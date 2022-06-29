#include "YDSetVariableDialog.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>
#include <QToolButton>
#include <QVBoxLayout>

#include "RapidJsonHelper.h"
#include "common/YDHelper.h"
#include "modules/YDModule.h"
#include "property/YDAddAxisVarDialog.h"

YDSetVariableDialog::YDSetVariableDialog(QWidget *parent)
    : YDDialog{parent},
      m_tableWidget{new QTableWidget(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)},
      m_addContionDia{nullptr} {
  setWindowTitle(YDSetVariableDialog::tr("轴坐标列表"));

  m_tableWidget->setColumnCount(6);

  QStringList list;
  list << YDSetVariableDialog::tr("是否使能")
       << YDSetVariableDialog::tr("运动轴号")
       << YDSetVariableDialog::tr("运动类型")
       << YDSetVariableDialog::tr("目标位置")
       << YDSetVariableDialog::tr("运动速度方式")
       << YDSetVariableDialog::tr("运动速度");

  m_tableWidget->horizontalHeader()->setStretchLastSection(true);
  m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_tableWidget->setHorizontalHeaderLabels(list);
  m_tableWidget->verticalHeader()->setVisible(false);
  m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);

  auto hlay2 = new QHBoxLayout;
  hlay2->addStretch();
  hlay2->addWidget(m_okBtn);
  hlay2->addWidget(m_cancelBtn);
  hlay2->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addWidget(m_tableWidget);
  vlay->addLayout(hlay2);

  m_okBtn->setText(YDSetVariableDialog::tr("确认"));
  m_cancelBtn->setText(YDSetVariableDialog::tr("取消"));

  resize(800, 600);

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDSetVariableDialog::slotOkBtnClicked);
  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDSetVariableDialog::slotCancelBtnClicked);
}

QStringList YDSetVariableDialog::textList() const {
  QStringList list;
  for (int i = 0; i < m_tableWidget->rowCount(); ++i) list << getContent(i);
  return list;
}

void YDSetVariableDialog::setTextList(const QStringList &list) {
  for (const auto &s : list)
    if (!s.isEmpty()) setContent(s);
}

void YDSetVariableDialog::slotOkBtnClicked() { accept(); }

void YDSetVariableDialog::slotCancelBtnClicked() { reject(); }

QString YDSetVariableDialog::getContent(int row) const {
  QString str;
  if (m_tableWidget->item(row, 0)->checkState() == Qt::Unchecked)
    str += QString("%1@").arg(YDSetVariableDialog::tr("否"));
  else
    str += QString("%1@").arg(YDSetVariableDialog::tr("是"));

  str += QString("%1@").arg(
      m_tableWidget->item(row, 1)->data(Qt::DisplayRole).toString());
  str += QString("%1@").arg(
      m_tableWidget->item(row, 2)->data(Qt::DisplayRole).toString());
  str += QString("%1@").arg(
      m_tableWidget->item(row, 3)->data(Qt::DisplayRole).toString());
  str += QString("%1@").arg(
      m_tableWidget->item(row, 4)->data(Qt::DisplayRole).toString());
  str += QString("%1").arg(
      m_tableWidget->item(row, 5)->data(Qt::DisplayRole).toString());

  return str;
}

void YDSetVariableDialog::setContent(const QString &str) {
  auto list = str.split("@");
  m_tableWidget->insertRow(m_tableWidget->rowCount());
  int row = m_tableWidget->rowCount() - 1;

  auto it0 = new QTableWidgetItem();
  auto it1 = new QTableWidgetItem(list[1]);
  auto it2 = new QTableWidgetItem(list[2]);
  auto it3 = new QTableWidgetItem(list[3]);
  auto it4 = new QTableWidgetItem(list[4]);
  auto it5 = new QTableWidgetItem(list[5]);
  it1->setFlags(Qt::NoItemFlags);
  it2->setFlags(Qt::NoItemFlags);
  it3->setFlags(Qt::NoItemFlags);
  it4->setFlags(Qt::NoItemFlags);
  it5->setFlags(Qt::NoItemFlags);

  if (list[0] == YDSetVariableDialog::tr("是"))
    it0->setCheckState(Qt::Checked);
  else
    it0->setCheckState(Qt::Unchecked);

  m_tableWidget->setItem(row, 0, it0);
  m_tableWidget->setItem(row, 1, it1);
  m_tableWidget->setItem(row, 2, it2);
  m_tableWidget->setItem(row, 3, it3);
  m_tableWidget->setItem(row, 4, it4);
  m_tableWidget->setItem(row, 5, it5);
}
