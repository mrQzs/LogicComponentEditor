#ifndef YDIPLINEEDIT_H
#define YDIPLINEEDIT_H

#include <QLineEdit>

class QValidator;

class YDIPLineEdit : public QLineEdit {
  Q_OBJECT
 public:
  YDIPLineEdit(QWidget* parent = nullptr);

 private:
  QValidator* m_validator;
};

#endif  // YDIPLINEEDIT_H
