#include "YDBackZMotion.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDBackZMotionName : public YDPropertyName {
 public:
  QString name() const { return YDBackZMotionName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDBackZMotionName::tr("错误"),
                               YDBackZMotionName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDBackZMotionName::tr("错误"),
                               YDBackZMotionName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDBackZMotionAxie : public YDPropertyAxis {
 public:
  QString name() const { return YDBackZMotionAxie::tr("运动轴号"); }
  QString codeName() const { return "Axie"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getAxisName(); }
  virtual void set(YDModule *m, QString str) { m->setAxisName(str); }
};

class YDBackZMotionSafe : public YDPropertySafeVar {
 public:
  QString name() const { return YDBackZMotionSafe::tr("安全保护"); }
  QString codeName() const { return "Safe"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSafeVarName(); }
  virtual void set(YDModule *m, QString str) { m->setSafeVarName(str); }
};

class YDBackZMotionWait : public YDPropertyEnum {
 public:
  YDBackZMotionWait(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDBackZMotionWait::tr("到位等待"); }
  QString codeName() const { return "Wait"; }

 protected:
  virtual int get(YDModule *m) const { return m->getInplaceWait(); }
  virtual void set(YDModule *m, int index) { m->setInplaceWait(index); }
};

class YDBackZMotionCustomErr : public YDPropertyInPlace {
 public:
  YDBackZMotionCustomErr(YDModule *m)
      : YDPropertyInPlace{m, -999999, 999999}, m_module{m} {}
  QString name() const { return YDBackZMotionCustomErr::tr("自定义误差带"); }
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

YDBackZMotion::YDBackZMotion() {
  setPreview(QPixmap(":/Module/Zero_Move.png"));
  auto w = new YDModuleWidget(this, MotionColor, MotionFColor);

  setWidget(w);

  m_properties << new YDBackZMotionName;
  m_properties << new YDBackZMotionAxie;

  m_properties << new YDBackZMotionSafe;

  QStringList waittype;
  waittype << YDBackZMotion::tr("不等待") << YDBackZMotion::tr("规划运动停止")
           << YDBackZMotion::tr("默认误差带")
           << YDBackZMotion::tr("自定义误差带");
  m_properties << new YDBackZMotionWait(waittype);

  m_properties << new YDBackZMotionCustomErr(this);
}

Module::Type YDBackZMotion::type() const { return Module::BackZ_Motion; }

void YDBackZMotion::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachHomeMoveModule(logicProcessId, m_backZMotionModule);
  Q_ASSERT(m_backZMotionModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDBackZMotion::tr("回零运动%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDBackZMotion::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachHomeMoveModule(lp->id, m_backZMotionModule);
  Q_ASSERT(m_backZMotionModule);
  setData();
}

void YDBackZMotion::getData() {
  m_logicProcess->type = LOGIC_PROCESS_HOME_MOVE;
  auto axisList = YDProjectManage::getAxisList();

  auto axis_name = getAxisName();
  for (auto a : axisList) {
    if (STRTQSTR(a->axis_name) == axis_name) {
      m_backZMotionModule->device_id = a->device_id;
      m_backZMotionModule->axis_index = a->axis_index;
      break;
    }
  }

  uint64 safeVarId = YDProjectManage::getSafeVirtualVarId(getSafeVarName());
  if (0 != safeVarId) m_backZMotionModule->safeguard_referid = safeVarId;

  m_backZMotionModule->inplace_wait_type = getInplaceWait();

  m_backZMotionModule->inplace_wait_value = getInplaceWaitValue();
}

void YDBackZMotion::setData() {
  auto axisList = YDProjectManage::getAxisList();
  auto device_id = m_backZMotionModule->device_id;
  auto axis_index = m_backZMotionModule->axis_index;

  QString name;

  for (auto a : axisList)
    if (device_id == a->device_id)
      if (axis_index == a->axis_index)
        name = STRTQSTR(a->axis_name.c_str());

  setAxisName(name);

  auto safeVarName = YDProjectManage::getSafeVirtualVarName(
      m_backZMotionModule->safeguard_referid);
  setSafeVarName(safeVarName);

  setInplaceWait(m_backZMotionModule->inplace_wait_type);
  setInplaceWaitValue(m_backZMotionModule->inplace_wait_value);
}
