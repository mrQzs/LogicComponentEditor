#ifndef YDPROPERTYAXIS_H
#define YDPROPERTYAXIS_H

#include "YDProperty.h"

class QComboBox;

class YDPropertyAxis : public YDProperty {
 public:
  YDPropertyAxis(YDProperty *parent = nullptr);

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

#endif  // YDPROPERTYAXIS_H