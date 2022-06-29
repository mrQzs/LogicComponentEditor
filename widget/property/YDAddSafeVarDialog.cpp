#include "YDAddSafeVarDialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/YDHelper.h"
#include "common/YDLogger.h"
#include "core/YDProjectManage.h"
#include "core/YDVariable.h"
#include "widget/YDConditionDialog.h"
#include "widget/YDNameLineEdit.h"

YDAddSafeVarDialog::YDAddSafeVarDialog(QWidget *parent)
    : YDDialog{parent},
      m_nameLab{new QLabel(this)},
      m_nameEdit{new YDNameLineEdit(this)},
      m_typeLab{new QLabel(this)},
      m_typeCombo{new QComboBox(this)},
      m_condLab{new QLabel(this)},
      m_condBtn{new QPushButton(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)},
      m_condDialog{nullptr},
      m_isUpdate{false} {
  setWindowTitle(YDAddSafeVarDialog::tr("逻辑运算符、判定条件"));

  auto glay = new QGridLayout;
  glay->addWidget(m_nameLab, 0, 0, 1, 1);
  glay->addWidget(m_nameEdit, 0, 1, 1, 1);
  glay->addWidget(m_typeLab, 1, 0, 1, 1);
  glay->addWidget(m_typeCombo, 1, 1, 1, 1);
  glay->addWidget(m_condLab, 2, 0, 1, 1);
  glay->addWidget(m_condBtn, 2, 1, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_okBtn);
  hlay->addStretch();
  hlay->addWidget(m_cancelBtn);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(glay);
  vlay->addLayout(hlay);

  m_nameLab->setText(YDAddSafeVarDialog::tr("名称"));
  m_typeLab->setText(YDAddSafeVarDialog::tr("判断条件"));
  m_condLab->setText(YDAddSafeVarDialog::tr("条件"));

  m_okBtn->setText(YDAddSafeVarDialog::tr("确认"));
  m_cancelBtn->setText(YDAddSafeVarDialog::tr("取消"));

  QStringList list;
  list << YDAddSafeVarDialog::tr("与") << YDAddSafeVarDialog::tr("或");
  m_typeCombo->addItems(list);

  connect(m_condBtn, &QPushButton::clicked, this,
          &YDAddSafeVarDialog::slotCondBtnClicked);

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDAddSafeVarDialog::slotOkBtnClicked);

  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDAddSafeVarDialog::slotCancelBtnClicked);

  resize(340, 120);
}

QStringList YDAddSafeVarDialog::textList() const {
  QStringList list;
  list << m_nameEdit->text() << QString::number(m_typeCombo->currentIndex())
       << m_condBtn->text();
  return list;
}

void YDAddSafeVarDialog::setTextList(const QStringList &list) {
  if (list.size() == 3) {
    m_nameEdit->setText(list[0]);
    m_typeCombo->setCurrentIndex(list[1].toUInt());
    m_condBtn->setText(list[2]);
  }
}

void YDAddSafeVarDialog::setUpdateParam(const QModelIndex &groupIndex,
                                        const QModelIndex &viewIndex,
                                        bool flag) {
  m_groupIndex = groupIndex;
  m_viewIndex = viewIndex;
  m_isUpdate = flag;
}

void YDAddSafeVarDialog::slotOkBtnClicked() {
  if (m_nameEdit->text().isEmpty()) {
    QMessageBox::warning(this, YDAddSafeVarDialog::tr("错误"),
                         YDAddSafeVarDialog::tr("名字不能为空!"));
    return;
  }

  if (m_isUpdate) {
    YDVariable *vg =
        reinterpret_cast<YDVariable *>(m_groupIndex.internalPointer());
    int row = m_viewIndex.row();
    auto vars = YDProjectManage::GetGroupedGlobalVars(vg->groupId());

    if (row < vars.size()) {
      auto var = vars[row];
      auto result = YDProjectManage::UpdateVariableName(
          var->variable_id, QSTRTSTR(m_nameEdit->text()));
      switch (result) {
        case -1:
          QMessageBox::warning(nullptr, YDAddSafeVarDialog::tr("提示"),
                               YDAddSafeVarDialog::tr("修改安全变量名称失败!"));
          return;
        case 0:
          break;
        case 1:
          QMessageBox::warning(nullptr, YDAddSafeVarDialog::tr("提示"),
                               YDAddSafeVarDialog::tr("安全变量名称有重复!"));
          return;
        default:
          return;
      }
    }
    m_isUpdate = false;
  }
  accept();
}

void YDAddSafeVarDialog::slotCancelBtnClicked() { reject(); }

void YDAddSafeVarDialog::slotCondBtnClicked() {
  if (m_condDialog) delete m_condDialog;
  m_condDialog = new YDConditionDialog(this);
  if (!m_condBtn->text().isEmpty()) {
    auto strlist = m_condBtn->text().split(";");
    m_condDialog->setTextList(strlist);
  }
  connect(m_condDialog, &YDConditionDialog::finished, this,
          &YDAddSafeVarDialog::slotCondDlgFinished);
  m_condDialog->open();
}

void YDAddSafeVarDialog::slotCondDlgFinished() {
  if (m_condDialog->result() == QDialog::Accepted) {
    auto strlist = m_condDialog->textList();
    QString str;
    for (const auto &s : strlist) str += s + ";";
    m_condBtn->setText(str);
  }
}
