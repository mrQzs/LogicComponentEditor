#ifndef YDSUBTASKCALL_H
#define YDSUBTASKCALL_H

#include "YDModule.h"

class YDSubTaskCall : public YDModule {
 public:
  YDSubTaskCall();

 public:
  // virtual
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task,uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDSUBTASKCALL_H
