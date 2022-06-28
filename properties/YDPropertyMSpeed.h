#ifndef YDPROPERTYMSPEED_H
#define YDPROPERTYMSPEED_H

#include "YDProperty.h"

class QComboBox;
class YDModule;

class YDPropertyMSpeed : public YDProperty {
 public:
  YDPropertyMSpeed(YDModule *m, YDProperty *parent = nullptr);

 public:
  QVariant value(YDModule *m) const override;
  void setValue(YDModule *m, QVariant value) override;

  bool hasEditor() const override;

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 public:
  YDModule *m_module;
  QComboBox *m_widget;
  QStringList m_enum;

 protected:
  virtual QString get(YDModule *m) const = 0;
  virtual void set(YDModule *m, QString value) = 0;
  void updateStrList();
};

#endif  // YDPROPERTYMSPEED_H
