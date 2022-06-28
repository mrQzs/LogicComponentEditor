#ifndef YDPROPERTYDELAYVALUE_H
#define YDPROPERTYDELAYVALUE_H

#include "YDProperty.h"

class QLineEdit;
class YDIntVarComboBox;

class YDPropertyDelayValue : public YDProperty {
 public:
  YDPropertyDelayValue(int type = 0, YDProperty *parent = nullptr);

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 protected:
  virtual QString get(YDModule *m) const = 0;
  virtual void set(YDModule *m, QString value) = 0;

 signals:
  void sigSetString(const QString &str);

 protected:
  QLineEdit *m_widget;
  YDIntVarComboBox *m_widget2;
  int m_type;
};

#endif  // YDPROPERTYDELAYVALUE_H
