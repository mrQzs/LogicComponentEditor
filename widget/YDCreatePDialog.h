#ifndef YDCREATEPDIALOG_H
#define YDCREATEPDIALOG_H

#include <QDialog>

class QLabel;
class YDNameLineEdit;
class QPushButton;

class YDCreatePDialog : public QDialog {
  Q_OBJECT
 public:
  explicit YDCreatePDialog(QWidget *parent = nullptr);

 public:
  QString getName() const;

 signals:

 private slots:
  void slotOkClicked();
  void slotCancelClicked();

 private:
  QLabel *m_nameLab;
  YDNameLineEdit *m_nameEdit;
  QPushButton *m_ok;
  QPushButton *m_cancel;
};

#endif  // YDCREATEPDIALOG_H
