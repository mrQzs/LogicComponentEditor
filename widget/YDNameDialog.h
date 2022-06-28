#ifndef YDNAMEDIALOG_H
#define YDNAMEDIALOG_H

#include <QDialog>

class QLabel;
class YDNameLineEdit;
class QPushButton;

class YDNameDialog : public QDialog {
  Q_OBJECT
 public:
  explicit YDNameDialog(QWidget *parent = nullptr);

 public:
  void setLabText(const QString &text);
  void setBtnName(const QString &name);
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

#endif  // YDNAMEDIALOG_H
