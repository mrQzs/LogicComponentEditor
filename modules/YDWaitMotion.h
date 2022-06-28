#ifndef YDWAITMOTION_H
#define YDWAITMOTION_H

#include "YDModule.h"

class YDWaitMotion : public YDModule {
 public:
  YDWaitMotion();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task, uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDWAITMOTION_H
