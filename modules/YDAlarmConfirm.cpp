#include "YDAlarmConfirm.h"

#include <QMessageBox>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDTask.h"
#include "properties/YDProperties.h"
#include "widget/module/YDModuleWidget.h"

class YDAlarmConfirmName : public YDPropertyName {
 public:
  QString name() const { return YDAlarmConfirmName::tr("名称"); }
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
          QMessageBox::warning(nullptr, YDAlarmConfirmName::tr("错误"),
                               YDAlarmConfirmName::tr("更新名称失败!"));
          break;
        case 0: {
          m->setName(str);
          m->updateItemName(str);
        } break;
        case 1:
          QMessageBox::warning(nullptr, YDAlarmConfirmName::tr("错误"),
                               YDAlarmConfirmName::tr("名称已重复!"));
          break;
      }
    }
  }
};

class YDAlarmConfirmLevel : public YDPropertyEnum {
 public:
  YDAlarmConfirmLevel(const QStringList &enumText) : YDPropertyEnum{enumText} {}
  virtual QString name() const { return YDAlarmConfirmLevel::tr("消息级别"); }
  virtual QString codeName() const { return "Level"; }

 protected:
  virtual int get(YDModule *m) const { return m->getAlarmLevel(); }
  virtual void set(YDModule *m, int index) { m->setAlarmLevel(index); }
};

class YDAlarmConfirmContent : public YDPropertyString {
 public:
  QString name() const { return YDAlarmConfirmName::tr("消息内容"); }
  QString codeName() const { return "Content"; }

 protected:
  virtual QString get(YDModule *m) const { return m->getAlarmContent(); }
  virtual void set(YDModule *m, QString str) {
    if (!str.isEmpty()) m->setAlarmContent(str);
  }
};

class YDAlarmConfirmActions : public YDCustomWProp {
 public:
  YDAlarmConfirmActions(YDModule *m)
      : YDCustomWProp(m, WidgetType::e_ALARMACTION) {}
  virtual QString name() const { return YDAlarmConfirmActions::tr("动作类型"); }
  virtual QString codeName() const { return "Actions"; }

 protected:
  virtual QStringList get(YDModule *m) const { return m->getAlarmActions(); }
  virtual void set(YDModule *m, QStringList list) { m->setAlarmActions(list); }
};

YDAlarmConfirm::YDAlarmConfirm() {
  setPreview(QPixmap(":/Module/Alarm_Confirm.png"));
  auto w = new YDModuleWidget(this, OtherColor, OtherFColor);

  setWidget(w);

  m_properties << new YDAlarmConfirmName;

  QStringList level;
  level << YDAlarmConfirm::tr("提示") << YDAlarmConfirm::tr("警告")
        << YDAlarmConfirm::tr("错误");
  m_properties << new YDAlarmConfirmLevel(level);

  m_properties << new YDAlarmConfirmContent;
  m_properties << new YDAlarmConfirmActions(this);
}

Module::Type YDAlarmConfirm::type() const { return Module::Alarm_Confirm; }

void YDAlarmConfirm::initModule(YDTask *task, uint64 parentId) {
  init(task);
  auto logicProcessId = getLogicProcessId();
  YDProjectManage::attachMessageModule(logicProcessId, m_messageModule);
  Q_ASSERT(m_messageModule);
  if (0 != parentId) m_logicProcess->parent_id = parentId;
  QString name = YDAlarmConfirm::tr("报警确认%1").arg(m_logicProcess->id);
  m_logicProcess->name = std::string(name.toLocal8Bit().data());
}

void YDAlarmConfirm::initModule(yd::lg::LogicProcess *lp) {
  m_logicProcess = lp;
  YDProjectManage::attachMessageModule(lp->id, m_messageModule);
  Q_ASSERT(m_messageModule);
  setData();
}

void YDAlarmConfirm::getData() {
  m_logicProcess->type = LOGIC_PROCESS_MESSAGE;
  m_messageModule->level = getAlarmLevel() + LOG_LEVEL_INFO;
}

void YDAlarmConfirm::setData() {
  setAlarmLevel(m_messageModule->level - LOG_LEVEL_INFO);
  QStringList actions;

  auto nm1 =
      STRTQSTR(m_messageModule->pAction1->action_name.c_str());
  auto nm2 =
      STRTQSTR(m_messageModule->pAction2->action_name.c_str());
  auto nm3 =
      STRTQSTR(m_messageModule->pAction3->action_name.c_str());
  auto nm4 =
      STRTQSTR(m_messageModule->pAction4->action_name.c_str());

  if (m_messageModule->pAction1->selected) actions << nm1;
  if (m_messageModule->pAction2->selected) actions << nm2;
  if (m_messageModule->pAction3->selected) actions << nm3;
  if (m_messageModule->pAction4->selected) actions << nm4;

  setAlarmActions(actions);
}

quint32 YDAlarmConfirm::getAction(const QString &str) {
  if (str == YDAlarmConfirm::tr("确认")) return INTERACT_COMMAND_CONFIRM;
  if (str == YDAlarmConfirm::tr("忽略")) return INTERACT_COMMAND_IGNORE;
  if (str == YDAlarmConfirm::tr("重试")) return INTERACT_COMMAND_RETRY;
  return INTERACT_COMMAND_TERMINATE;
}

QString YDAlarmConfirm::getActionStr(quint32 value) const {
  switch (value) {
    case INTERACT_COMMAND_CONFIRM:
      return YDAlarmConfirm::tr("确认");
    case INTERACT_COMMAND_IGNORE:
      return YDAlarmConfirm::tr("忽略");
    case INTERACT_COMMAND_RETRY:
      return YDAlarmConfirm::tr("重试");
  }
  return YDAlarmConfirm::tr("终止");
}
