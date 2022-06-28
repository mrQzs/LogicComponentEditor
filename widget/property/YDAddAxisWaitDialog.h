#ifndef YDADDAXISWAITDIALOG_H
#define YDADDAXISWAITDIALOG_H

#include <QDialog>

class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;

class YDAddAxisWaitDialog : public QDialog {
  Q_OBJECT
 public:
  YDAddAxisWaitDialog(QWidget* parent);

 public:
  // get
  QString text();

  // set
  void setText(const QString& str);

 public slots:
  void slotOkBtnClicked();
  void slotCancelBtnClicked();

 private slots:
  void slotWayChanged(int);

 private:
  QLabel* m_axisLab;
  QComboBox* m_axisBox;
  QLabel* m_wayLab;
  QComboBox* m_wayBox;
  QLabel* m_valueLab;
  QLineEdit* m_valueEdit;
  QPushButton* m_okBtn;
  QPushButton* m_cancelBtn;
};

#endif  // YDADDAXISWAITDIALOG_H
