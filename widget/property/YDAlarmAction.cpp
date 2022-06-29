#include "YDAlarmAction.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/YDHelper.h"
#include "modules/YDModule.h"
#include "widget/YDDTComboBox.h"
#include "widget/YDNameLineEdit.h"

YDAlarmAction::YDAlarmAction(YDModule *m, QWidget *parent)
    : YDDialog{parent},
      m_module{m},
      m_confirm{new QCheckBox(this)},
      m_cfEdit{new QLineEdit(this)},
      m_ignore{new QCheckBox(this)},
      m_igEdit{new QLineEdit(this)},
      m_retry{new QCheckBox(this)},
      m_rtEdit{new QLineEdit(this)},
      m_stop{new QCheckBox(this)},
      m_spEdit{new QLineEdit(this)},
      m_okBtn{new QPushButton(this)},
      m_cancelBtn{new QPushButton(this)} {
  setWindowTitle(YDAlarmAction::tr("选择动作类型"));

  auto glay = new QGridLayout;
  glay->addWidget(m_confirm, 0, 0, 1, 1);
  glay->addWidget(m_cfEdit, 0, 1, 1, 1);
  glay->addWidget(m_ignore, 0, 2, 1, 1);
  glay->addWidget(m_igEdit, 0, 3, 1, 1);
  glay->addWidget(m_retry, 1, 0, 1, 1);
  glay->addWidget(m_rtEdit, 1, 1, 1, 1);
  glay->addWidget(m_stop, 1, 2, 1, 1);
  glay->addWidget(m_spEdit, 1, 3, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_okBtn);
  hlay->addStretch();
  hlay->addWidget(m_cancelBtn);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->addLayout(glay);
  vlay->addLayout(hlay);

  m_actions = m->getActions();

  m_cfEdit->setText(STRTQSTR(m_actions[0]->action_name.c_str()));
  m_igEdit->setText(STRTQSTR(m_actions[1]->action_name.c_str()));
  m_rtEdit->setText(STRTQSTR(m_actions[2]->action_name.c_str()));
  m_spEdit->setText(STRTQSTR(m_actions[3]->action_name.c_str()));

  m_confirm->setChecked(m_actions[0]->selected);
  m_ignore->setChecked(m_actions[1]->selected);
  m_retry->setChecked(m_actions[2]->selected);
  m_stop->setChecked(m_actions[3]->selected);

  m_okBtn->setText(YDAlarmAction::tr("确认"));
  m_cancelBtn->setText(YDAlarmAction::tr("取消"));

  connect(m_okBtn, &QPushButton::clicked, this,
          &YDAlarmAction::slotOkBtnClicked);

  connect(m_cancelBtn, &QPushButton::clicked, this,
          &YDAlarmAction::slotCancelBtnClicked);

  connect(m_cfEdit, &QLineEdit::textChanged, this,
          &YDAlarmAction::slotcfChange);
  connect(m_igEdit, &QLineEdit::textChanged, this,
          &YDAlarmAction::slotigChange);
  connect(m_rtEdit, &QLineEdit::textChanged, this,
          &YDAlarmAction::slotrtChange);
  connect(m_spEdit, &QLineEdit::textChanged, this,
          &YDAlarmAction::slotspChange);

  connect(m_confirm, &QCheckBox::clicked, this, &YDAlarmAction::slotcfChecked);
  connect(m_ignore, &QCheckBox::clicked, this, &YDAlarmAction::slotigChecked);
  connect(m_retry, &QCheckBox::clicked, this, &YDAlarmAction::slotrtChecked);
  connect(m_stop, &QCheckBox::clicked, this, &YDAlarmAction::slotspChecked);
}

QStringList YDAlarmAction::textList() const {
  QStringList list;
  if (m_confirm->isChecked()) list << m_cfEdit->text();
  if (m_ignore->isChecked()) list << m_igEdit->text();
  if (m_retry->isChecked()) list << m_rtEdit->text();
  if (m_stop->isChecked()) list << m_spEdit->text();

  return list;
}

void YDAlarmAction::setTextList(const QStringList &infos) {
  for (const auto &s : infos)
    if (!s.isEmpty()) setChecked(s);
}

void YDAlarmAction::focusOutEvent(QFocusEvent *e) { show(); }

void YDAlarmAction::slotOkBtnClicked() {
  if (m_confirm->isChecked() || m_ignore->isChecked() || m_retry->isChecked() ||
      m_stop->isChecked())
    accept();
  else {
    QMessageBox::warning(this, YDAlarmAction::tr("错误"),
                         YDAlarmAction::tr("请至少勾选一个!"));
  }
}

void YDAlarmAction::slotCancelBtnClicked() { reject(); }

void YDAlarmAction::slotcfChange(const QString &t) {
  if (!t.isEmpty()) {
    m_actions[0]->action_name = QSTRTSTR(t);
  } else {
    m_cfEdit->setText(
        STRTQSTR(m_actions[0]->action_name.c_str()));
  }
}

void YDAlarmAction::slotigChange(const QString &t) {
  if (!t.isEmpty()) {
    m_actions[1]->action_name = QSTRTSTR(t);
  } else {
    m_igEdit->setText(
        STRTQSTR(m_actions[1]->action_name.c_str()));
  }
}

void YDAlarmAction::slotrtChange(const QString &t) {
  if (!t.isEmpty()) {
    m_actions[2]->action_name = QSTRTSTR(t);
  } else {
    m_rtEdit->setText(
        STRTQSTR(m_actions[2]->action_name.c_str()));
  }
}

void YDAlarmAction::slotspChange(const QString &t) {
  if (!t.isEmpty()) {
    m_actions[3]->action_name = QSTRTSTR(t);
  } else {
    m_spEdit->setText(
        STRTQSTR(m_actions[3]->action_name.c_str()));
  }
}

void YDAlarmAction::slotcfChecked(bool b) { m_actions[0]->selected = b; }

void YDAlarmAction::slotigChecked(bool b) { m_actions[1]->selected = b; }

void YDAlarmAction::slotrtChecked(bool b) { m_actions[2]->selected = b; }

void YDAlarmAction::slotspChecked(bool b) { m_actions[3]->selected = b; }

void YDAlarmAction::setChecked(const QString &str) {
  auto an1 = STRTQSTR(m_actions[0]->action_name.c_str());
  auto an2 = STRTQSTR(m_actions[1]->action_name.c_str());
  auto an3 = STRTQSTR(m_actions[2]->action_name.c_str());
  auto an4 = STRTQSTR(m_actions[3]->action_name.c_str());

  if (str == an1) m_confirm->setChecked(true);
  if (str == an2) m_ignore->setChecked(true);
  if (str == an3) m_retry->setChecked(true);
  if (str == an4) m_stop->setChecked(true);
}
