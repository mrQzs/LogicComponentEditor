#include "YDJogMotion.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDJogMotionName : public YDPropertyName {
 public:
  QString name() const { return YDJogMotionName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDJogMotionName::tr("错误"),
                               YDJogMotionName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDJogMotionName::tr("错误"),
                               YDJogMotionName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDJogMotionAxie : public YDPropertyAxis {
 public:
  QString name() const { return YDJogMotionAxie::tr("运动轴号"); }
  QString codeName() const { return "Axie"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getAxisName(); }
  virtual void set(YDModule *m, QString str) { m->setAxisName(str); }
};

class YDJogMotionSpeed : public YDPropertyMSpeed {
 public:
  YDJogMotionSpeed(YDModule *m) : YDPropertyMSpeed{m} {}
  QString name() const { return YDJogMotionSpeed::tr("运动速度"); }
  QString codeName() const { return "SpeedWay"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSpeedStr(); }
  virtual void set(YDModule *m, QString str) { m->setSpeedStr(str); }
};

class YDJogMotionSpeedWay : public YDPropertyEnum {
 public:
  YDJogMotionSpeedWay(QStringList enumText, YDJogMotionSpeed *speed)
      : YDPropertyEnum{enumText}, m_curIndex{0}, m_speed{speed} {}
  QString name() const { return YDJogMotionSpeedWay::tr("运动速度方式"); }
  QString codeName() const { return "SpeedWay"; }

 protected:
  virtual int get(YDModule *m) const { return m->getSpeedWay(); }
  virtual void set(YDModule *m, int index) { m->setSpeedWay(index); }

 private:
  int m_curIndex;
  YDJogMotionSpeed *m_speed;
};

class YDJogMotionSafe : public YDPropertySafeVar {
 public:
  QString name() const { return YDJogMotionSafe::tr("安全保护"); }
  QString codeName() const { return "Safe"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSafeVarName(); }
  virtual void set(YDModule *m, QString str) { m->setSafeVarName(str); }
};

YDJogMotion::YDJogMotion() {
  setPreview(QPixmap(":/Module/Jog_Move.png"));
  auto w = new YDModuleWidget(this, MotionColor, MotionFColor);

  setWidget(w);

  QStringList speedWay;
  speedWay << YDJogMotion::tr("百分比") << YDJogMotion::tr("变量");

  m_properties << new YDJogMotionName;
  m_properties << new YDJogMotionAxie;

  auto sp = new YDJogMotionSpeed(this);
  m_properties << new YDJogMotionSpeedWay(speedWay, sp);
  m_properties << sp;

  m_properties << new YDJogMotionSafe;
}

Module::Type YDJogMotion::type() const { return Module::Jog_Motion; }

void YDJogMotion::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachJogMoveModule(logicProcessId, m_jogMotionModule);
  Q_ASSERT(m_jogMotionModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDJogMotion::tr("Jog运动%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDJogMotion::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachJogMoveModule(lp->id, m_jogMotionModule);
  Q_ASSERT(m_jogMotionModule);
  setData();
}

void YDJogMotion::getData() {
  m_logicProcess->type = LOGIC_PROCESS_JOG_MOVE;
  auto axisList = YDProjectManage::getAxisList();

  auto axis_name = getAxisName();
  for (auto a : axisList) {
    if (QString::fromLocal8Bit(a->axis_name) == axis_name) {
      m_jogMotionModule->device_id = a->device_id;
      m_jogMotionModule->axis_index = a->axis_index;
      break;
    }
  }

  if (getSpeedWay()) {
    uint64 speedVarId = YDProjectManage::getVarId(getSpeedStr());
    if (speedVarId != 0) {
      m_jogMotionModule->velocity_referid = speedVarId;
    }
  } else {
    auto str = getSpeedStr();
    str = str.mid(0, str.size() - 1);
    m_jogMotionModule->velocity_referid = str.toUInt();
  }

  uint64 safeVarId = YDProjectManage::getSafeVirtualVarId(getSafeVarName());
  if (0 != safeVarId) m_jogMotionModule->safeguard_referid = safeVarId;

  m_jogMotionModule->inplace_wait_type = getInplaceWait();

  m_jogMotionModule->inplace_wait_value = getInplaceWaitValue();
}

void YDJogMotion::setData() {
  auto axisList = YDProjectManage::getAxisList();
  auto device_id = m_jogMotionModule->device_id;
  auto axis_index = m_jogMotionModule->axis_index;

  QString name;

  for (auto a : axisList)
    if (device_id == a->device_id)
      if (axis_index == a->axis_index)
        name = QString::fromLocal8Bit(a->axis_name.c_str());

  setAxisName(name);

  if (m_jogMotionModule->velocity_referid <= 100) {
    setSpeedWay(0);
    auto str = QString::number(m_jogMotionModule->velocity_referid) + "%";
    setSpeedStr(str);
  } else {
    setSpeedWay(1);
    auto list = YDProjectManage::getAllVirtualVariables();
    auto id = m_jogMotionModule->velocity_referid;
    for (auto v : list) {
      if (id == v->variable_id) {
        QString str = QString::fromLocal8Bit(v->variable_name);
        setSpeedStr(str);
        break;
      }
    }
  }

  auto safeVarName = YDProjectManage::getSafeVirtualVarName(
      m_jogMotionModule->safeguard_referid);
  setSafeVarName(safeVarName);

  setInplaceWait(m_jogMotionModule->inplace_wait_type);
  setInplaceWaitValue(m_jogMotionModule->inplace_wait_value);
}
