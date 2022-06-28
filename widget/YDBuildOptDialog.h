#ifndef YDBUILDOPTDIALOG_H
#define YDBUILDOPTDIALOG_H

#include <QDialog>

class QLabel;
class QComboBox;
class QPushButton;

class YDBuildOptDialog : public QDialog {
  Q_OBJECT
 public:
  YDBuildOptDialog(QWidget* parent = nullptr);

 public:
  int getStruct() const;
  int getWay() const;

 private slots:
  void slotOkClicked(bool);
  void slotCancelClicked(bool);
  void slotCpuChanged(int);

 private:
  QLabel* m_struct;
  QComboBox* m_structBox;

  QLabel* m_cpu;
  QComboBox* m_cpuBox;

  QPushButton* m_ok;
  QPushButton* m_cancel;
};

#endif  // YDBUILDOPTDIALOG_H
