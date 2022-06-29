#include "YDIPLineEdit.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QValidator>

YDIPLineEdit::YDIPLineEdit(QWidget *parent) : QLineEdit(parent) {
  QRegularExpression re(
      "^((\\d|[1-9]\\d|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d|[1-9]\\d|1\\d\\d|"
      "2[0-4]\\d|25[0-5])$");
  m_validator = new QRegularExpressionValidator(re, this);

  this->setValidator(m_validator);
}
