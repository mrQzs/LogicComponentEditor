#ifndef YDCONTROLDO_H
#define YDCONTROLDO_H

#include "YDModule.h"

class YDControlDO : public YDModule {
 public:
  YDControlDO();

 public:
  // virtual
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task,uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDCONTROLDO_H
