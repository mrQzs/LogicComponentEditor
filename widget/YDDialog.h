#ifndef YDDIALOG_H
#define YDDIALOG_H

#include <QDialog>

class YDDialog : public QDialog {
  Q_OBJECT
 public:
  YDDialog(QWidget *parent = nullptr);

 public:
  // get
  virtual QStringList textList() const = 0;

  // set
  virtual void setTextList(const QStringList &list) = 0;
};

#endif  // YDDIALOG_H
