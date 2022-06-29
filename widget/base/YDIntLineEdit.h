#ifndef YDINTLINEEDIT_H
#define YDINTLINEEDIT_H

#include <QLineEdit>

class QIntValidator;

class YDIntLineEdit : public QLineEdit {
  Q_OBJECT
 public:
  YDIntLineEdit(QWidget* parent = nullptr);

  void setLimit(const int& min, const int& max);

 private slots:
  void SlotEditingFinished();

 private:
  QIntValidator* m_validator;
};

#endif  // YDINTLINEEDIT_H
