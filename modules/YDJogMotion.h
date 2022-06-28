#ifndef YDJOGMOTION_H
#define YDJOGMOTION_H

#include "YDModule.h"

class YDJogMotion : public YDModule {
 public:
  YDJogMotion();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task,uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDJOGMOTION_H
