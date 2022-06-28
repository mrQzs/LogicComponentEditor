#ifndef YDMODULE_H
#define YDMODULE_H

#include <QCoreApplication>
#include <QPixmap>

#include "common/YDGlobal.h"
#include "debug/YDDgHelper.h"
#include "platform.h"
#include "yddef.h"

class QWidget;
class YDProperty;
class YDTask;

extern const QColor MotionColor;
extern const QColor IoColor;
extern const QColor ControlColor;
extern const QColor OtherColor;

extern const QColor MotionFColor;
extern const QColor IoFColor;
extern const QColor ControlFColor;
extern const QColor OtherFColor;

class YDModule {
  Q_DECLARE_TR_FUNCTIONS(YDModule)
 public:
  YDModule();
  virtual ~YDModule();

 public:
  // virtual
  virtual Module::Type type() const = 0;
  virtual void initModule(YDTask *task, uint64 parentId = 0) = 0;
  virtual void initModule(yd::lg::LogicProcess *lp) = 0;
  virtual void getData() = 0;
  virtual void setData() = 0;
  virtual void setStateMap(const QMap<uint32, yd::proto::ProcState> &map);
  virtual void resize();

 public:
  // get
  QPixmap preview(int type = 0) const;
  QString name() const;
  QWidget *widget() const;
  QList<YDProperty *> properties() const;
  YDProperty *property(const QString &name) const;
  virtual int high() const;
  uint32 getLogicProcessId();
  virtual bool isValid() const;
  yd::proto::ProcState getDebugState() const;
  uint32 getParentId() const;
  QString icon() const;

  // set
  void setPreview(const QPixmap &p);
  void setName(const QString &name);
  void setWidget(QWidget *w);
  void setParentId(uint32 id);
  void setDebugState(yd::proto::ProcState &state);

  // other
  void init(YDTask *task);
  void setTask(YDTask *task);
  void updateItemName(const QString &name);
  void updateIfName(const QString &name);
  void updateIfElseName(const QString &name);
  void updateLoopName(const QString &name);

  void setPreviousId(uint64 id);
  void setNextId(uint64 id);

 public:
  void release();

 public:
  void copy(YDModule *module);
  YDTask *getYDTask() const;
  QList<yd::lg::MessageAction *> getActions() const;
  yd::lg::AxisInplaceWait *getAXisWait(const QString &str);
  QString getAxisWaitStr(yd::lg::AxisInplaceWait *axis) const;

 public:
  //#####get#####
  // base
  bool getsyncMode() const;

  // motion
  QString getAxisName() const;
  QString getPosVarName() const;
  int getSpeedWay() const;
  QString getSpeedStr() const;
  QString getSpeedPosStr() const;
  int getStopWay() const;
  QString getSafeVarName() const;
  double getInplaceWaitValue() const;
  int getWaitConditionWay() const;
  QStringList getAxisWaitList() const;
  QStringList getAxisList() const;
  std::vector<uint64> getAxisIdList() const;
  void setAxisIdList(const QList<uint64> &list);

  // io
  QString getDOName() const;
  QString getAOName() const;
  int getDOState() const;
  QString getIOName() const;
  QString getCylinder() const;
  QString getCylinderDir() const;

  // condition
  int getConditionWay() const;
  int getIfConditionWay() const;
  int getLoopConditionWay() const;
  QStringList getConditionList() const;
  QStringList getIfConditionList() const;
  QStringList getLoopConditionList() const;
  uint32 getDelayTime() const;
  uint32 getLoopTimes() const;
  int getInplaceWait() const;

  // other
  QString getCallTask() const;
  int getAlarmLevel() const;
  QString getAlarmContent() const;
  QStringList getAlarmActions() const;
  int getDelayType() const;
  QString getDelayValue() const;
  int getWaitTime() const;
  int getCodeType() const;
  QStringList getCodeList() const;
  int getDataCashSize() const;
  QString getSelectModule() const;

  //#####set#####
  // base
  void setSyncMode(bool b);

  // motion
  void setAxisName(const QString &str);
  void setPosVarName(const QString &str);
  void setSpeedWay(int index);
  void setSpeedStr(const QString &str);
  void setSpeedPosStr(const QString &str);
  void setStopWay(int index);
  void setInplaceWait(int index);
  void setSafeVarName(const QString &str);
  void setInplaceWaitValue(double value);
  void setWaitConditionWay(int index);
  void setAxisWaitList(const QStringList &list);
  void setAxisList(const QStringList &list);

  // io
  void setDOName(const QString &name);
  void setAOName(const QString &name);
  void setDOState(int index);
  void setIOName(const QString &name);
  void setCylinder(const QString &name);
  void setCylinderDir(const QString &str);

  // condition
  void setConditionWay(int index);
  void setIfConditionWay(int index);
  void setLoopConditionWay(int index);
  void setConditionList(const QStringList &list);
  void setIfConditionList(const QStringList &list);
  void setLoopConditionList(const QStringList &list);
  void setDelayTime(uint32 time);
  void setLoopTimes(uint32 times);

  // other
  void setTaskCall(const QString &str);
  void setAlarmLevel(int index);
  void setAlarmContent(const QString &str);
  void setAlarmActions(const QStringList &);
  void setDelayType(int type);
  void setDelayValue(const QString &value);
  void setWaitTime(int time);
  void setCodeType(int type);
  void setCodeList(const QStringList &code);
  void setDataCashSize(int size);
  void setSelectModule(const QString &name);

 public:
  yd::lg::AbsoluteMoveModule *m_absMotionModule;
  yd::lg::RelativeMoveModule *m_relMotionModule;
  yd::lg::JogMoveModule *m_jogMotionModule;
  yd::lg::MultAxisesMoveModule *m_mulMotionModule;
  yd::lg::HomeMoveModule *m_backZMotionModule;
  yd::lg::StopMoveModule *m_stopMotionModule;
  yd::lg::InplaceWaitModule *m_inplaceWaitModule;
  yd::lg::DOControlModule *m_doControlModule;
  yd::lg::AOControlModule *m_aoControlModule;
  yd::lg::CylinderModule *m_cylinderModule;
  yd::lg::IfElseProcess *m_ifElseProcess;
  yd::lg::IfProcess *m_ifProcess;
  yd::lg::CounterLoopModule *m_timesLoopModule;
  yd::lg::ConditionLoopProcess *m_conditionProcess;
  yd::lg::BreakModule *m_jumpModule;
  yd::lg::DelayModule *m_delayModule;
  yd::lg::TaskCallerModule *m_subTaskModule;
  yd::lg::MessageModule *m_messageModule;
  yd::lg::TaskStateWaitModule *m_taskWaitModule;
  yd::lg::ProgramModule *m_programModule;
  yd::lg::JumpToModule *m_jumpToModule;

 protected:
  YDTask *m_task;
  yd::lg::LogicProcess *m_logicProcess;
  QString m_axisName;
  QString m_posVarName;
  int m_speedWay;
  QString m_speedStr;
  QString m_speedPosStr;
  int m_stopWay;
  QString m_doName;
  QString m_aoName;
  int m_doState;
  QString m_ioName;
  uint32 m_loopTimes;
  QString m_callTask;
  int m_inplaceWait;
  QString m_safeVarName;
  double m_inplaceWaitValue;
  int m_alarmLevel;
  QStringList m_alarmActions;
  QString m_cylinderName;
  QString m_cylinderDir;
  int m_delayType;
  QString m_delayValue;
  QStringList m_axisList;
  int m_waitTime;
  int m_codeType;
  QStringList m_codeList;
  int m_dataCashSize;
  QString m_moduleName;

 protected:
  QPixmap m_preview;
  QWidget *m_widget;
  QList<YDProperty *> m_properties;
  yd::proto::ProcState m_debugState;

 private:
  bool m_enable;
};

extern YDModule *selectModule;

Q_DECLARE_METATYPE(YDModule *)
Q_DECLARE_METATYPE(const YDModule *)

#endif  // YDMODULE_H
