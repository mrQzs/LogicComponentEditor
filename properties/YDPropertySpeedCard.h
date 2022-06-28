#ifndef YDPROPERTYSPEEDCARD_H
#define YDPROPERTYSPEEDCARD_H

#include "YDProperty.h"

class QComboBox;
class YDModule;

class YDPropertySpeedCard : public YDProperty {
 public:
  YDPropertySpeedCard(YDProperty *parent = nullptr);

 public:
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
  virtual QString get(YDModule *m) const = 0;
  virtual void set(YDModule *m, QString value) = 0;
  void updateStrList();
};

#endif  // YDPROPERTYSPEEDCARD_H
