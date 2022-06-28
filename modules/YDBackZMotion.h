#ifndef YDBACKZMOTION_H
#define YDBACKZMOTION_H

#include "YDModule.h"

class YDBackZMotion : public YDModule {
 public:
  YDBackZMotion();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task,uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDBACKZMOTION_H
