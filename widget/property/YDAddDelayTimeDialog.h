#ifndef YDADDDELAYTIMEDIALOG_H
#define YDADDDELAYTIMEDIALOG_H

#include "widget/YDDialog.h"

class QLabel;
class QLineEdit;
class QComboBox;
class YDIntVarComboBox;
class QPushButton;

class YDAddDelayTimeDialog : public YDDialog {
  Q_OBJECT
 public:
  YDAddDelayTimeDialog(QWidget* parent = nullptr);

 public:
  // get
  virtual QStringList textList() const;

  // set
  virtual void setTextList(const QStringList& list);

 private:
  QLabel* m_wayLab;
  QComboBox* m_wayBox;
  QLabel* m_valueLab1;
  QLineEdit* m_valueEdit;
  QLabel* m_valueLab2;
  YDIntVarComboBox* m_valueBox;
  QPushButton* m_ok;
  QPushButton* m_cancel;
};

#endif  // YDADDDELAYTIMEDIALOG_H
