#include "YDConditionDialog.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>
#include <QToolButton>
#include <QVBoxLayout>

#include "property/YDAddConditionDialog.h"

YDConditionDialog::YDConditionDialog(QWidget *parent)
    : YDDialog{parent},
      m_addBtn{new QToolButton(this)},
      m_delBtn{new QToolButton(this)},
      m_tableWidget{new QTableWidget(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)},
      m_addContionDia{nullptr},
      m_editItem{nullptr} {
  setWindowTitle(YDConditionDialog::tr("条件列表"));

  m_tableWidget->setColumnCount(5);

  QStringList list;
  list << YDConditionDialog::tr("关联变量") << YDConditionDialog::tr("比较类型")
       << YDConditionDialog::tr("判定数值") << YDConditionDialog::tr("误差范围")
       << YDConditionDialog::tr("是否取反");

  m_tableWidget->setHorizontalHeaderLabels(list);
  m_tableWidget->verticalHeader()->setVisible(false);
  m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
  m_tableWidget->horizontalHeader()->setStretchLastSection(true);
  m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  auto hlay1 = new QHBoxLayout;
  hlay1->addStretch();
  hlay1->addWidget(m_addBtn);
  hlay1->addWidget(m_delBtn);

  auto hlay2 = new QHBoxLayout;
  hlay2->addStretch();
  hlay2->addWidget(m_okBtn);
  hlay2->addWidget(m_cancelBtn);
  hlay2->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(hlay1);
  vlay->addWidget(m_tableWidget);
  vlay->addLayout(hlay2);

  m_addBtn->setIcon(QIcon(":/Icon/add.png"));
  m_delBtn->setIcon(QIcon(":/Icon/delete.png"));
  m_okBtn->setText(YDConditionDialog::tr("确定"));
  m_cancelBtn->setText(YDConditionDialog::tr("取消"));

  resize(800, 600);

  connect(m_addBtn, &QToolButton::clicked, this,
          &YDConditionDialog::slotAddBtnClicked);
  connect(m_delBtn, &QToolButton::clicked, this,
          &YDConditionDialog::slotDelBtnClicked);

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDConditionDialog::slotOkBtnClicked);
  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDConditionDialog::slotCancelBtnClicked);

  connect(m_tableWidget, &QTableWidget::itemDoubleClicked, this,
          &YDConditionDialog::slotEditItem);
}

QStringList YDConditionDialog::textList() const {
  QStringList list;
  for (int i = 0; i < m_tableWidget->rowCount(); ++i) list << getContent(i);

  return list;
}

void YDConditionDialog::setTextList(const QStringList &list) {
  for (const auto &s : list)
    if (!s.isEmpty()) setContent(s);
}

void YDConditionDialog::focusOutEvent(QFocusEvent *) { show(); }

void YDConditionDialog::slotAddBtnClicked() {
  if (m_addContionDia) {
    delete m_addContionDia;
    m_addContionDia = nullptr;
  }
  m_addContionDia = new YDAddConditionDialog(this);
  connect(m_addContionDia, &QDialog::finished, this,
          &YDConditionDialog::slotAddConditionDiaFinished);
  m_addContionDia->open();
}

void YDConditionDialog::slotDelBtnClicked() {
  QList<QTableWidgetItem *> list = m_tableWidget->selectedItems();
  if (list.size() != 0) {
    QTableWidgetItem *sel = list[0];
    if (sel) {
      int r = m_tableWidget->row(sel);
      m_tableWidget->removeRow(r);
    }
  }
}

void YDConditionDialog::slotOkBtnClicked() { accept(); }

void YDConditionDialog::slotCancelBtnClicked() { reject(); }

void YDConditionDialog::slotEditItem(QTableWidgetItem *item) {
  m_editItem = item;
  QString str = getContent(item->row());
  m_addContionDia = new YDAddConditionDialog(this);
  connect(m_addContionDia, &QDialog::finished, this,
          &YDConditionDialog::slotUpdateItem);
  m_addContionDia->setText(str);
  m_addContionDia->open();
}

void YDConditionDialog::slotAddConditionDiaFinished() {
  if (m_addContionDia->result() == QDialog::Accepted) {
    setContent(m_addContionDia->text());
  }
}

void YDConditionDialog::slotUpdateItem() {
  if (m_addContionDia->result() == QDialog::Accepted) {
    updateContent(m_addContionDia->text());
  }
}

QString YDConditionDialog::getContent(int row) const {
  QString str;
  str += QString("%1@").arg(
      m_tableWidget->item(row, 0)->data(Qt::DisplayRole).toString());
  str += QString("%1@").arg(
      m_tableWidget->item(row, 1)->data(Qt::DisplayRole).toString());
  str += QString("%1@").arg(
      m_tableWidget->item(row, 2)->data(Qt::DisplayRole).toString());
  str += QString("%1@").arg(
      m_tableWidget->item(row, 3)->data(Qt::DisplayRole).toString());
  str += QString("%1").arg(
      m_tableWidget->item(row, 4)->data(Qt::DisplayRole).toString());
  return str;
}

void YDConditionDialog::setContent(const QString &str) {
  auto list = str.split("@");
  m_tableWidget->insertRow(m_tableWidget->rowCount());
  int row = m_tableWidget->rowCount() - 1;
  auto it1 = new QTableWidgetItem(list[0]);
  auto it2 = new QTableWidgetItem(list[1]);
  auto it3 = new QTableWidgetItem(list[2]);
  auto it4 = new QTableWidgetItem(list[3]);
  auto it5 = new QTableWidgetItem(list[4]);
  m_tableWidget->setItem(row, 0, it1);
  m_tableWidget->setItem(row, 1, it2);
  m_tableWidget->setItem(row, 2, it3);
  m_tableWidget->setItem(row, 3, it4);
  m_tableWidget->setItem(row, 4, it5);
}

void YDConditionDialog::updateContent(const QString &str) {
  auto list = str.split("@");
  int row = m_editItem->row();
  m_tableWidget->item(row, 0)->setData(Qt::DisplayRole, list[0]);
  m_tableWidget->item(row, 1)->setData(Qt::DisplayRole, list[1]);
  m_tableWidget->item(row, 2)->setData(Qt::DisplayRole, list[2]);
  m_tableWidget->item(row, 3)->setData(Qt::DisplayRole, list[3]);
  m_tableWidget->item(row, 4)->setData(Qt::DisplayRole, list[4]);
}
