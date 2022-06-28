#include "YDNameLineEdit.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QValidator>

YDNameLineEdit::YDNameLineEdit(QWidget *parent) : QLineEdit(parent) {
  QRegularExpression re(
      "(^[a-zA-Z_]|^[^\\x00-\\xff])((\\w|_|[^\\x00-\\xff]){0,63})");
  m_validator = new QRegularExpressionValidator(re, this);

  this->setValidator(m_validator);
}
