#ifndef YDABSMOTION_H
#define YDABSMOTION_H

#include "YDModule.h"

class YDAbsMotion : public YDModule {
 public:
  YDAbsMotion();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task, uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDABSMOTION_H
