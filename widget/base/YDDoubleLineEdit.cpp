#include "YDDoubleLineEdit.h"

#include <QDoubleValidator>

YDDoubleLineEdit::YDDoubleLineEdit(QWidget *parent) : QLineEdit{parent} {
  m_validator = new QDoubleValidator(this);
  this->setValidator(m_validator);
}
