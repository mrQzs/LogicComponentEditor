#ifndef YDADDCONDITIONDIALOG_H
#define YDADDCONDITIONDIALOG_H

#include <QDialog>

class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;

class YDAddConditionDialog : public QDialog {
  Q_OBJECT
 public:
  YDAddConditionDialog(QWidget* parent);

 public:
  // get
  QString text();

  // set
  void setText(const QString& str);

 public slots:
  void slotOkBtnClicked();
  void slotCancelBtnClicked();

 private:
  QLabel* m_varLab;
  QComboBox* m_varBox;
  QLabel* m_cmpLab;
  QComboBox* m_cmpBox;
  QLabel* m_valueLab;
  QLineEdit* m_valueEdit;
  QLabel* m_errRangeLab;
  QLineEdit* m_errRangeEdit;
  QLabel* m_invertLab;
  QCheckBox* m_invertBox;

  QPushButton* m_okBtn;
  QPushButton* m_cancelBtn;
};

#endif  // YDADDCONDITIONDIALOG_H
