#include "YDStopMotion.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDStopMotionName : public YDPropertyName {
 public:
  QString name() const { return YDStopMotionName::tr("名称"); }
  QString codeName() const { return "Name"; }

 protected:
  virtual QString get(YDModule *m) const { return m->name(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) {
      auto name = QSTRTSTR(str);
      int ret = YDProjectManage::updateLogicProcessName(
          m->getYDTask()->id(), m->getLogicProcessId(), name);
      switch (ret) {
        case -1:
          QMessageBox::warning(nullptr, YDStopMotionName::tr("错误"),
                               YDStopMotionName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDStopMotionName::tr("错误"),
                               YDStopMotionName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDStopMotionAxie : public YDPropertyAxis {
 public:
  QString name() const { return YDStopMotionAxie::tr("运动轴号"); }
  QString codeName() const { return "Axie"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getAxisName(); }
  virtual void set(YDModule *m, QString str) { m->setAxisName(str); }
};

class YDStopMotionStopWay : public YDPropertyEnum {
 public:
  YDStopMotionStopWay(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDStopMotionStopWay::tr("停止方式"); }
  QString codeName() const { return "StopWay"; }

 protected:
  virtual int get(YDModule *m) const { return m->getStopWay(); }
  virtual void set(YDModule *m, int index) { m->setStopWay(index); }
};

class YDStopMotionSafe : public YDPropertySafeVar {
 public:
  QString name() const { return YDStopMotionSafe::tr("安全保护"); }
  QString codeName() const { return "Safe"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSafeVarName(); }
  virtual void set(YDModule *m, QString str) { m->setSafeVarName(str); }
};

class YDStopMotionWait : public YDPropertyEnum {
 public:
  YDStopMotionWait(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDStopMotionWait::tr("到位等待"); }
  QString codeName() const { return "Wait"; }

 protected:
  virtual int get(YDModule *m) const { return m->getInplaceWait(); }
  virtual void set(YDModule *m, int index) { m->setInplaceWait(index); }
};

class YDStopMotionCustomErr : public YDPropertyInPlace {
 public:
  YDStopMotionCustomErr(YDModule *m)
      : YDPropertyInPlace{m, -999999, 999999}, m_module{m} {}
  QString name() const { return YDStopMotionCustomErr::tr("自定义误差带"); }
  QString codeName() const { return "CustomErr"; }
  virtual bool isShow() const {
    if (m_module->getInplaceWait() != 3) return false;
    return true;
  }

 protected:
  virtual double get(YDModule *m) const { return m->getInplaceWaitValue(); }
  virtual void set(YDModule *m, double value) { m->setInplaceWaitValue(value); }

 private:
  YDModule *m_module;
};

YDStopMotion::YDStopMotion() {
  setPreview(QPixmap(":/Module/Stop_Move.png"));
  auto w = new YDModuleWidget(this, MotionColor, MotionFColor);

  setWidget(w);

  QStringList StopWay;
  StopWay << YDStopMotion::tr("紧急停止") << YDStopMotion::tr("平滑停止");

  m_properties << new YDStopMotionName;
  m_properties << new YDStopMotionAxie;
  m_properties << new YDStopMotionStopWay(StopWay);

  m_properties << new YDStopMotionSafe;

  QStringList waittype;
  waittype << YDStopMotion::tr("规划运动停止") << YDStopMotion::tr("默认误差带")
           << YDStopMotion::tr("自定义误差带");
  m_properties << new YDStopMotionWait(waittype);

  m_properties << new YDStopMotionCustomErr(this);
}

Module::Type YDStopMotion::type() const { return Module::Stop_Motion; }

void YDStopMotion::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachStopMoveModule(logicProcessId, m_stopMotionModule);
  Q_ASSERT(m_stopMotionModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDStopMotion::tr("停止运动%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDStopMotion::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachStopMoveModule(lp->id, m_stopMotionModule);
  Q_ASSERT(m_stopMotionModule);
  setData();
}

void YDStopMotion::getData() {
  m_logicProcess->type = LOGIC_PROCESS_STOP_MOVE;
  auto axisList = YDProjectManage::getAxisList();

  auto axis_name = getAxisName();
  for (auto a : axisList) {
    if (STRTQSTR(a->axis_name) == axis_name) {
      m_stopMotionModule->device_id = a->device_id;
      m_stopMotionModule->axis_index = a->axis_index;
      break;
    }
  }

  m_stopMotionModule->method_referid = getStopWay();

  uint64 safeVarId = YDProjectManage::getSafeVirtualVarId(getSafeVarName());
  if (0 != safeVarId) m_stopMotionModule->safeguard_referid = safeVarId;

  m_stopMotionModule->inplace_wait_type = getInplaceWait();

  m_stopMotionModule->inplace_wait_value = getInplaceWaitValue();
}

void YDStopMotion::setData() {
  auto axisList = YDProjectManage::getAxisList();
  auto device_id = m_stopMotionModule->device_id;
  auto axis_index = m_stopMotionModule->axis_index;

  QString name;

  for (auto a : axisList)
    if (device_id == a->device_id)
      if (axis_index == a->axis_index)
        name = STRTQSTR(a->axis_name.c_str());

  setAxisName(name);
  int index = m_stopMotionModule->method_referid == 0 ? 0 : 1;
  setStopWay(index);

  auto safeVarName = YDProjectManage::getSafeVirtualVarName(
      m_stopMotionModule->safeguard_referid);
  setSafeVarName(safeVarName);

  setInplaceWait(m_stopMotionModule->inplace_wait_type);
  setInplaceWaitValue(m_stopMotionModule->inplace_wait_value);
}
