#ifndef YDIFCONDITION_H
#define YDIFCONDITION_H

#include "YDModule.h"

class YDIfConditionWidget;

class YDIfCondition : public YDModule {
 public:
  YDIfCondition();

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
  YDIfConditionWidget *m_widget;
};
#endif  // YDIFCONDITION_H
