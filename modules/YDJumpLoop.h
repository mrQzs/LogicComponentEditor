#ifndef YDJUMPLOOP_H
#define YDJUMPLOOP_H

#include "YDModule.h"

class YDJumpLoop : public YDModule {
 public:
  YDJumpLoop();

 public:
  // virtual
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task, uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
  virtual bool isValid() const;

 private:
  bool isInLoop(yd::lg::LogicProcess *p) const;
};

#endif  // YDJUMPLOOP_H
