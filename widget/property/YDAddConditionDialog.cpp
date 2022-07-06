#include "YDAddConditionDialog.h"

#include <QCheckBox>
#include <QComboBox>
#include <QCompleter>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QValidator>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDAddConditionDialog::YDAddConditionDialog(QWidget* parent)
    : QDialog{parent},
      m_varLab{new QLabel(this)},
      m_varBox{new QComboBox(this)},
      m_cmpLab{new QLabel(this)},
      m_cmpBox{new QComboBox(this)},
      m_valueLab{new QLabel(this)},
      m_valueEdit{new QLineEdit(this)},
      m_errRangeLab{new QLabel(this)},
      m_errRangeEdit{new QLineEdit(this)},
      m_invertLab{new QLabel(this)},
      m_invertBox{new QCheckBox(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)} {
  setWindowTitle(YDAddConditionDialog::tr("添加变量条件"));
  auto glay = new QGridLayout;
  glay->addWidget(m_varLab, 0, 0, 1, 1);
  glay->addWidget(m_varBox, 0, 1, 1, 1);
  glay->addWidget(m_cmpLab, 1, 0, 1, 1);
  glay->addWidget(m_cmpBox, 1, 1, 1, 1);
  glay->addWidget(m_valueLab, 2, 0, 1, 1);
  glay->addWidget(m_valueEdit, 2, 1, 1, 1);
  glay->addWidget(m_errRangeLab, 3, 0, 1, 1);
  glay->addWidget(m_errRangeEdit, 3, 1, 1, 1);
  glay->addWidget(m_invertLab, 4, 0, 1, 1);
  glay->addWidget(m_invertBox, 4, 1, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_okBtn);
  hlay->addWidget(m_cancelBtn);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(glay);
  vlay->addLayout(hlay);

  m_varLab->setText(YDAddConditionDialog::tr("关联变量"));
  m_cmpLab->setText(YDAddConditionDialog::tr("比较类型"));
  m_valueLab->setText(YDAddConditionDialog::tr("判定数值"));
  m_errRangeLab->setText(YDAddConditionDialog::tr("误差范围"));
  m_invertLab->setText(YDAddConditionDialog::tr("是否取反"));
  m_invertBox->setText(YDAddConditionDialog::tr("是"));
  m_okBtn->setText(YDAddConditionDialog::tr("确定"));
  m_cancelBtn->setText(YDAddConditionDialog::tr("取消"));

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDAddConditionDialog::slotOkBtnClicked);
  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDAddConditionDialog::slotCancelBtnClicked);

  m_varBox->setEditable(true);
  QCompleter* pCompleter = new QCompleter(m_varBox->model(), this);
  pCompleter->setFilterMode(Qt::MatchContains);
  m_varBox->setCompleter(pCompleter);

  QStringList list;
  list << "";
  auto vars = YDProjectManage::getAllVariables();
  for (auto v : vars)
    list << QString("%1").arg(STRTQSTR(v->variable_name.c_str()));
  m_varBox->addItems(list);

  QStringList cmpWay;
  cmpWay << YDAddConditionDialog::tr("小于")
         << YDAddConditionDialog::tr("小于等于")
         << YDAddConditionDialog::tr("等于") << YDAddConditionDialog::tr("大于")
         << YDAddConditionDialog::tr("大于等于")
         << YDAddConditionDialog::tr("不相等");
  m_cmpBox->addItems(cmpWay);

  auto validator = new QDoubleValidator(this);
  m_valueEdit->setValidator(validator);
  m_errRangeEdit->setValidator(validator);

  m_valueEdit->setPlaceholderText("100");
  m_errRangeEdit->setPlaceholderText("0.01");
}

QString YDAddConditionDialog::text() {
  QString str;
  str += m_varBox->currentText() + "@";
  str += m_cmpBox->currentText() + "@";
  str += m_valueEdit->text() + "@";
  str += m_errRangeEdit->text() + "@";
  str += (m_invertBox->checkState() ? YDAddConditionDialog::tr("是")
                                    : YDAddConditionDialog::tr("否")) +
         "@";

  return str;
}

void YDAddConditionDialog::setText(const QString& str) {
  auto list = str.split('@');
  int index = m_varBox->findText(list[0]);
  if (index < 0) index = 0;
  m_varBox->setCurrentIndex(index);

  index = m_cmpBox->findText(list[1]);
  if (index < 0) index = 0;
  m_cmpBox->setCurrentIndex(index);

  m_valueEdit->setText(list[2]);
  m_errRangeEdit->setText(list[3]);
  bool b = list[4] == YDAddConditionDialog::tr("是") ? true : false;
  m_invertBox->setChecked(b);
}

void YDAddConditionDialog::slotOkBtnClicked() {
  if (m_errRangeEdit->text().isEmpty() || m_valueEdit->text().isEmpty())
    QMessageBox::warning(this, YDAddConditionDialog::tr("错误"),
                         YDAddConditionDialog::tr("值不能为空!"));
  else if (0 == m_varBox->currentIndex() ||
           m_varBox->currentIndex() >= m_varBox->count())
    QMessageBox::warning(this, YDAddConditionDialog::tr("错误"),
                         YDAddConditionDialog::tr("请选择变量!"));
  else
    accept();
}

void YDAddConditionDialog::slotCancelBtnClicked() { reject(); }
