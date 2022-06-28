#ifndef YDSCRIPTPROPDIALOG_H
#define YDSCRIPTPROPDIALOG_H

#include <QDialog>

#include "yd_project.h"

class QLabel;
class QLineEdit;
class QComboBox;
class YDNameLineEdit;

class YDScriptPropDialog : public QDialog {
  Q_OBJECT
 public:
  YDScriptPropDialog(QWidget* parent = nullptr);

 public:
  void setScritp(yd::adv::ExtendScript* script);
  int getType();

 private slots:
  void slotOkClicked();
  void slotCancelClicked();

 private:
  QLabel* m_name;
  YDNameLineEdit* m_nameEdit;

  QLabel* m_type;
  QComboBox* m_typeBox;

  QLabel* m_way;
  QComboBox* m_wayBox;

  QLabel* m_time;
  QLineEdit* m_timeEdit;

  QLabel* m_data;
  QLineEdit* m_dataEdit;

  QPushButton* m_ok;
  QPushButton* m_cancel;

  yd::adv::ExtendScript* m_script;
};

#endif  // YDSCRIPTPROPDIALOG_H
