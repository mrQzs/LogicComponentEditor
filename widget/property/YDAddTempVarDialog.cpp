#include "YDAddTempVarDialog.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "widget/YDDTComboBox.h"
#include "widget/YDNameLineEdit.h"
#include "widget/YDVariableDialog.h"

YDAddTempVarDialog::YDAddTempVarDialog(QWidget *parent)
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
      m_varDlg{nullptr} {
  setWindowTitle(YDAddTempVarDialog::tr("添加变量"));

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

  m_nameLab->setText(YDAddTempVarDialog::tr("名称"));
  m_typeLab->setText(YDAddTempVarDialog::tr("数值类型"));
  m_boolLab->setText(YDAddTempVarDialog::tr("初始值"));
  m_axisLab->setText(YDAddTempVarDialog::tr("初始值"));
  m_valueLab->setText(YDAddTempVarDialog::tr("初始值"));
  m_minLab->setText(YDAddTempVarDialog::tr("最小值"));
  m_maxLab->setText(YDAddTempVarDialog::tr("最大值"));

  m_okBtn->setText(YDAddTempVarDialog::tr("确认"));
  m_cancelBtn->setText(YDAddTempVarDialog::tr("取消"));

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
          &YDAddTempVarDialog::slotOkBtnClicked);

  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDAddTempVarDialog::slotCancelBtnClicked);

  connect(m_typeCombo, &QComboBox::currentIndexChanged, this,
          &YDAddTempVarDialog::slotTypeChanged);

  connect(m_axisBtn, &QPushButton::clicked, this,
          &YDAddTempVarDialog::slotAxisBtnClicked);
}

QStringList YDAddTempVarDialog::textList() const {
  QStringList list;
  int index = m_typeCombo->currentIndex();
  list << m_nameEdit->text() << QString::number(index);

  switch (index) {
    case 0:
      list << (m_boolBox->currentIndex() == 0 ? "true" : "false");
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

void YDAddTempVarDialog::setTextList(const QStringList &infos) {
  setWindowTitle(YDAddTempVarDialog::tr("修改变量"));
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

void YDAddTempVarDialog::slotOkBtnClicked() {
  if (m_nameEdit->text().isEmpty()) {
    QMessageBox::warning(this, YDAddTempVarDialog::tr("错误"),
                         YDAddTempVarDialog::tr("名字不能为空!"));
    return;
  }

  int index = m_typeCombo->currentIndex();
  if (1 == index || 2 == index) {
    if (m_valueEdit->text().isEmpty() || m_minEdit->text().isEmpty() ||
        m_maxEdit->text().isEmpty()) {
      QMessageBox::warning(this, YDAddTempVarDialog::tr("错误"),
                           YDAddTempVarDialog::tr("值不能为空!"));
      return;
    }
  }

  accept();
}

void YDAddTempVarDialog::slotCancelBtnClicked() { reject(); }

void YDAddTempVarDialog::slotTypeChanged(int index) {
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
    case 1:
    case 2:
      m_valueLab->show();
      m_valueEdit->show();
      m_minLab->show();
      m_minEdit->show();
      m_maxLab->show();
      m_maxEdit->show();
      m_axisBtn->setText("");
      break;
    case 3:
      m_valueLab->show();
      m_valueEdit->show();
      m_minEdit->clear();
      m_maxEdit->clear();
      m_axisBtn->setText("");
      break;
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

void YDAddTempVarDialog::slotAxisBtnClicked(bool) {
  auto str = m_axisBtn->text();
  auto list = str.split(',');
  if (m_varDlg) delete m_varDlg;
  m_varDlg = new YDVariableDialog(this);
  connect(m_varDlg, &QDialog::finished, this,
          &YDAddTempVarDialog::slotVarDialogFinished);

  m_varDlg->resize(680, 400);
  m_varDlg->setTextList(list);
  m_varDlg->open();
}

void YDAddTempVarDialog::slotVarDialogFinished() {
  if (m_varDlg->result() == QDialog::Accepted) {
    auto list = m_varDlg->textList();
    QString tmp;
    for (const auto &s : list) {
      tmp += QString("%1,").arg(s);
    }

    m_axisBtn->setText(tmp);
  }
}
