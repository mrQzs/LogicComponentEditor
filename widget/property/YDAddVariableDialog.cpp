#include "YDAddVariableDialog.h"

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
#include "widget/YDDTComboBox.h"
#include "widget/YDNameLineEdit.h"
#include "widget/YDVariableDialog.h"

YDAddVariableDialog::YDAddVariableDialog(QWidget *parent)
    : YDDialog{parent},
      m_nameLab{new QLabel(this)},
      m_nameEdit{new YDNameLineEdit(this)},
      m_typeLab{new QLabel(this)},
      m_typeCombo{new YDDTComboBox(this)},
      m_boolLab{new QLabel(this)},
      m_boolBox{new QComboBox(this)},
      m_axisLab{new QLabel(this)},
      m_axisBtn{new QPushButton(this)},
      m_valueLab{new QLabel(this)},
      m_valueEdit{new QLineEdit(this)},
      m_minLab{new QLabel(this)},
      m_minEdit{new QLineEdit(this)},
      m_maxLab{new QLabel(this)},
      m_maxEdit{new QLineEdit(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)},
      m_varDlg{nullptr},
      m_isUpdate{false} {
  setWindowTitle(YDAddVariableDialog::tr("添加全局变量"));

  auto glay = new QGridLayout;
  glay->addWidget(m_nameLab, 0, 0, 1, 1);
  glay->addWidget(m_nameEdit, 0, 1, 1, 1);
  glay->addWidget(m_typeLab, 1, 0, 1, 1);
  glay->addWidget(m_typeCombo, 1, 1, 1, 1);
  glay->addWidget(m_boolLab, 2, 0, 1, 1);
  glay->addWidget(m_boolBox, 2, 1, 1, 1);
  glay->addWidget(m_axisLab, 3, 0, 1, 1);
  glay->addWidget(m_axisBtn, 3, 1, 1, 1);
  glay->addWidget(m_valueLab, 4, 0, 1, 1);
  glay->addWidget(m_valueEdit, 4, 1, 1, 1);
  glay->addWidget(m_minLab, 5, 0, 1, 1);
  glay->addWidget(m_minEdit, 5, 1, 1, 1);
  glay->addWidget(m_maxLab, 6, 0, 1, 1);
  glay->addWidget(m_maxEdit, 6, 1, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_okBtn);
  hlay->addStretch();
  hlay->addWidget(m_cancelBtn);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(glay);
  vlay->addLayout(hlay);

  m_nameLab->setText(YDAddVariableDialog::tr("名称"));
  m_typeLab->setText(YDAddVariableDialog::tr("数值类型"));
  m_boolLab->setText(YDAddVariableDialog::tr("初始值"));
  m_axisLab->setText(YDAddVariableDialog::tr("初始值"));
  m_valueLab->setText(YDAddVariableDialog::tr("初始值"));
  m_minLab->setText(YDAddVariableDialog::tr("最小值"));
  m_maxLab->setText(YDAddVariableDialog::tr("最大值"));

  m_okBtn->setText(YDAddVariableDialog::tr("确认"));
  m_cancelBtn->setText(YDAddVariableDialog::tr("取消"));

  m_valueLab->hide();
  m_valueEdit->hide();
  m_axisLab->hide();
  m_axisBtn->hide();
  m_minLab->hide();
  m_minEdit->hide();
  m_maxLab->hide();
  m_maxEdit->hide();

  QStringList list;
  list << "True"
       << "False";
  m_boolBox->addItems(list);

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDAddVariableDialog::slotOkBtnClicked);

  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDAddVariableDialog::slotCancelBtnClicked);

  connect(m_typeCombo, &QComboBox::currentIndexChanged, this,
          &YDAddVariableDialog::slotTypeChanged);

  connect(m_axisBtn, &QPushButton::clicked, this,
          &YDAddVariableDialog::slotAxisBtnClicked);

  m_typeCombo->setCurrentIndex(2);
  slotTypeChanged(2);
  m_minEdit->setText("-1000");
  m_valueEdit->setText("0");
  m_maxEdit->setText("1000");

  resize(600, 140);
}

QStringList YDAddVariableDialog::textList() const {
  QStringList list;
  int index = m_typeCombo->currentIndex();
  list << m_nameEdit->text() << QString::number(index);

  switch (index) {
    case 0:
      list << (m_boolBox->currentIndex() == 0 ? "True" : "False");
      break;
    case 1:
    case 2:
      list << m_valueEdit->text() << m_minEdit->text() << m_maxEdit->text();
      break;
    case 3:
      list << m_valueEdit->text();
      break;
    case 4:
      list << m_axisBtn->text();
      break;
    default:
      break;
  }
  return list;
}

void YDAddVariableDialog::setTextList(const QStringList &infos) {
  setWindowTitle(YDAddVariableDialog::tr("修改全局变量"));
  m_nameEdit->setText(infos[0]);
  int index = infos[1].toUInt();
  slotTypeChanged(index);
  m_typeCombo->setCurrentIndex(index);
  switch (index) {
    case 0:
      m_boolBox->setCurrentText(infos[2]);
      break;
    case 1:
    case 2:
      m_valueEdit->setText(infos[2]);
      m_minEdit->setText(infos[3]);
      m_maxEdit->setText(infos[4]);
      break;
    case 3:
      m_valueEdit->setText(infos[2]);
      break;
    case 4:
      m_axisBtn->setText(infos[2]);
      break;
    default:
      break;
  }
}

void YDAddVariableDialog::setUpdateParam(const QModelIndex &groupIndex,
                                         const QModelIndex &viewIndex,
                                         bool flag) {
  m_groupIndex = groupIndex;
  m_viewIndex = viewIndex;
  m_isUpdate = flag;
}

void YDAddVariableDialog::slotOkBtnClicked() {
  if (m_nameEdit->text().isEmpty()) {
    QMessageBox::warning(this, YDAddVariableDialog::tr("错误"),
                         YDAddVariableDialog::tr("名字不能为空!"));
    return;
  }

  int index = m_typeCombo->currentIndex();
  if (1 == index || 2 == index) {
    if (m_valueEdit->text().isEmpty() || m_minEdit->text().isEmpty() ||
        m_maxEdit->text().isEmpty()) {
      QMessageBox::warning(this, YDAddVariableDialog::tr("错误"),
                           YDAddVariableDialog::tr("值不能为空!"));
      return;
    }

    if (m_minEdit->text().toDouble() > m_maxEdit->text().toDouble()) {
      QMessageBox::warning(this, YDAddVariableDialog::tr("错误"),
                           YDAddVariableDialog::tr("最小值不能大于最大值!"));
      return;
    }

    if (m_valueEdit->text().toDouble() < m_minEdit->text().toDouble()) {
      QMessageBox::warning(this, YDAddVariableDialog::tr("错误"),
                           YDAddVariableDialog::tr("初始值不能小于最小值!"));
      return;
    }

    if (m_valueEdit->text().toDouble() > m_maxEdit->text().toDouble()) {
      QMessageBox::warning(this, YDAddVariableDialog::tr("错误"),
                           YDAddVariableDialog::tr("初始值不能大于最大值!"));
      return;
    }
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
          QMessageBox::warning(
              nullptr, YDAddVariableDialog::tr("提示"),
              YDAddVariableDialog::tr("修改全局变量名称失败!"));
          return;
        case 0:
          break;
        case 1:
          QMessageBox::warning(nullptr, YDAddVariableDialog::tr("提示"),
                               YDAddVariableDialog::tr("全局变量名称有重复!"));
          return;
        default:
          return;
      }
    }
    m_isUpdate = false;
  }
  accept();
}

void YDAddVariableDialog::slotCancelBtnClicked() { reject(); }

void YDAddVariableDialog::slotTypeChanged(int index) {
  m_boolLab->hide();
  m_boolBox->hide();
  m_axisLab->hide();
  m_axisBtn->hide();
  m_valueLab->hide();
  m_valueEdit->hide();
  m_minLab->hide();
  m_minEdit->hide();
  m_maxLab->hide();
  m_maxEdit->hide();

  switch (index) {
    case 0:
      m_boolLab->show();
      m_boolBox->show();
      m_minEdit->clear();
      m_maxEdit->clear();
      m_valueEdit->clear();
      m_axisBtn->setText("");
      break;
    case 1: {
      m_valueLab->show();
      m_valueEdit->show();
      m_valueEdit->setValidator(new QIntValidator());
      m_minLab->show();
      m_minEdit->show();
      m_minEdit->setValidator(new QIntValidator());
      m_maxLab->show();
      m_maxEdit->show();
      m_maxEdit->setValidator(new QIntValidator());
      m_axisBtn->setText("");
      break;
    }
    case 2:
      m_valueLab->show();
      m_valueEdit->show();
      m_valueEdit->setValidator(new QDoubleValidator());
      m_minLab->show();
      m_minEdit->show();
      m_minEdit->setValidator(new QDoubleValidator());
      m_maxLab->show();
      m_maxEdit->show();
      m_maxEdit->setValidator(new QDoubleValidator());
      m_axisBtn->setText("");
      break;
    case 3: {
      m_valueLab->show();
      m_valueEdit->show();
      m_valueEdit->clear();
      m_valueEdit->setValidator(nullptr);
      m_minEdit->clear();
      m_maxEdit->clear();
      m_axisBtn->setText("");
      break;
    }
    case 4:
      m_axisLab->show();
      m_axisBtn->show();
      m_minEdit->clear();
      m_maxEdit->clear();
      m_valueEdit->clear();
      break;
    default:
      break;
  }
}

void YDAddVariableDialog::slotAxisBtnClicked(bool) {
  auto str = m_axisBtn->text();
  auto list = str.split(',');
  if (m_varDlg) delete m_varDlg;
  m_varDlg = new YDVariableDialog(this);
  connect(m_varDlg, &QDialog::finished, this,
          &YDAddVariableDialog::slotVarDialogFinished);

  m_varDlg->resize(680, 400);
  m_varDlg->setTextList(list);
  m_varDlg->open();
}

void YDAddVariableDialog::slotVarDialogFinished() {
  if (m_varDlg->result() == QDialog::Accepted) {
    auto list = m_varDlg->textList();
    QString tmp;
    for (const auto &s : list) {
      tmp += QString("%1,").arg(s);
    }

    m_axisBtn->setText(tmp);
  }
}
