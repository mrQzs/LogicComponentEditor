#ifndef YDIFELSECONDITION_H
#define YDIFELSECONDITION_H

#include "YDModule.h"

class YDModuleIFElseWidget;

class YDIfElseCondition : public YDModule {
 public:
  YDIfElseCondition();

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
  YDModuleIFElseWidget *m_widget;
};

#endif  // YDIFELSECONDITION_H
