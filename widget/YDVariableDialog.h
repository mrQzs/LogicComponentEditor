#ifndef YDVARIABLEDIALOG_H
#define YDVARIABLEDIALOG_H

#include "YDDialog.h"

class QTableWidget;
class QPushButton;
class QToolButton;
class YDAddAxisVarDialog;
class QTableWidgetItem;

class YDVariableDialog : public YDDialog {
  Q_OBJECT
 public:
  YDVariableDialog(QWidget *parent = nullptr);

 public:
  // get
  virtual QStringList textList() const;

  // set
  virtual void setTextList(const QStringList &list);

 public slots:
  void slotAddBtnClicked();
  void slotDelBtnClicked();

  void slotOkBtnClicked();
  void slotCancelBtnClicked();

  void slotEditItem(QTableWidgetItem *item);
  void slotAddConditionDiaFinished();
  void slotUpdateItem();

 private:
  QString getContent(int row) const;
  void setContent(const QString &str);
  void updateContent(const QString &str);

 private:
  QToolButton *m_addBtn;
  QToolButton *m_delBtn;
  QTableWidget *m_tableWidget;
  QPushButton *m_okBtn;
  QPushButton *m_cancelBtn;

  YDAddAxisVarDialog *m_addContionDia;
  QTableWidgetItem *m_editItem;
};

#endif  // YDVARIABLEDIALOG_H
