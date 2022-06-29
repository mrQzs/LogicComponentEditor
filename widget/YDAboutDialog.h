#ifndef YDABOUTDIALOG_H
#define YDABOUTDIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;
class YDAboutDialog : public QDialog {
  Q_OBJECT
 public:
  YDAboutDialog(QWidget *parent = nullptr);

 private slots:
  void SlotConfirmClicked();

 private:
  QLabel *m_versionLabel;
  QPushButton *m_confirmBtn;
};

#endif  // YDABOUTDIALOG_H
