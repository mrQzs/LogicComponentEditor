#ifndef YDVARSETDIALOG_H
#define YDVARSETDIALOG_H

#include <QDialog>

#include "YDDebugDialog.h"
#include "platform.h"
#include "yddef.h"

class QLabel;
class QLineEdit;
class QPushButton;
class YDNameLineEdit;

class YDVarSetDialog : public QDialog {
  Q_OBJECT
 public:
  YDVarSetDialog(QWidget* parent = nullptr);

 public:
  void setVar(yd::vr::SystemVariable* var,
              const yd::proto::VariableRTValue& varstate);

 private slots:
  void slotOkClicked(bool);
  void slotCancelClicked(bool);
  void slotValueChanged(const QString& str);

 private:
  QLabel* m_name;
  YDNameLineEdit* m_nameEdit;

  QLabel* m_type;
  QLineEdit* m_typeEdit;

  QLabel* m_min;
  QLineEdit* m_minEdit;

  QLabel* m_max;
  QLineEdit* m_maxEdit;

  QLabel* m_value;
  QLineEdit* m_valueEdit;

  QLabel* m_time;
  QLineEdit* m_timeEdit;

  QPushButton* m_ok;
  QPushButton* m_cancel;

  yd::vr::SystemVariable* m_var;
};

#endif  // YDVARSETDIALOG_H
