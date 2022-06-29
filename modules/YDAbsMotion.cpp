#include "YDAbsMotion.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDAbsMotionName : public YDPropertyName {
 public:
  QString name() const { return YDAbsMotionName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDAbsMotionName::tr("错误"),
                               YDAbsMotionName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDAbsMotionName::tr("错误"),
                               YDAbsMotionName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDAbsMotionAxie : public YDPropertyAxis {
 public:
  QString name() const { return YDAbsMotionAxie::tr("运动轴号"); }
  QString codeName() const { return "Axie"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getAxisName(); }
  virtual void set(YDModule *m, QString str) { m->setAxisName(str); }
};

class YDAbsMotionPosion : public YDPropertyVar {
 public:
  QString name() const { return YDAbsMotionPosion::tr("目标位置(毫米)"); }
  QString codeName() const { return "Posion"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getPosVarName(); }
  virtual void set(YDModule *m, QString str) { m->setPosVarName(str); }
};

class YDAbsMotionSpeed : public YDPropertyMSpeed {
 public:
  YDAbsMotionSpeed(YDModule *m) : YDPropertyMSpeed{m} {}
  QString name() const { return YDAbsMotionSpeed::tr("运动速度"); }
  QString codeName() const { return "SpeedWay"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSpeedStr(); }
  virtual void set(YDModule *m, QString str) { m->setSpeedStr(str); }
};

class YDAbsMotionSpeedWay : public YDPropertyEnum {
 public:
  YDAbsMotionSpeedWay(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDAbsMotionSpeedWay::tr("运动速度方式"); }
  QString codeName() const { return "SpeedWay"; }

 protected:
  virtual int get(YDModule *m) const { return m->getSpeedWay(); }
  virtual void set(YDModule *m, int index) { m->setSpeedWay(index); }
};

class YDAbsMotionSafe : public YDPropertySafeVar {
 public:
  QString name() const { return YDAbsMotionSafe::tr("安全保护"); }
  QString codeName() const { return "Safe"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSafeVarName(); }
  virtual void set(YDModule *m, QString str) { m->setSafeVarName(str); }
};

class YDAbsMotionWait : public YDPropertyEnum {
 public:
  YDAbsMotionWait(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDAbsMotionWait::tr("到位等待"); }
  QString codeName() const { return "Wait"; }

 protected:
  virtual int get(YDModule *m) const { return m->getInplaceWait(); }
  virtual void set(YDModule *m, int index) { m->setInplaceWait(index); }
};

class YDAbsMotionCustomErr : public YDPropertyInPlace {
 public:
  YDAbsMotionCustomErr(YDModule *m)
      : YDPropertyInPlace{m, -999999, 999999}, m_module{m} {}
  QString name() const { return YDAbsMotionCustomErr::tr("自定义误差带"); }
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

YDAbsMotion::YDAbsMotion() {
  setPreview(QPixmap(":/Module/Abs_Move.png"));
  auto w = new YDModuleWidget(this, MotionColor, MotionFColor);

  setWidget(w);

  QStringList speedWay;
  speedWay << YDAbsMotion::tr("百分比") << YDAbsMotion::tr("变量");

  m_properties << new YDAbsMotionName;
  m_properties << new YDAbsMotionAxie;
  m_properties << new YDAbsMotionPosion;

  auto sp = new YDAbsMotionSpeed(this);
  m_properties << new YDAbsMotionSpeedWay(speedWay);
  m_properties << sp;

  m_properties << new YDAbsMotionSafe;

  QStringList waittype;
  waittype << YDAbsMotion::tr("不等待") << YDAbsMotion::tr("规划运动停止")
           << YDAbsMotion::tr("默认误差带") << YDAbsMotion::tr("自定义误差带");
  m_properties << new YDAbsMotionWait(waittype);

  m_properties << new YDAbsMotionCustomErr(this);
}

Module::Type YDAbsMotion::type() const { return Module::Abs_Motion; }

void YDAbsMotion::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachAbsoluteMoveModule(logicProcessId, m_absMotionModule);
  Q_ASSERT(m_absMotionModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDAbsMotion::tr("绝对运动%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDAbsMotion::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachAbsoluteMoveModule(lp->id, m_absMotionModule);
  Q_ASSERT(m_absMotionModule);
  setData();
}

void YDAbsMotion::getData() {
  m_logicProcess->type = LOGIC_PROCESS_ABSOLUTE_MOVE;
  auto axisList = YDProjectManage::getAxisList();
  auto axis_name = getAxisName();

  for (auto a : axisList) {
    if (STRTQSTR(a->axis_name) == axis_name) {
      m_absMotionModule->device_id = a->device_id;
      m_absMotionModule->axis_index = a->axis_index;
      break;
    }
  }

  uint64 posVarId = YDProjectManage::getVirtualVarId(getPosVarName());
  if (0 != posVarId) m_absMotionModule->position_referid = posVarId;

  if (getSpeedWay()) {
    uint64 speedVarId = YDProjectManage::getVarId(getSpeedStr());
    if (speedVarId != 0) {
      m_absMotionModule->velocity_referid = speedVarId;
    }
  } else {
    auto str = getSpeedStr();
    str = str.mid(0, str.size() - 1);
    m_absMotionModule->velocity_referid = str.toUInt();
  }

  uint64 safeVarId = YDProjectManage::getSafeVirtualVarId(getSafeVarName());
  if (0 != safeVarId) m_absMotionModule->safeguard_referid = safeVarId;

  m_absMotionModule->inplace_wait_type = getInplaceWait();

  m_absMotionModule->inplace_wait_value = getInplaceWaitValue();
}

void YDAbsMotion::setData() {
  auto axisList = YDProjectManage::getAxisList();
  auto device_id = m_absMotionModule->device_id;
  auto axis_index = m_absMotionModule->axis_index;

  QString name;

  for (auto a : axisList)
    if (device_id == a->device_id)
      if (axis_index == a->axis_index)
        name = STRTQSTR(a->axis_name.c_str());

  setAxisName(name);

  auto varName =
      YDProjectManage::getVarName(m_absMotionModule->position_referid);
  setPosVarName(varName);

  if (m_absMotionModule->velocity_referid <= 100) {
    setSpeedWay(0);
    auto str = QString::number(m_absMotionModule->velocity_referid) + "%";
    setSpeedStr(str);
  } else {
    setSpeedWay(1);
    auto list = YDProjectManage::getAllVirtualVariables();
    auto id = m_absMotionModule->velocity_referid;
    for (auto v : list) {
      if (id == v->variable_id) {
        QString str = STRTQSTR(v->variable_name);
        setSpeedStr(str);
        break;
      }
    }
  }

  auto safeVarName = YDProjectManage::getSafeVirtualVarName(
      m_absMotionModule->safeguard_referid);
  setSafeVarName(safeVarName);

  setInplaceWait(m_absMotionModule->inplace_wait_type);
  setInplaceWaitValue(m_absMotionModule->inplace_wait_value);
}
