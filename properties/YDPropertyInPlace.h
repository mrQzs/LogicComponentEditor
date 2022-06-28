#ifndef YDPROPERTYINPLACE_H
#define YDPROPERTYINPLACE_H

#include "YDProperty.h"

class QDoubleSpinBox;
class YDModule;

class YDPropertyInPlace : public YDPropertyType<double> {
 public:
  YDPropertyInPlace(YDModule *m, double min, double max,
                             YDProperty *parent = nullptr);
  YDPropertyInPlace(YDModule *m, double min, double max,
                             QString surfix, YDProperty *parent = nullptr);

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 protected:
  virtual double get(YDModule *m) const = 0;
  virtual void set(YDModule *m, double value) = 0;

 protected:
  YDModule *m_module;
  QDoubleSpinBox *m_widget;
  double m_min;
  double m_max;
  QString m_surfix;
};

#endif  // YDPROPERTYINPLACE_H
