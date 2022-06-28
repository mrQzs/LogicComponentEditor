#ifndef YDNAMELINEEDIT_H
#define YDNAMELINEEDIT_H

#include <QLineEdit>

class QValidator;

class YDNameLineEdit : public QLineEdit {
  Q_OBJECT
 public:
  YDNameLineEdit(QWidget* parent = nullptr);

 private:
  QValidator* m_validator;
};

#endif  // YDNAMELINEEDIT_H
