#include "YDNameDialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "YDNameLineEdit.h"
#include "common/YDHelper.h"
#include "core/YDProjectManage.h"

YDNameDialog::YDNameDialog(QWidget *parent)
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

  m_nameLab->setText(YDNameDialog::tr("项目名称:"));
  m_ok->setText(YDNameDialog::tr("更改"));
  m_cancel->setText(YDNameDialog::tr("取消"));

  connect(m_ok, &QPushButton::clicked, this, &YDNameDialog::slotOkClicked);
  connect(m_cancel, &QPushButton::clicked, this,
          &YDNameDialog::slotCancelClicked);
}

void YDNameDialog::setLabText(const QString &text) { m_nameLab->setText(text); }

void YDNameDialog::setBtnName(const QString &name) { m_ok->setText(name); }

QString YDNameDialog::getName() const { return m_nameEdit->text(); }

void YDNameDialog::clear() { m_nameEdit->clear(); }

void YDNameDialog::slotOkClicked() {
  auto name = m_nameEdit->text();
  if (name.isEmpty()) {
    QMessageBox::warning(nullptr, YDNameDialog::tr("错误"),
                         YDNameDialog::tr("名称为空!"));
    return;
  }

  std::vector<std::string> list;
  YDProjectManage::enumuerateProjects(list);
  for (auto v : list) {
    auto str = STRTQSTR(v.c_str());
    if (str == name) {
      QMessageBox::warning(nullptr, YDNameDialog::tr("错误"),
                           YDNameDialog::tr("名称已存在!"));
      return;
    }
  }

  accept();
}

void YDNameDialog::slotCancelClicked() { reject(); }
