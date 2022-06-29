#include "YDChangeNameDialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "YDNameLineEdit.h"
#include "core/YDProjectManage.h"

YDChangeNameDialog::YDChangeNameDialog(QWidget *parent)
    : QDialog{parent},
      m_nameLab{new QLabel(this)},
      m_nameEdit{new YDNameLineEdit(this)},
      m_ok{new QPushButton(this)},
      m_cancel{new QPushButton(this)} {
  auto hlay = new QHBoxLayout;
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_nameLab);
  hlay->addStretch();

  auto hlay2 = new QHBoxLayout;
  hlay2->addStretch();
  hlay2->addWidget(m_ok);
  hlay2->addWidget(m_cancel);
  hlay2->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(10, 10, 10, 10);
  vlay->setSpacing(10);

  vlay->addLayout(hlay);
  vlay->addWidget(m_nameEdit);
  vlay->addLayout(hlay2);

  m_nameLab->setText(YDChangeNameDialog::tr("项目名称:"));
  m_ok->setText(YDChangeNameDialog::tr("更改"));
  m_cancel->setText(YDChangeNameDialog::tr("取消"));

  connect(m_ok, &QPushButton::clicked, this,
          &YDChangeNameDialog::slotOkClicked);
  connect(m_cancel, &QPushButton::clicked, this,
          &YDChangeNameDialog::slotCancelClicked);
}

QString YDChangeNameDialog::getName() const { return m_nameEdit->text(); }

void YDChangeNameDialog::clear() { m_nameEdit->clear(); }

void YDChangeNameDialog::slotOkClicked() {
  auto name = m_nameEdit->text();
  if (name.isEmpty()) {
    QMessageBox::warning(nullptr, YDChangeNameDialog::tr("错误"),
                         YDChangeNameDialog::tr("工程名为空!"));
    return;
  }

  std::vector<std::string> list;
  YDProjectManage::enumuerateProjects(list);
  for (auto v : list) {
    auto str = QString::fromLocal8Bit(v.c_str());
    if (str == name) {
      QMessageBox::warning(nullptr, YDChangeNameDialog::tr("错误"),
                           YDChangeNameDialog::tr("工程名已存在!"));
      return;
    }
  }

  accept();
}

void YDChangeNameDialog::slotCancelClicked() { reject(); }
