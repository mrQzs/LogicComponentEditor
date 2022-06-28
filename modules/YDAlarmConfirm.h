#ifndef YDALARMCONFIRM_H
#define YDALARMCONFIRM_H

#include "YDModule.h"

class YDAlarmConfirm : public YDModule {
 public:
  YDAlarmConfirm();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task, uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();

 private:
  quint32 getAction(const QString &str);
  QString getActionStr(quint32 value) const;
};

#endif  // YDALARMCONFIRM_H
