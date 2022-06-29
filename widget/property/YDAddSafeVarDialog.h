#ifndef YDADDSAFEVARDIALOG_H
#define YDADDSAFEVARDIALOG_H

#include <QModelIndex>

#include "widget/YDDialog.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class YDConditionDialog;
class YDNameLineEdit;

class YDAddSafeVarDialog : public YDDialog {
  Q_OBJECT
 public:
  YDAddSafeVarDialog(QWidget *parent = nullptr);

 public:
  // get
  virtual QStringList textList() const;

  // set
  virtual void setTextList(const QStringList &list);

  void setUpdateParam(const QModelIndex &groupIndex,
                      const QModelIndex &viewIndex, bool flag);

 public slots:
  void slotOkBtnClicked();
  void slotCancelBtnClicked();
  void slotCondBtnClicked();
  void slotCondDlgFinished();

 private:
  QLabel *m_nameLab;
  YDNameLineEdit *m_nameEdit;

  QLabel *m_typeLab;
  QComboBox *m_typeCombo;

  QLabel *m_condLab;
  QPushButton *m_condBtn;

  QPushButton *m_okBtn;
  QPushButton *m_cancelBtn;

  YDConditionDialog *m_condDialog;

  bool m_isUpdate;
  QModelIndex m_groupIndex;
  QModelIndex m_viewIndex;
};

#endif  // YDADDSAFEVARDIALOG_H
