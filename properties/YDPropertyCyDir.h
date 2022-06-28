#ifndef YDPROPERTYCYDIR_H
#define YDPROPERTYCYDIR_H

#include "YDProperty.h"

class YDModule;
class QComboBox;

class YDPropertyCyDir : public YDProperty {
 public:
  YDPropertyCyDir(YDModule *m, YDProperty *parent = nullptr);

  QVariant value(YDModule *m) const override;
  void setValue(YDModule *m, QVariant value) override;

  bool hasEditor() const override;

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 public:
  QComboBox *m_widget;
  QStringList m_enum;
  YDModule *m_module;

 protected:
  virtual QString get(YDModule *m) const = 0;
  virtual void set(YDModule *m, QString value) = 0;
  void updateStrList();
};

#endif  // YDPROPERTYCYDIR_H
