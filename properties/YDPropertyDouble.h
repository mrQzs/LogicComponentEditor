#ifndef YDPROPERTYDOUBLE_H
#define YDPROPERTYDOUBLE_H

#include "YDProperty.h"

class QDoubleSpinBox;

class YDPropertyDouble : public YDPropertyType<double> {
 public:
  YDPropertyDouble(double min, double max, YDProperty *parent = nullptr);
  YDPropertyDouble(double min, double max, QString surfix,
                   YDProperty *parent = nullptr);

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 protected:
  virtual double get(YDModule *m) const = 0;
  virtual void set(YDModule *m, double value) = 0;

 protected:
  QDoubleSpinBox *m_widget;
  double m_min;
  double m_max;
  QString m_surfix;
};

#endif  // YDPROPERTYDOUBLE_H
