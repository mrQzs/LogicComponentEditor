#ifndef YDPROPERTYBOOL_H
#define YDPROPERTYBOOL_H

#include "YDProperty.h"

class QCheckBox;

class YDPropertyBool : public YDPropertyType<bool> {
 public:
  YDPropertyBool(YDProperty *parent = nullptr);

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 protected:
  virtual bool get(YDModule *m) const = 0;
  virtual void set(YDModule *m, bool value) = 0;

 protected:
  QCheckBox *m_widget;
};

#endif  // YDPROPERTYBOOL_H
