#ifndef YDSTOPMOTION_H
#define YDSTOPMOTION_H

#include "YDModule.h"

class YDStopMotion : public YDModule {
 public:
  YDStopMotion();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task,uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDSTOPMOTION_H
