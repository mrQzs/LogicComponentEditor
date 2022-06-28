#include "YDDelayWait.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDDelayWaitName : public YDPropertyName {
 public:
  QString name() const { return YDDelayWaitName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDDelayWaitName::tr("错误"),
                               YDDelayWaitName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDDelayWaitName::tr("错误"),
                               YDDelayWaitName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDDelayWaitWay : public YDPropertyEnum {
 public:
  YDDelayWaitWay(QStringList enumText) : YDPropertyEnum{enumText} {}
  QString name() const { return YDDelayWaitWay::tr("延时方式"); }
  QString codeName() const { return "Way"; }

 protected:
  virtual int get(YDModule *m) const { return m->getDelayType(); }
  virtual void set(YDModule *m, int index) { m->setDelayType(index); }
};

class YDDelayWaitValue : public YDPropertyDelayTime {
 public:
  YDDelayWaitValue(YDModule *m) : YDPropertyDelayTime{m} {}
  QString name() const { return YDDelayWaitName::tr("延时时间(ms)"); }
  QString codeName() const { return "Value"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getDelayValue(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) m->setDelayValue(str);
  }
};

YDDelayWait::YDDelayWait() {
  setPreview(QPixmap(":/Module/Delay_Wait.png"));
  auto w = new YDModuleWidget(this, ControlColor, ControlFColor);

  setWidget(w);

  QStringList way;
  way << YDDelayWait::tr("数值") << YDDelayWait::tr("变量");

  m_properties << new YDDelayWaitName;
  m_properties << new YDDelayWaitWay(way);
  m_properties << new YDDelayWaitValue(this);
}

Module::Type YDDelayWait::type() const { return Module::Delay_Wait; }

void YDDelayWait::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachDelayModule(logicProcessId, m_delayModule);
  Q_ASSERT(m_delayModule);
  m_delayModule->delay_time = 0;
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDDelayWait::tr("延时等待%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDDelayWait::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachDelayModule(lp->id, m_delayModule);
  Q_ASSERT(m_delayModule);
  setData();
}

void YDDelayWait::getData() {
  m_logicProcess->type = LOGIC_PROCESS_DELAY;
  if (0 == getDelayType())
    m_delayModule->delay_time = getDelayValue().toULongLong();
  else {
    m_delayModule->delay_time =
        YDProjectManage::getVirtualVarId(getDelayValue());
  }
}

void YDDelayWait::setData() {
  auto type = m_delayModule->delay_time;
  if (type >= OFFSET_VALUE_TYPE) {
    setDelayType(1);
    setDelayValue(YDProjectManage::getVirtualVarName(type));
  } else
    setDelayValue(QString::number(type));
}
