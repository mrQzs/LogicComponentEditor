#include "YDWaitMotion.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDWaitMotionName : public YDPropertyName {
 public:
  QString name() const { return YDWaitMotionName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDWaitMotionName::tr("错误"),
                               YDWaitMotionName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDWaitMotionName::tr("错误"),
                               YDWaitMotionName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDWaitMotionWay : public YDPropertyEnum {
 public:
  YDWaitMotionWay(QStringList enumText) : YDPropertyEnum{enumText} {}
  virtual QString name() const { return YDWaitMotionWay::tr("逻辑运算符"); }
  virtual QString codeName() const { return "Way"; }

 protected:
  virtual int get(YDModule *m) const { return m->getWaitConditionWay(); }
  virtual void set(YDModule *m, int index) { m->setWaitConditionWay(index); }
};

class YDWaitMotionList : public YDCustomWProp {
 public:
  YDWaitMotionList() : YDCustomWProp(WidgetType::e_INPLACEWAIT) {}
  virtual QString name() const {
    return YDWaitMotionList::tr("轴到位等待列表");
  }
  virtual QString codeName() const { return "AxisList"; }

 protected:
  virtual QStringList get(YDModule *m) const { return m->getAxisWaitList(); }
  virtual void set(YDModule *m, QStringList list) { m->setAxisWaitList(list); }
};

YDWaitMotion::YDWaitMotion() {
  setPreview(QPixmap(":/Module/Inplace_Wait.png"));
  auto w = new YDModuleWidget(this, MotionColor, MotionFColor);

  setWidget(w);

  m_properties << new YDWaitMotionName;

  QStringList conditionWay;
  conditionWay << YDWaitMotion::tr("与运算") << YDWaitMotion::tr("或运算");
  m_properties << new YDWaitMotionWay(conditionWay);
  m_properties << new YDWaitMotionList;
}

Module::Type YDWaitMotion::type() const { return Module::Wait_Motion; }

void YDWaitMotion::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachInplaceWaitModule(logicProcessId, m_inplaceWaitModule);
  Q_ASSERT(m_inplaceWaitModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDWaitMotion::tr("到位等待%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
  m_inplaceWaitModule->logic_operator = LOGIC_OPERATOR_AND;
}

void YDWaitMotion::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachInplaceWaitModule(lp->id, m_inplaceWaitModule);
  Q_ASSERT(m_inplaceWaitModule);
  setData();
}

void YDWaitMotion::getData() {
  m_logicProcess->type = LOGIC_PROCESS_INPLACE_WAIT;
  m_inplaceWaitModule->logic_operator =
      getWaitConditionWay() + LOGIC_OPERATOR_AND;
}

void YDWaitMotion::setData() {
  setWaitConditionWay(m_inplaceWaitModule->logic_operator - LOGIC_OPERATOR_AND);
}
