#include "YDRelMotion.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDRelMotionName : public YDPropertyName {
 public:
  QString name() const { return YDRelMotionName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDRelMotionName::tr("错误"),
                               YDRelMotionName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDRelMotionName::tr("错误"),
                               YDRelMotionName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDRelMotionAxie : public YDPropertyAxis {
 public:
  QString name() const { return YDRelMotionAxie::tr("运动轴号"); }
  QString codeName() const { return "Axie"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getAxisName(); }
  virtual void set(YDModule *m, QString str) { m->setAxisName(str); }
};

class YDRelMotionPosion : public YDPropertyVar {
 public:
  QString name() const { return YDRelMotionPosion::tr("运动距离(毫米)"); }
  QString codeName() const { return "Posion"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getPosVarName(); }
  virtual void set(YDModule *m, QString str) { m->setPosVarName(str); }
};

class YDRelMotionSpeed : public YDPropertyMSpeed {
 public:
  YDRelMotionSpeed(YDModule *m) : YDPropertyMSpeed{m} {}
  QString name() const { return YDRelMotionSpeed::tr("运动速度"); }
  QString codeName() const { return "SpeedWay"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSpeedStr(); }
  virtual void set(YDModule *m, QString str) { m->setSpeedStr(str); }
};

class YDRelMotionSpeedWay : public YDPropertyEnum {
 public:
  YDRelMotionSpeedWay(QStringList enumText, YDRelMotionSpeed *speed)
      : YDPropertyEnum{enumText}, m_curIndex{0}, m_speed{speed} {}
  QString name() const { return YDRelMotionSpeedWay::tr("运动速度方式"); }
  QString codeName() const { return "SpeedWay"; }

 protected:
  virtual int get(YDModule *m) const { return m->getSpeedWay(); }
  virtual void set(YDModule *m, int index) { m->setSpeedWay(index); }

 private:
  int m_curIndex;
  YDRelMotionSpeed *m_speed;
};

class YDRelMotionSafe : public YDPropertySafeVar {
 public:
  QString name() const { return YDRelMotionSafe::tr("安全保护"); }
  QString codeName() const { return "Safe"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSafeVarName(); }
  virtual void set(YDModule *m, QString str) { m->setSafeVarName(str); }
};

class YDRelMotionWait : public YDPropertyEnum {
 public:
  YDRelMotionWait(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDRelMotionWait::tr("到位等待"); }
  QString codeName() const { return "Wait"; }

 protected:
  virtual int get(YDModule *m) const { return m->getInplaceWait(); }
  virtual void set(YDModule *m, int index) { m->setInplaceWait(index); }
};

class YDRelMotionCustomErr : public YDPropertyInPlace {
 public:
  YDRelMotionCustomErr(YDModule *m)
      : YDPropertyInPlace{m, -999999, 999999}, m_module{m} {}
  QString name() const { return YDRelMotionCustomErr::tr("自定义误差带"); }
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

YDRelMotion::YDRelMotion() {
  setPreview(QPixmap(":/Module/Rel_Move.png"));
  auto w = new YDModuleWidget(this, MotionColor, MotionFColor);

  setWidget(w);

  QStringList speedWay;
  speedWay << YDRelMotion::tr("百分比") << YDRelMotion::tr("变量");

  QStringList asyn;
  asyn << YDRelMotion::tr("否") << YDRelMotion::tr("是");
  m_properties << new YDRelMotionName;
  m_properties << new YDRelMotionAxie;
  m_properties << new YDRelMotionPosion;

  auto sp = new YDRelMotionSpeed(this);
  m_properties << new YDRelMotionSpeedWay(speedWay, sp);
  m_properties << sp;

  m_properties << new YDRelMotionSafe;

  QStringList waittype;
  waittype << YDRelMotion::tr("不等待") << YDRelMotion::tr("规划运动停止")
           << YDRelMotion::tr("默认误差带") << YDRelMotion::tr("自定义误差带");
  m_properties << new YDRelMotionWait(waittype);

  m_properties << new YDRelMotionCustomErr(this);
}

Module::Type YDRelMotion::type() const { return Module::Rel_Motion; }

void YDRelMotion::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachRelativeMoveModule(logicProcessId, m_relMotionModule);
  Q_ASSERT(m_relMotionModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDRelMotion::tr("相对运动%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDRelMotion::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachRelativeMoveModule(lp->id, m_relMotionModule);
  Q_ASSERT(m_relMotionModule);
  setData();
}

void YDRelMotion::getData() {
  m_logicProcess->type = LOGIC_PROCESS_RELATIVE_MOVE;
  auto axisList = YDProjectManage::getAxisList();
  auto axis_name = getAxisName();

  for (auto a : axisList) {
    if (QString::fromLocal8Bit(a->axis_name) == axis_name) {
      m_relMotionModule->device_id = a->device_id;
      m_relMotionModule->axis_index = a->axis_index;
      break;
    }
  }

  uint64 posVarId = YDProjectManage::getVarId(getPosVarName());
  if (0 != posVarId) m_relMotionModule->distance_referid = posVarId;

  if (getSpeedWay()) {
    uint64 speedVarId = YDProjectManage::getVarId(getSpeedStr());
    if (speedVarId != 0) {
      m_relMotionModule->velocity_referid = speedVarId;
    }
  } else {
    auto str = getSpeedStr();
    str = str.mid(0, str.size() - 1);
    m_relMotionModule->velocity_referid = str.toUInt();
  }

  uint64 safeVarId = YDProjectManage::getSafeVirtualVarId(getSafeVarName());
  if (0 != safeVarId) m_relMotionModule->safeguard_referid = safeVarId;

  m_relMotionModule->inplace_wait_type = getInplaceWait();

  m_relMotionModule->inplace_wait_value = getInplaceWaitValue();
}

void YDRelMotion::setData() {
  auto axisList = YDProjectManage::getAxisList();
  auto device_id = m_relMotionModule->device_id;
  auto axis_index = m_relMotionModule->axis_index;

  QString name;

  for (auto a : axisList)
    if (device_id == a->device_id)
      if (axis_index == a->axis_index)
        name = QString::fromLocal8Bit(a->axis_name.c_str());

  setAxisName(name);

  auto varName =
      YDProjectManage::getVarName(m_relMotionModule->distance_referid);
  setPosVarName(varName);

  if (m_relMotionModule->velocity_referid <= 100) {
    setSpeedWay(0);
    auto str = QString::number(m_relMotionModule->velocity_referid) + "%";
    setSpeedStr(str);
  } else {
    setSpeedWay(1);
    auto list = YDProjectManage::getAllVirtualVariables();
    auto id = m_relMotionModule->velocity_referid;
    for (auto v : list) {
      if (id == v->variable_id) {
        QString str = QString::fromLocal8Bit(v->variable_name);
        setSpeedStr(str);
        break;
      }
    }
  }

  auto safeVarName = YDProjectManage::getSafeVirtualVarName(
      m_relMotionModule->safeguard_referid);
  setSafeVarName(safeVarName);

  setInplaceWait(m_relMotionModule->inplace_wait_type);
  setInplaceWaitValue(m_relMotionModule->inplace_wait_value);
}
