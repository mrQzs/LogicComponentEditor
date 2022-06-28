#include "YDModule.h"

#include <QMessageBox>

#include "RapidJsonHelper.h"
#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "properties/YDProperty.h"
#include "widget/module/YDIfConditionWidget.h"
#include "widget/module/YDModuleIFElseWidget.h"
#include "widget/module/YDModuleLoopWidget.h"
#include "widget/module/YDModuleWidget.h"
#include "yd_project.h"

// const QColor MotionColor = QColor("#4c97ff");
// const QColor IoColor = QColor("#ec6337");
// const QColor ControlColor = QColor("#ffab19");
// const QColor OtherColor = QColor("#ff8c1a");

const QColor MotionColor = Qt::white;
const QColor MotionFColor = Qt::black;
const QColor IoColor = Qt::white;
const QColor IoFColor = Qt::black;
const QColor ControlColor = Qt::white;
const QColor ControlFColor = Qt::black;
const QColor OtherColor = Qt::white;
const QColor OtherFColor = Qt::black;
YDModule *selectModule = nullptr;

YDModule::YDModule()
    : m_task{nullptr},
      m_logicProcess{nullptr},
      m_absMotionModule{nullptr},
      m_relMotionModule{nullptr},
      m_jogMotionModule{nullptr},
      m_mulMotionModule{nullptr},
      m_backZMotionModule{nullptr},
      m_stopMotionModule{nullptr},
      m_inplaceWaitModule{nullptr},
      m_doControlModule{nullptr},
      m_aoControlModule{nullptr},
      m_cylinderModule{nullptr},
      m_ifElseProcess{nullptr},
      m_ifProcess{nullptr},
      m_timesLoopModule{nullptr},
      m_conditionProcess{nullptr},
      m_jumpModule{nullptr},
      m_delayModule{nullptr},
      m_subTaskModule{nullptr},
      m_messageModule{nullptr},
      m_taskWaitModule{nullptr},
      m_programModule{nullptr},
      m_speedWay{0},
      m_stopWay{0},
      m_doState{0},
      m_loopTimes{0},
      m_inplaceWait{0},
      m_inplaceWaitValue{0},
      m_alarmLevel{0},
      m_delayType{0},
      m_waitTime{0},
      m_codeType{0},
      m_dataCashSize{0} {}

YDModule::~YDModule() {
  auto w = reinterpret_cast<YDModuleWidget *>(m_widget);
  delete w;
}

void YDModule::setStateMap(const QMap<uint32, yd::proto::ProcState> &) {}

void YDModule::resize() { m_task->resizeModel(); }

QPixmap YDModule::preview(int type) const {
  if (1 == type)
    return m_preview.scaled(100, 150, Qt::IgnoreAspectRatio,
                            Qt::SmoothTransformation);
  return m_preview;
}

QString YDModule::name() const {
  return QString::fromLocal8Bit(m_logicProcess->name.c_str());
}

QWidget *YDModule::widget() const { return m_widget; }

QList<YDProperty *> YDModule::properties() const { return m_properties; }

YDProperty *YDModule::property(const QString &name) const {
  for (YDProperty *p : m_properties) {
    if (p->name() == name) return p;
  }
  return nullptr;
}

int YDModule::high() const { return 30; }

uint32 YDModule::getLogicProcessId() { return m_logicProcess->id; }

bool YDModule::isValid() const { return true; }

proto::ProcState YDModule::getDebugState() const { return m_debugState; }

uint32 YDModule::getParentId() const { return m_logicProcess->parent_id; }

QString YDModule::icon() const { return ":/Module/Module.png"; }

void YDModule::setPreview(const QPixmap &p) { m_preview = p; }

void YDModule::setName(const QString &name) {
  m_logicProcess->name = name.toLocal8Bit();
}

void YDModule::setWidget(QWidget *w) { m_widget = w; }

void YDModule::setParentId(uint32 id) { m_logicProcess->parent_id = id; }

void YDModule::setDebugState(proto::ProcState &state) { m_debugState = state; }

void YDModule::init(YDTask *task) {
  m_task = task;
  YDProjectManage::createTaskProcess(task->id(), m_logicProcess);
  Q_ASSERT(m_logicProcess);
  m_logicProcess->parent_id = task->id();
}

void YDModule::setTask(YDTask *task) { m_task = task; }

void YDModule::updateItemName(const QString &name) {
  auto w = static_cast<YDModuleWidget *>(m_widget);
  w->setText(name);
  w->update();
}

void YDModule::updateIfName(const QString &name) {
  auto w = static_cast<YDIfConditionWidget *>(m_widget);
  w->setText(name);
  w->update();
}

void YDModule::updateIfElseName(const QString &name) {
  auto w = static_cast<YDModuleIFElseWidget *>(m_widget);
  w->setText(name);
  w->update();
}

void YDModule::updateLoopName(const QString &name) {
  auto w = static_cast<YDModuleLoopWidget *>(m_widget);
  w->setText(name);
  w->update();
}

void YDModule::setPreviousId(uint64 id) { m_logicProcess->previous_id = id; }

void YDModule::setNextId(uint64 id) { m_logicProcess->next_id = id; }

void YDModule::release() {
  YDProjectManage::deleteTaskProcess(m_task->id(), m_logicProcess->id);
}

void YDModule::copy(YDModule *) {}

YDTask *YDModule::getYDTask() const { return m_task; }

QList<yd::lg::MessageAction *> YDModule::getActions() const {
  QList<yd::lg::MessageAction *> list;
  list.push_back(m_messageModule->pAction1);
  list.push_back(m_messageModule->pAction2);
  list.push_back(m_messageModule->pAction3);
  list.push_back(m_messageModule->pAction4);

  return list;
}

lg::AxisInplaceWait *YDModule::getAXisWait(const QString &str) {
  lg::AxisInplaceWait *tmp = nullptr;
  YDProjectManage::createAxisInplaceWait(getLogicProcessId(), tmp);
  auto infos = str.split('@');

  auto axname = infos[0];
  auto list = YDProjectManage::getAxisList();
  for (auto a : list) {
    auto name = QString::fromLocal8Bit(a->axis_name);
    if (name == axname) {
      tmp->device_id = a->device_id;
      tmp->axis_index = a->axis_index;
      break;
    }
  }

  tmp->inplace_wait_value = 0;

  if (infos[1] == YDModule::tr("不等待"))
    tmp->inplace_wait_type = 0;
  else if (infos[1] == YDModule::tr("规划运动停止"))
    tmp->inplace_wait_type = 1;
  else if (infos[1] == YDModule::tr("默认误差带"))
    tmp->inplace_wait_type = 2;
  else {
    tmp->inplace_wait_type = 3;
    tmp->inplace_wait_value = infos[2].toDouble();
  }

  return tmp;
}

QString YDModule::getAxisWaitStr(yd::lg::AxisInplaceWait *axis) const {
  QString tmp;
  auto list = YDProjectManage::getAxisList();
  for (auto a : list) {
    auto name = QString::fromLocal8Bit(a->axis_name);
    if ((a->device_id == axis->device_id) &&
        (a->axis_index == axis->axis_index)) {
      tmp += name + '@';
      break;
    }
  }

  switch (axis->inplace_wait_type) {
    case 0:
      tmp += QString("%1@").arg(YDModule::tr("不等待"));
      tmp += "";
      break;
    case 1:
      tmp += QString("%1@").arg(YDModule::tr("规划运动停止"));
      tmp += "";
      break;
    case 2:
      tmp += QString("%1@").arg(YDModule::tr("默认误差带"));
      tmp += "";
      break;
    case 3:
      tmp += QString("%1@").arg(YDModule::tr("自定义误差带"));
      tmp += QString::number(axis->inplace_wait_value);
      break;
    default:
      break;
  }
  return tmp;
}

//#####get#####
// base
bool YDModule::getsyncMode() const { return m_logicProcess->sync_mode; }

// motion
QString YDModule::getAxisName() const { return m_axisName; }

QString YDModule::getPosVarName() const { return m_posVarName; }

int YDModule::getSpeedWay() const { return m_speedWay; }

QString YDModule::getSpeedStr() const { return m_speedStr; }

QString YDModule::getSpeedPosStr() const { return m_speedPosStr; }

int YDModule::getStopWay() const { return m_stopWay; }

QString YDModule::getSafeVarName() const { return m_safeVarName; }

double YDModule::getInplaceWaitValue() const { return m_inplaceWaitValue; }

int YDModule::getWaitConditionWay() const {
  return m_inplaceWaitModule->logic_operator - LOGIC_OPERATOR_AND;
}

QStringList YDModule::getAxisWaitList() const {
  QStringList axisList;
  auto list = m_inplaceWaitModule->listAxisInplaceWaits;
  for (auto v : list) axisList << getAxisWaitStr(v);
  return axisList;
}

QStringList YDModule::getAxisList() const {
  QStringList list;
  auto str = getSpeedPosStr();
  auto id = YDProjectManage::getVirtualVarId(str);
  auto ids = getAxisIdList();
  QSet<uint64> idset;
  for (auto id : ids) idset.insert(id);
  if (0 != id) {
    vr::SystemVariable *var = nullptr;
    auto vars = YDProjectManage::getAllVirtualVariables();
    for (auto v : vars) {
      if (v->variable_id == id) {
        var = v;
        break;
      }
    }
    if (var) {
      yd::COORDS m_coords;
      memset(&m_coords, 0, sizeof(yd::COORDS));
      yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &m_coords);
      QString axstr;
      for (int i = 0; i < m_coords.ucNumber; ++i) {
        uint64 did = m_coords.arrCoords[i].uiDeviceId;
        uint32 aid = m_coords.arrCoords[i].usAxis;
        did = did << 32;
        did = did | aid;
        if (idset.contains(did))
          axstr += QString("%1@").arg(YDModule::tr("是"));
        else
          axstr += QString("%1@").arg(YDModule::tr("否"));

        axstr +=
            QString("%1,").arg(YDHelper::CoorData2QStr(m_coords.arrCoords[i]));
      }
      list = axstr.split(',');
    }
  }
  return list;
}

std::vector<uint64> YDModule::getAxisIdList() const {
  return m_mulMotionModule->enabled_axisids;
}

void YDModule::setAxisIdList(const QList<uint64> &list) {
  m_mulMotionModule->enabled_axisids.clear();
  for (auto id : list) m_mulMotionModule->enabled_axisids.push_back(id);
}

// io
QString YDModule::getDOName() const { return m_doName; }

QString YDModule::getAOName() const { return m_aoName; }

int YDModule::getDOState() const { return m_doState; }

QString YDModule::getIOName() const { return m_ioName; }
QString YDModule::getCylinder() const { return m_cylinderName; }

QString YDModule::getCylinderDir() const { return m_cylinderDir; }

// condition
int YDModule::getConditionWay() const {
  return m_ifElseProcess->pConditionModule->logic_operator - LOGIC_OPERATOR_AND;
}

int YDModule::getIfConditionWay() const {
  return m_ifProcess->pConditionModule->logic_operator - LOGIC_OPERATOR_AND;
}

int YDModule::getLoopConditionWay() const {
  return m_conditionProcess->pConditionModule->logic_operator -
         LOGIC_OPERATOR_AND;
}

QStringList YDModule::getConditionList() const {
  auto list = m_ifElseProcess->pConditionModule->listConditions;
  QStringList strList;
  if (list.size() == 0) return strList;

  for (auto c : list) {
    QString str;
    auto name = YDProjectManage::getVarName(c->parameter_id);
    if (name.isEmpty()) continue;
    str += QString("%1@").arg(name);
    str += QString("%1@").arg(YDHelper::getCompareStr(c->compare_operator));
    str += QString("%1@").arg(QString::fromStdString(c->judge_value));
    str += QString("%1@").arg(QString::fromStdString(c->allow_error));
    bool b = c->not_operator;
    str += QString("%1@").arg(b ? YDModule::tr("是") : YDModule::tr("否"));
    strList << str;
  }
  return strList;
}

QStringList YDModule::getIfConditionList() const {
  auto list = m_ifProcess->pConditionModule->listConditions;
  QStringList strList;
  if (list.size() == 0) return strList;

  for (auto c : list) {
    QString str;
    auto name = YDProjectManage::getVarName(c->parameter_id);
    if (name.isEmpty()) continue;
    str += QString("%1@").arg(name);
    str += QString("%1@").arg(YDHelper::getCompareStr(c->compare_operator));
    str += QString("%1@").arg(QString::fromStdString(c->judge_value));
    str += QString("%1@").arg(QString::fromStdString(c->allow_error));
    bool b = c->not_operator;
    str += QString("%1@").arg(b ? YDModule::tr("是") : YDModule::tr("否"));
    strList << str;
  }
  return strList;
}

QStringList YDModule::getLoopConditionList() const {
  auto list = m_conditionProcess->pConditionModule->listConditions;
  QStringList strList;
  if (list.size() == 0) return strList;

  for (auto c : list) {
    QString str;
    auto name = YDProjectManage::getVarName(c->parameter_id);
    if (name.isEmpty()) continue;
    str += QString("%1@").arg(name);
    str += QString("%1@").arg(YDHelper::getCompareStr(c->compare_operator));
    str += QString("%1@").arg(QString::fromStdString(c->judge_value));
    str += QString("%1@").arg(QString::fromStdString(c->allow_error));
    bool b = c->not_operator;
    str += QString("%1@").arg(b ? YDModule::tr("是") : YDModule::tr("否"));
    strList << str;
  }
  return strList;
}

uint32 YDModule::getDelayTime() const { return m_delayModule->delay_time; }

uint32 YDModule::getLoopTimes() const { return m_loopTimes; }

int YDModule::getInplaceWait() const { return m_inplaceWait; }

QString YDModule::getCallTask() const { return m_callTask; }

int YDModule::getAlarmLevel() const { return m_alarmLevel; }

QString YDModule::getAlarmContent() const {
  return QString::fromLocal8Bit(m_messageModule->content.c_str());
}

QStringList YDModule::getAlarmActions() const { return m_alarmActions; }

int YDModule::getDelayType() const { return m_delayType; }

QString YDModule::getDelayValue() const { return m_delayValue; }

int YDModule::getWaitTime() const { return m_waitTime; }

int YDModule::getCodeType() const { return m_codeType; }

QStringList YDModule::getCodeList() const { return m_codeList; }

int YDModule::getDataCashSize() const { return m_dataCashSize; }

QString YDModule::getSelectModule() const { return m_moduleName; }

//#####get#####
// base
void YDModule::setSyncMode(bool b) { m_logicProcess->sync_mode = b; }

// motion
void YDModule::setAxisName(const QString &str) { m_axisName = str; }

void YDModule::setPosVarName(const QString &str) { m_posVarName = str; }

void YDModule::setSpeedWay(int index) { m_speedWay = index; }

void YDModule::setSpeedStr(const QString &str) { m_speedStr = str; }

void YDModule::setSpeedPosStr(const QString &str) { m_speedPosStr = str; }

void YDModule::setStopWay(int index) { m_stopWay = index; }

void YDModule::setInplaceWait(int index) { m_inplaceWait = index; }

void YDModule::setSafeVarName(const QString &str) { m_safeVarName = str; }

void YDModule::setInplaceWaitValue(double value) { m_inplaceWaitValue = value; }

void YDModule::setWaitConditionWay(int index) {
  m_inplaceWaitModule->logic_operator = index + LOGIC_OPERATOR_AND;
}

void YDModule::setAxisWaitList(const QStringList &list) {
  for (auto a : m_inplaceWaitModule->listAxisInplaceWaits)
    YDProjectManage::deleteAxisInplaceWait(getLogicProcessId(), a->inplace_id);
  m_inplaceWaitModule->listAxisInplaceWaits.clear();

  for (const auto a : list) getAXisWait(a);
}

void YDModule::setAxisList(const QStringList &list) {
  auto str = getSpeedPosStr();
  auto id = YDProjectManage::getVirtualVarId(str);
  auto ids = getAxisIdList();
  QSet<uint64> idset;
  for (auto id : ids) idset.insert(id);
  if (0 != id) {
    vr::SystemVariable *var = nullptr;
    auto vars = YDProjectManage::getAllVirtualVariables();
    for (auto v : vars) {
      if (v->variable_id == id) {
        var = v;
        break;
      }
    }
    if (var) {
      yd::COORDS m_coords;
      memset(&m_coords, 0, sizeof(yd::COORDS));
      yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &m_coords);
      QList<uint64> ulist;

      for (int i = 0; i < list.size(); ++i) {
        auto cd = list[i].split('@').at(0);
        if (cd == YDModule::tr("是")) {
          uint64 did = m_coords.arrCoords[i].uiDeviceId;
          uint32 aid = m_coords.arrCoords[i].usAxis;
          did = did << 32;
          did = did | aid;
          ulist.push_back(did);
        }
      }
      setAxisIdList(ulist);
    }
  }
}

// io
void YDModule::setDOName(const QString &name) { m_doName = name; }

void YDModule::setAOName(const QString &name) { m_aoName = name; }

void YDModule::setDOState(int index) { m_doState = index; }

void YDModule::setIOName(const QString &name) { m_ioName = name; }

void YDModule::setCylinder(const QString &name) { m_cylinderName = name; }

void YDModule::setCylinderDir(const QString &str) { m_cylinderDir = str; }

// condition
void YDModule::setConditionWay(int index) {
  m_ifElseProcess->pConditionModule->logic_operator =
      index + LOGIC_OPERATOR_AND;
}

void YDModule::setIfConditionWay(int index) {
  m_ifProcess->pConditionModule->logic_operator = index + LOGIC_OPERATOR_AND;
}

void YDModule::setLoopConditionWay(int index) {
  m_conditionProcess->pConditionModule->logic_operator =
      index + LOGIC_OPERATOR_AND;
}

void YDModule::setConditionList(const QStringList &list) {
  m_ifElseProcess->pConditionModule->listConditions.clear();
  int index = 0;
  for (auto s : list) {
    yd::lg::Condition *condition = nullptr;
    YDProjectManage::createCondition(getLogicProcessId(), condition);

    QStringList strlist = s.split("@");
    uint64 id = YDProjectManage::getVarId(strlist[0]);
    if (0 == id) continue;

    condition->parameter_id = id;
    condition->compare_operator = YDHelper::getCompareIndex(strlist[1]);
    condition->judge_value = QSTRTSTR(strlist[2]);
    condition->allow_error = strlist[3].toStdString();
    bool b = strlist[4] == YDModule::tr("是") ? true : false;
    condition->not_operator = b;
    condition->judge_order = ++index;
  }
}

void YDModule::setIfConditionList(const QStringList &list) {
  m_ifProcess->pConditionModule->listConditions.clear();
  int index = 0;
  for (auto s : list) {
    yd::lg::Condition *condition = nullptr;
    YDProjectManage::createCondition(getLogicProcessId(), condition);

    QStringList strlist = s.split("@");
    uint64 id = YDProjectManage::getVarId(strlist[0]);
    if (0 == id) continue;

    condition->parameter_id = id;
    condition->compare_operator = YDHelper::getCompareIndex(strlist[1]);
    condition->judge_value = QSTRTSTR(strlist[2]);
    condition->allow_error = strlist[3].toStdString();
    bool b = strlist[4] == YDModule::tr("是") ? true : false;
    condition->not_operator = b;
    condition->judge_order = ++index;
  }
}

void YDModule::setLoopConditionList(const QStringList &list) {
  for (auto c : m_conditionProcess->pConditionModule->listConditions)
    YDProjectManage::deleteCondition(getLogicProcessId(), c->condition_id);
  m_conditionProcess->pConditionModule->listConditions.clear();

  int index = 0;
  for (auto s : list) {
    yd::lg::Condition *condition = nullptr;
    YDProjectManage::createCondition(getLogicProcessId(), condition);

    QStringList strlist = s.split("@");
    uint64 id = YDProjectManage::getVarId(strlist[0]);
    if (0 == id) continue;

    condition->parameter_id = id;
    condition->compare_operator = YDHelper::getCompareIndex(strlist[1]);
    condition->judge_value = QSTRTSTR(strlist[2]);
    condition->allow_error = strlist[3].toStdString();
    bool b = strlist[4] == YDModule::tr("是") ? true : false;
    condition->not_operator = b;
    condition->judge_order = ++index;
  }
}

void YDModule::setDelayTime(uint32 time) { m_delayModule->delay_time = time; }

void YDModule::setLoopTimes(uint32 times) { m_loopTimes = times; }

void YDModule::setTaskCall(const QString &str) { m_callTask = str; }

void YDModule::setAlarmLevel(int index) { m_alarmLevel = index; }

void YDModule::setAlarmContent(const QString &str) {
  m_messageModule->content = QSTRTSTR(str);
}

void YDModule::setAlarmActions(const QStringList &list) {
  m_alarmActions.clear();
  m_alarmActions = list;
}

void YDModule::setDelayType(int type) { m_delayType = type; }

void YDModule::setDelayValue(const QString &value) { m_delayValue = value; }

void YDModule::setWaitTime(int time) { m_waitTime = time; }

void YDModule::setCodeType(int type) { m_codeType = type; }

void YDModule::setCodeList(const QStringList &code) { m_codeList = code; }

void YDModule::setDataCashSize(int size) { m_dataCashSize = size; }

void YDModule::setSelectModule(const QString &name) { m_moduleName = name; }
