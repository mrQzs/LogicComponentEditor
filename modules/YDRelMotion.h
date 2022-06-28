#ifndef YDRELMOTION_H
#define YDRELMOTION_H

#include "YDModule.h"

class YDRelMotion : public YDModule {
 public:
  YDRelMotion();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task,uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDRELMOTION_H
