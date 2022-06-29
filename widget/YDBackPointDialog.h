#ifndef YDBACKPOINTDIALOG_H
#define YDBACKPOINTDIALOG_H

#include <QDialog>

class QLabel;
class QComboBox;
class QPushButton;

#include "platform.h"

class YDBackPointDialog : public QDialog {
  Q_OBJECT
 public:
  YDBackPointDialog(QWidget* parent = nullptr);

 public:
  void setType(uint8 type);
  uint8 getType();

 private slots:
  void slotOkClicked();
  void slotCancelClicked();

 private:
  QLabel* m_platLab;
  QComboBox* m_platBox;

  QPushButton* m_ok;
  QPushButton* m_cancel;
};

#endif  // YDBACKPOINTDIALOG_H
