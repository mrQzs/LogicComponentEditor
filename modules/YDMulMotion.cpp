#include "YDMulMotion.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDMulMotionName : public YDPropertyName {
 public:
  QString name() const { return YDMulMotionName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDMulMotionName::tr("错误"),
                               YDMulMotionName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDMulMotionName::tr("错误"),
                               YDMulMotionName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDMulMotionSpeedPos : public YDPropertySpeedCard {
 public:
  QString name() const { return YDMulMotionSpeedPos::tr("运动坐标"); }
  QString codeName() const { return "SpeedPos"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSpeedPosStr(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) m->setSpeedPosStr(str);
  }
};

class YDMulMotionSet : public YDCustomWProp {
 public:
  YDMulMotionSet() : YDCustomWProp(WidgetType::e_SETVARIABLE) {}
  virtual QString name() const { return YDMulMotionSet::tr("使能设置"); }
  virtual QString codeName() const { return "Set"; }

 protected:
  virtual QStringList get(YDModule *m) const { return m->getAxisList(); }

  virtual void set(YDModule *m, QStringList list) { m->setAxisList(list); }
};

class YDMulMotionSafe : public YDPropertySafeVar {
 public:
  QString name() const { return YDMulMotionSafe::tr("安全保护"); }
  QString codeName() const { return "Safe"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getSafeVarName(); }
  virtual void set(YDModule *m, QString str) { m->setSafeVarName(str); }
};

class YDMulMotionWait : public YDPropertyEnum {
 public:
  YDMulMotionWait(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDMulMotionWait::tr("到位等待"); }
  QString codeName() const { return "Wait"; }

 protected:
  virtual int get(YDModule *m) const { return m->getInplaceWait(); }
  virtual void set(YDModule *m, int index) { m->setInplaceWait(index); }
};

class YDMulMotionCustomErr : public YDPropertyInPlace {
 public:
  YDMulMotionCustomErr(YDModule *m)
      : YDPropertyInPlace{m, -999999, 999999}, m_module{m} {}
  QString name() const { return YDMulMotionCustomErr::tr("自定义误差带"); }
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

YDMulMotion::YDMulMotion() {
  setPreview(QPixmap(":/Module/Mul_Move.png"));
  auto w = new YDModuleWidget(this, MotionColor, MotionFColor);

  setWidget(w);

  m_properties << new YDMulMotionName;
  m_properties << new YDMulMotionSpeedPos;
  m_properties << new YDMulMotionSet;

  m_properties << new YDMulMotionSafe;

  QStringList waittype;
  waittype << YDMulMotion::tr("不等待") << YDMulMotion::tr("规划运动停止")
           << YDMulMotion::tr("默认误差带") << YDMulMotion::tr("自定义误差带");
  m_properties << new YDMulMotionWait(waittype);

  m_properties << new YDMulMotionCustomErr(this);
}

Module::Type YDMulMotion::type() const { return Module::Mul_Motion; }

void YDMulMotion::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachMultiAxisesMoveModule(logicProcessId,
                                               m_mulMotionModule);
  Q_ASSERT(m_mulMotionModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDMulMotion::tr("多轴运动%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDMulMotion::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachMultiAxisesMoveModule(lp->id, m_mulMotionModule);
  Q_ASSERT(m_mulMotionModule);
  setData();
}

void YDMulMotion::getData() {
  m_logicProcess->type = LOGIC_PROCESS_MULTIAXISES_MOVE;
  uint64 posVarId = YDProjectManage::getVirtualVarId(getSpeedPosStr());
  if (0 != posVarId) m_mulMotionModule->coords_referid = posVarId;

  uint64 safeVarId = YDProjectManage::getSafeVirtualVarId(getSafeVarName());
  if (0 != safeVarId) m_mulMotionModule->safeguard_referid = safeVarId;

  m_mulMotionModule->inplace_wait_type = getInplaceWait();

  m_mulMotionModule->inplace_wait_value = getInplaceWaitValue();
}

void YDMulMotion::setData() {
  auto varName =
      YDProjectManage::getVirtualVarName(m_mulMotionModule->coords_referid);
  setSpeedPosStr(varName);

  auto safeVarName = YDProjectManage::getSafeVirtualVarName(
      m_mulMotionModule->safeguard_referid);
  setSafeVarName(safeVarName);

  setInplaceWait(m_mulMotionModule->inplace_wait_type);
  setInplaceWaitValue(m_mulMotionModule->inplace_wait_value);
}
