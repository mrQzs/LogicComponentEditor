#ifndef YDPROPERTYNAME_H
#define YDPROPERTYNAME_H

#include "YDProperty.h"

class YDNameLineEdit;

class YDPropertyName : public YDPropertyType<QString> {
 public:
  YDPropertyName(YDProperty *parent = nullptr);

  QWidget *editor(QWidget *parent) override;
  void updateEditor(YDModule *m) override;
  void updateWidget(YDModule *m) override;

 protected:
  virtual QString get(YDModule *m) const = 0;
  virtual void set(YDModule *m, QString value) = 0;

 signals:
  void sigSetString(const QString &str);

 protected:
  YDNameLineEdit *m_widget;
};

#endif  // YDPROPERTYNAME_H
