#include "YDVarSetDialog.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "YDDgHelper.h"
#include "common/YDHelper.h"
#include "widget/YDNameLineEdit.h"

YDVarSetDialog::YDVarSetDialog(QWidget *parent)
    : QDialog{parent},
      m_name{new QLabel(this)},
      m_nameEdit{new YDNameLineEdit(this)},
      m_type{new QLabel(this)},
      m_typeEdit{new QLineEdit(this)},
      m_min{new QLabel(this)},
      m_minEdit{new QLineEdit(this)},
      m_max{new QLabel(this)},
      m_maxEdit{new QLineEdit(this)},
      m_value{new QLabel(this)},
      m_valueEdit{new QLineEdit(this)},
      m_time{new QLabel(this)},
      m_timeEdit{new QLineEdit(this)},
      m_ok{new QPushButton(this)},
      m_cancel{new QPushButton(this)} {
  setWindowTitle(YDVarSetDialog::tr("修改变量"));
  auto grid = new QGridLayout;
  grid->addWidget(m_name, 0, 0, 1, 1);
  grid->addWidget(m_nameEdit, 0, 1, 1, 1);
  grid->addWidget(m_type, 1, 0, 1, 1);
  grid->addWidget(m_typeEdit, 1, 1, 1, 1);
  grid->addWidget(m_min, 2, 0, 1, 1);
  grid->addWidget(m_minEdit, 2, 1, 1, 1);
  grid->addWidget(m_max, 3, 0, 1, 1);
  grid->addWidget(m_maxEdit, 3, 1, 1, 1);
  grid->addWidget(m_value, 4, 0, 1, 1);
  grid->addWidget(m_valueEdit, 4, 1, 1, 1);
  grid->addWidget(m_time, 5, 0, 1, 1);
  grid->addWidget(m_timeEdit, 5, 1, 1, 1);

  auto hbox = new QHBoxLayout;
  hbox->addStretch();
  hbox->addWidget(m_ok);
  hbox->addWidget(m_cancel);
  hbox->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(10, 10, 10, 10);
  vlay->setSpacing(6);
  vlay->addLayout(grid);
  vlay->addLayout(hbox);

  m_name->setText(YDVarSetDialog::tr("名称:"));
  m_type->setText(YDVarSetDialog::tr("数据类型:"));
  m_min->setText(YDVarSetDialog::tr("最小值:"));
  m_max->setText(YDVarSetDialog::tr("最大值:"));
  m_value->setText(YDVarSetDialog::tr("当前值:"));
  m_time->setText(YDVarSetDialog::tr("更新时间:"));

  m_name->setAlignment(Qt::AlignRight);
  m_type->setAlignment(Qt::AlignRight);
  m_min->setAlignment(Qt::AlignRight);
  m_max->setAlignment(Qt::AlignRight);
  m_value->setAlignment(Qt::AlignRight);
  m_time->setAlignment(Qt::AlignRight);

  m_ok->setText(YDVarSetDialog::tr("确认"));
  m_cancel->setText(YDVarSetDialog::tr("取消"));

  m_nameEdit->setDisabled(true);
  m_typeEdit->setDisabled(true);
  m_minEdit->setDisabled(true);
  m_maxEdit->setDisabled(true);
  m_timeEdit->setDisabled(true);

  connect(m_ok, &QPushButton::clicked, this, &YDVarSetDialog::slotOkClicked);
  connect(m_cancel, &QPushButton::clicked, this,
          &YDVarSetDialog::slotCancelClicked);
  connect(m_valueEdit, &QLineEdit::textChanged, this,
          &YDVarSetDialog::slotValueChanged);
}

void YDVarSetDialog::setVar(yd::vr::SystemVariable *var,
                            const yd::proto::VariableRTValue &varstate) {
  m_var = var;
  QString time;
  if (varstate.ullTimestamp > 0)
    time = STRTQSTR(
        yd::CTimestamp::FormatTimeFromMicroseconds(varstate.ullTimestamp)
            .c_str());

  m_nameEdit->setText(STRTQSTR(var->variable_name.c_str()));
  m_typeEdit->setText(YDHelper::getDataType(var->value_type));
  m_minEdit->setText(STRTQSTR(var->min_value.c_str()));
  m_maxEdit->setText(STRTQSTR(var->max_value.c_str()));
  m_valueEdit->setText(STRTQSTR(varstate.strRealtimeValue.c_str()));

  m_timeEdit->setText(time);
}

void YDVarSetDialog::slotOkClicked(bool) {
  YDDgHelper::setSingleVariableValue(m_var->variable_id, m_var->init_value);
  accept();
}

void YDVarSetDialog::slotCancelClicked(bool) { reject(); }

void YDVarSetDialog::slotValueChanged(const QString &str) {
  if (!str.isEmpty()) {
    std::string val = QSTRTSTR(str);  // str.toUtf8().constData();
    m_var->init_value = val;
  }
}
