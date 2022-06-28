#ifndef YDCUSTOMWPROP_H
#define YDCUSTOMWPROP_H

#include "YDProperty.h"

class YDDialog;

enum WidgetType {
  e_CONDITION = 0,
  e_ALARMACTION,
  e_INPLACEWAIT,
  e_SETVARIABLE,
  e_PROGRAM
};

class YDCustomWProp : public YDProperty {
 public:
  explicit YDCustomWProp(WidgetType type, YDProperty *parent = nullptr);
  explicit YDCustomWProp(YDModule *m, WidgetType type,
                         YDProperty *parent = nullptr);

 public:
  virtual QString name() const { return QString(); }
  virtual QString codeName() const { return QString(); }

 public:
  bool hasEditor() const override;
  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

  QVariant value(YDModule *m) const override;
  void setValue(YDModule *m, QVariant value) override;

 protected:
  YDDialog *m_widget;

  virtual QStringList get(YDModule *m) const = 0;
  virtual void set(YDModule *m, QStringList list) = 0;

 private:
  YDModule *m_module;
  WidgetType m_type;
};

#endif  // YDCUSTOMWPROP_H
