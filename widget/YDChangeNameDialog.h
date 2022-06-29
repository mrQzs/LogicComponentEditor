#ifndef YDCHANGENAMEDIALOG_H
#define YDCHANGENAMEDIALOG_H

#include <QDialog>

class QLabel;
class YDNameLineEdit;
class QPushButton;

class YDChangeNameDialog : public QDialog {
  Q_OBJECT
 public:
  explicit YDChangeNameDialog(QWidget *parent = nullptr);

 public:
  QString getName() const;
  void clear();

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

#endif  // YDCHANGENAMEDIALOG_H
