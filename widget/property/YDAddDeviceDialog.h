#ifndef YDADDDEVICEDIALOG_H
#define YDADDDEVICEDIALOG_H

#include "widget/YDDialog.h"

class QLabel;
class QLineEdit;
class QPushButton;
class YDDeviceTypeComboBox;
class YDNameLineEdit;

class YDAddDeviceDialog : public YDDialog {
  Q_OBJECT
 public:
  YDAddDeviceDialog(const QString &title, QWidget *parent = nullptr);

 public:
  // get
  virtual QStringList textList() const;

  // set
  virtual void setTextList(const QStringList &list);

 public slots:
  void slotOkBtnClicked();
  void slotCancelBtnClicked();

 private:
  QLabel *m_nameLab;
  YDNameLineEdit *m_nameEdit;

  QLabel *m_cardLab;
  QLineEdit *m_cardEdit;

  QLabel *m_typeLab;
  YDDeviceTypeComboBox *m_typeCombo;

  QLabel *m_configLab;
  QLineEdit *m_configEdit;
  QPushButton *m_configBtn;

  QLabel *m_remarkLab;
  QLineEdit *m_remarkEdit;

  QPushButton *m_okBtn;
  QPushButton *m_cancelBtn;
};

#endif  // YDADDDEVICEDIALOG_H
