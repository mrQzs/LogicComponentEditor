#ifndef YDADDRECIVARDIALOG_H
#define YDADDRECIVARDIALOG_H

#include <QModelIndex>

#include "widget/YDDialog.h"

class QLabel;
class QLineEdit;
class QPushButton;
class YDDTComboBox;
class QComboBox;
class YDVariableDialog;
class YDNameLineEdit;

class YDAddReciVarDialog : public YDDialog {
  Q_OBJECT
 public:
  YDAddReciVarDialog(QWidget *parent = nullptr);

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
  void slotTypeChanged(int);
  void slotAxisBtnClicked(bool);
  void slotVarDialogFinished();

 private:
  QLabel *m_nameLab;
  YDNameLineEdit *m_nameEdit;

  QLabel *m_typeLab;
  YDDTComboBox *m_typeCombo;

  QLabel *m_boolLab;
  QComboBox *m_boolBox;

  QLabel *m_axisLab;
  QPushButton *m_axisBtn;

  QLabel *m_valueLab;
  QLineEdit *m_valueEdit;

  QLabel *m_minLab;
  QLineEdit *m_minEdit;

  QLabel *m_maxLab;
  QLineEdit *m_maxEdit;

  QPushButton *m_okBtn;
  QPushButton *m_cancelBtn;

  YDVariableDialog *m_varDlg;

  bool m_isUpdate;
  QModelIndex m_groupIndex;
  QModelIndex m_viewIndex;
};

#endif  // YDADDRECIVARDIALOG_H
