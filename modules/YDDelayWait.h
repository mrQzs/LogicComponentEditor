#ifndef YDDELAYWAIT_H
#define YDDELAYWAIT_H

#include "YDModule.h"

class YDDelayWait : public YDModule {
 public:
  YDDelayWait();

 public:
  // virtual
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task,uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDDELAYWAIT_H
