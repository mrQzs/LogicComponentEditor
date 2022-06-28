#ifndef YDWAITCOMPLETE_H
#define YDWAITCOMPLETE_H

#include "YDModule.h"

class YDWaitComplete : public YDModule {
 public:
  YDWaitComplete();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task, uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDWAITCOMPLETE_H
