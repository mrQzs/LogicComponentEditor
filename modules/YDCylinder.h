#ifndef YDCYLINDER_H
#define YDCYLINDER_H

#include "YDModule.h"

class YDCylinder : public YDModule {
 public:
  YDCylinder();

 public:
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task, uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
};

#endif  // YDCYLINDER_H
