#ifndef YDDOUBLELINEEDIT_H
#define YDDOUBLELINEEDIT_H

#include <QLineEdit>

class QDoubleValidator;

class YDDoubleLineEdit : public QLineEdit {
  Q_OBJECT
 public:
  YDDoubleLineEdit(QWidget* parent = nullptr);

 private:
  QDoubleValidator* m_validator;
};

#endif  // YDDOUBLELINEEDIT_H
