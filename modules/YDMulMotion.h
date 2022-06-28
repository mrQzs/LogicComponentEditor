#ifndef YDMULMOTION_H
#define YDMULMOTION_H

#include "YDModule.h"

class YDMulMotion : public YDModule {
 public:
  YDMulMotion();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task,uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDMULMOTION_H
