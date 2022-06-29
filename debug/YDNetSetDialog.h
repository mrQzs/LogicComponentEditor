#ifndef YDNETSETDIALOG_H
#define YDNETSETDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class YDIntLineEdit;
class YDIPLineEdit;

class YDNetSetDialog : public QDialog {
 public:
  YDNetSetDialog(QWidget* parent = nullptr);

 public:
  QString getIP() const;
  QString getPort() const;
  QString getTime() const;

 private slots:
  void slotOkBtnClicked(bool);
  void slotCancelBtnclicked(bool);

 private:
  QLabel* m_ipLab;
  YDIPLineEdit* m_ipEdit;

  QLabel* m_portLab;
  YDIntLineEdit* m_portEdit;

  QLabel* m_timeLab;
  YDIntLineEdit* m_timeEdit;

  QPushButton* m_okBtn;
  QPushButton* m_cancelBtn;
};

#endif  // YDNETSETDIALOG_H
