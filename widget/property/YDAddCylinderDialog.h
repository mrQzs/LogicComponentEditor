#ifndef YDADDCYLINDERDIALOG_H
#define YDADDCYLINDERDIALOG_H

#include "widget/YDDialog.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QCheckBox;
class QTabWidget;

class YDAddCylinderDialog : public YDDialog {
  Q_OBJECT
 public:
  YDAddCylinderDialog(QWidget *parent = nullptr);

 public:
  // get
  virtual QStringList textList() const;

  // set
  virtual void setTextList(const QStringList &list);

 public slots:
  void slotOkBtnClicked();
  void slotCancelBtnClicked();
  void slotSingleCheck(bool);
  void slotDoubleCheck(bool);

  void slotWayFSelect(int);
  void slotWayBSelect(int);

  void slotDirName1Changed(const QString &str);
  void slotDirName2Changed(const QString &str);

 private:
  void init();

 private:
  QLabel *m_nameLab;
  QLineEdit *m_nameEdit;

  QLabel *m_dirName1;
  QLineEdit *m_dirEdit1;

  QLabel *m_dirName2;
  QLineEdit *m_dirEdit2;

  QLabel *m_typeLab;
  QComboBox *m_typeCombo;

  QCheckBox *m_single;
  QComboBox *m_elec1Combo;

  QCheckBox *m_double;

  QComboBox *m_elec2Combo;

  QTabWidget *m_tabWidget;

  QLabel *m_wayLabF;
  QComboBox *m_wayComboF;

  QLabel *m_inputLabF;
  QComboBox *m_inputComboF;

  QLabel *m_delayLabF;
  QLineEdit *m_delayEditF;

  QLabel *m_alarmLabF;
  QLineEdit *m_alarmEditF;

  QLabel *m_wayLabB;
  QComboBox *m_wayComboB;

  QLabel *m_inputLabB;
  QComboBox *m_inputComboB;

  QLabel *m_delayLabB;
  QLineEdit *m_delayEditB;

  QLabel *m_alarmLabB;
  QLineEdit *m_alarmEditB;

  QPushButton *m_okBtn;
  QPushButton *m_cancelBtn;
};

#endif  // YDADDCYLINDERDIALOG_H
