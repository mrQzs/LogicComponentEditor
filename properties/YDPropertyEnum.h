#ifndef YDPROPERTYENUM_H
#define YDPROPERTYENUM_H

#include "YDProperty.h"

class QComboBox;

class YDPropertyEnum : public YDProperty {
 public:
  YDPropertyEnum(QStringList enumText, YDProperty *parent = nullptr);

  QVariant value(YDModule *m) const override;
  void setValue(YDModule *m, QVariant value) override;

  bool hasEditor() const override;

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 public:
  QComboBox *m_widget;
  QStringList m_enum;

 protected:
  virtual int get(YDModule *m) const = 0;
  virtual void set(YDModule *m, int value) = 0;
};

#endif  // YDPROPERTYENUM_H
