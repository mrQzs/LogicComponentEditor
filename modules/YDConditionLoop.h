#ifndef YDCONDITIONLOOP_H
#define YDCONDITIONLOOP_H

#include "YDModule.h"

class YDModuleLoopWidget;

class YDConditionLoop : public YDModule {
 public:
  YDConditionLoop();

 public:
  // virtual
  virtual Module::Type type() const;
  virtual void initModule(YDTask *task, uint64 parentId = 0);
  virtual void initModule(yd::lg::LogicProcess *lp);
  virtual void getData();
  virtual void setData();
  virtual int high() const;
  virtual void setStateMap(const QMap<uint32, yd::proto::ProcState> &map);
  virtual void resize();

 private:
  YDModuleLoopWidget *m_widget;
};

#endif  // YDCONDITIONLOOP_H
