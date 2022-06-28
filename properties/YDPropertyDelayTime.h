#ifndef YDPROPERTYDELAYTIME_H
#define YDPROPERTYDELAYTIME_H

#include "YDProperty.h"
class YDIntVarComboBox;
class QLineEdit;
class YDModule;

class YDPropertyDelayTime : public YDProperty {
 public:
  YDPropertyDelayTime(YDModule *m, YDProperty *parent = nullptr);

 public:
  QVariant value(YDModule *m) const override;
  void setValue(YDModule *m, QVariant value) override;

  bool hasEditor() const override;

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 public:
  YDModule *m_module;
  QLineEdit *m_widget1;
  YDIntVarComboBox *m_widget2;
  QStringList m_enum;

 protected:
  virtual QString get(YDModule *m) const = 0;
  virtual void set(YDModule *m, QString value) = 0;
};

#endif  // YDPROPERTYDELAYTIME_H
