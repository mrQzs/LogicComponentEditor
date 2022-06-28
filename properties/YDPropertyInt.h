#ifndef YDPROPERTYINT_H
#define YDPROPERTYINT_H

#include "YDProperty.h"

class QSpinBox;

class YDPropertyInt : public YDPropertyType<int> {
 public:
  YDPropertyInt(int min, int max, YDProperty *parent = nullptr);
  YDPropertyInt(int min, int max, QString surfix, YDProperty *parent = nullptr);

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 protected:
  QSpinBox *m_widget;
  int m_min;
  int m_max;
  QString m_surfix;

  virtual int get(YDModule *m) const = 0;
  virtual void set(YDModule *m, int value) = 0;
};

#endif  // YDPROPERTYINT_H
