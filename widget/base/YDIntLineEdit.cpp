#include "YDIntLineEdit.h"

#include <QIntValidator>

YDIntLineEdit::YDIntLineEdit(QWidget *parent) : QLineEdit(parent) {
  m_validator = new QIntValidator(this);
  this->setValidator(m_validator);

  connect(this, &YDIntLineEdit::editingFinished, this,
          &YDIntLineEdit::SlotEditingFinished);
}

void YDIntLineEdit::setLimit(const int &min, const int &max) {
  m_validator->setRange(min, max);
}

void YDIntLineEdit::SlotEditingFinished() {
  if (this->text().toInt() < m_validator->bottom()) {
    this->setText(QString::number(m_validator->bottom()));
  } else if (this->text().toInt() > m_validator->top()) {
    this->setText(QString::number(m_validator->top()));
  }
}
