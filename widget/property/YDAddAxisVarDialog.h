#ifndef YDADDAXISVARDIALOG_H
#define YDADDAXISVARDIALOG_H

#include "widget/YDDialog.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class YDIntLineEdit;

class YDAddAxisVarDialog : public QDialog {
  Q_OBJECT
 public:
  YDAddAxisVarDialog(QWidget *parent = nullptr);

 public:
  // get
  QString text();

  // set
  void setText(const QString &str);

 public slots:
  void slotOkBtnClicked();
  void slotCancelBtnClicked();

 private slots:
  void slotWayChanged(int index);
  void slotTargetWayChanged(int index);

 private:
  QLabel *m_axisLab;
  QComboBox *m_axisBox;

  QLabel *m_typeLab;
  QComboBox *m_typeCombo;

  QLabel *m_targetWayLab;
  QComboBox *m_targetWayBox;

  QLabel *m_targetLab;
  YDIntLineEdit *m_targetEdit;
  QComboBox *m_targetBox;

  QLabel *m_speedLab;
  QComboBox *m_speedBox;

  QLabel *m_speedLab2;
  QComboBox *m_speedBox2;

  QPushButton *m_okBtn;
  QPushButton *m_cancelBtn;

  QStringList m_enum;
};

#endif  // YDADDAXISVARDIALOG_H
