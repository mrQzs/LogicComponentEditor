#ifndef YDSETVARIABLEDIALOG_H
#define YDSETVARIABLEDIALOG_H

#include "YDDialog.h"
#include "yd_project.h"

class QTableWidget;
class QPushButton;
class YDAddAxisVarDialog;
class YDModule;

class YDSetVariableDialog : public YDDialog {
  Q_OBJECT
 public:
  YDSetVariableDialog(QWidget *parent = nullptr);

 public:
  // get
  virtual QStringList textList() const;

  // set
  virtual void setTextList(const QStringList &list);

 public slots:
  void slotOkBtnClicked();
  void slotCancelBtnClicked();

 private:
  QString getContent(int row) const;
  void setContent(const QString &str);

 private:
  QTableWidget *m_tableWidget;
  QPushButton *m_okBtn;
  QPushButton *m_cancelBtn;

  YDAddAxisVarDialog *m_addContionDia;
};

#endif  // YDSETVARIABLEDIALOG_H
