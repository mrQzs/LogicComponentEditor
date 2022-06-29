#ifndef YDPROPERTYTASK_H
#define YDPROPERTYTASK_H

#include "YDProperty.h"

class QComboBox;
class YDModule;
class YDTask;

class YDPropertyTask : public YDProperty {
 public:
  YDPropertyTask(YDProperty *parent = nullptr);

 public:
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
  QList<quint32> m_idList;

 protected:
  virtual quint32 get(YDModule *m) const = 0;
  virtual void set(YDModule *m, quint32 value) = 0;
  void updateStrList();

 private:
  YDTask *m_task;
};

#endif  // YDPROPERTYTASK_H
