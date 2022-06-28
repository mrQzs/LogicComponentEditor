#ifndef YDJUMPTOTASK_H
#define YDJUMPTOTASK_H

#include "YDModule.h"

class YDJumpToTask : public YDModule {
 public:
  YDJumpToTask();

 public:
  // virtual
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task, uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDJUMPTOTASK_H
