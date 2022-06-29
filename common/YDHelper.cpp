#include "common/YDHelper.h"

#include <QCryptographicHash>
#include <QDateTime>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QListWidget>
#include <QRandomGenerator>
#include <QTextStream>

#include "MainWindow.h"
#include "YDLogger.h"
#include "common/YDGlobal.h"
#include "core/YDProjectManage.h"
#include "modules/YDModules.h"

YDHelper *YDHelper::s_instance = nullptr;

YDHelper::YDHelper()
    : m_pMain(nullptr),
      m_nameIndex{0},
      m_curIndex{0},
      m_debugMode{false},
      m_isStart{false},
      m_isTestStart{false},
      m_timer{new QElapsedTimer},
      m_random{new QRandomGenerator(
          QDateTime::currentDateTime().toSecsSinceEpoch())},
      m_stream{new QTextStream} {
  Q_ASSERT(nullptr == s_instance);
  s_instance = this;
  m_list << YDHelper::tr("布尔型");
  m_list << YDHelper::tr("整型");
  m_list << YDHelper::tr("浮点型");
  m_list << YDHelper::tr("字符串型");
  m_list << YDHelper::tr("运动坐标");

  m_cmpStrs << YDModule::tr("小于") << YDModule::tr("小于等于")
            << YDModule::tr("等于") << YDModule::tr("大于")
            << YDModule::tr("大于等于") << YDModule::tr("不相等");

  m_stream->setEncoding(QStringConverter::Utf8);
}

YDHelper::~YDHelper() {
  if (m_random) delete m_random;
  if (m_stream) delete m_stream;
  Q_ASSERT(this == s_instance);
  s_instance = nullptr;
  delete m_timer;
}

MainWindow *YDHelper::getMainW() {
  Q_ASSERT(nullptr != s_instance->m_pMain);
  return s_instance->m_pMain;
}

YDUserInfo *YDHelper::getUserInfo() {
  Q_ASSERT(nullptr != s_instance->m_pMain);
  return s_instance->m_pUserInfo;
}

YDModule *YDHelper::getModule(int type) {
  YDModule *w = nullptr;
  Module::Type moduleType = static_cast<Module::Type>(type);

  switch (moduleType) {
    case Module::Abs_Motion:
      w = new YDAbsMotion;
      break;
    case Module::Rel_Motion:
      w = new YDRelMotion;
      break;
    case Module::Jog_Motion:
      w = new YDJogMotion;
      break;
    case Module::Mul_Motion:
      w = new YDMulMotion;
      break;
    case Module::BackZ_Motion:
      w = new YDBackZMotion;
      break;
    case Module::Stop_Motion:
      w = new YDStopMotion;
      break;
    case Module::Wait_Motion:
      w = new YDWaitMotion;
      break;
    case Module::Control_DO:
      w = new YDControlDO;
      break;
    case Module::Control_AO:
      w = new YDControlAO;
      break;
    case Module::Cylinder:
      w = new YDCylinder;
      break;
    case Module::If_Condition:
      w = new YDIfCondition;
      break;
    case Module::IfElse_Condition:
      w = new YDIfElseCondition;
      break;
    case Module::Times_Loop:
      w = new YDTimesLoop;
      break;
    case Module::Condition_Loop:
      w = new YDConditionLoop;
      break;
    case Module::Jump_Loop:
      w = new YDJumpLoop;
      break;
    case Module::Delay_Wait:
      w = new YDDelayWait;
      break;
    case Module::SubTask_Call:
      w = new YDSubTaskCall;
      break;
    case Module::Wait_Complete:
      w = new YDWaitComplete;
      break;
    case Module::Alarm_Confirm:
      w = new YDAlarmConfirm;
      break;
    case Module::Programable:
      w = new YDProgramable;
      break;
    case Module::Jump_To_Task:
      w = new YDJumpToTask;
      break;
  }

  return w;
}

YDModulePropModel *YDHelper::getModPropModel() {
  Q_ASSERT(nullptr != s_instance->m_pMain);
  return s_instance->m_pMain->getModPropModel();
}

QStringList YDHelper::getDataTypeList() { return s_instance->m_list; }

QString YDHelper::getDataType(uint8 index) {
  switch (index) {
    case DATA_TYPE_BOOL:
      return s_instance->m_list.at(0);
    case DATA_TYPE_INT8:
    case DATA_TYPE_UINT8:
    case DATA_TYPE_INT16:
    case DATA_TYPE_UINT16:
    case DATA_TYPE_INT32:
    case DATA_TYPE_UINT32:
    case DATA_TYPE_INT64:
    case DATA_TYPE_UINT64:
      return s_instance->m_list.at(1);
    case DATA_TYPE_FLOAT:
    case DATA_TYPE_DOUBLE:
      return s_instance->m_list.at(2);
    case DATA_TYPE_STRING:
      return s_instance->m_list.at(3);
    case DATA_TYPE_AXIS_COORD:
      return s_instance->m_list.at(4);
  }
  return 0;
}

int YDHelper::getDataTypeIndex(const QString &str) {
  auto index = str.toUInt();
  switch (index) {
    case 0:
      return DATA_TYPE_BOOL;
    case 1:
      return DATA_TYPE_INT64;
    case 2:
      return DATA_TYPE_DOUBLE;
    case 3:
      return DATA_TYPE_STRING;
    case 4:
      return DATA_TYPE_AXIS_COORD;
  }
  return 0;
}

std::string YDHelper::qstringToString(const QString &str) {
  return std::string(str.toLocal8Bit().data());
}

uint8 YDHelper::getCompareIndex(const QString &str) {
  if (s_instance->m_cmpStrs[0] == str) return COMPARE_TYPE_LESS_THAN;
  if (s_instance->m_cmpStrs[1] == str) return COMPARE_TYPE_LESS_EQUAL;
  if (s_instance->m_cmpStrs[2] == str) return COMPARE_TYPE_EQUAL_TO;
  if (s_instance->m_cmpStrs[3] == str) return COMPARE_TYPE_GREATER_THAN;
  if (s_instance->m_cmpStrs[4] == str) return COMPARE_TYPE_GREATER_EQUAL;
  if (s_instance->m_cmpStrs[5] == str) return COMPARE_TYPE_NOT_EQUAL_TO;

  return COMPARE_TYPE_LESS_THAN;
}

QString YDHelper::getCompareStr(uint8 index) {
  return s_instance->m_cmpStrs[index - COMPARE_TYPE_LESS_THAN];
}

bool YDHelper::isDebugMode() { return s_instance->m_debugMode; }

bool YDHelper::getTestStart() { return s_instance->m_isTestStart; }

void YDHelper::setMainW(MainWindow *mainW) {
  Q_ASSERT(nullptr != mainW);
  s_instance->m_pMain = mainW;
}

void YDHelper::setUserInfo(YDUserInfo *usrInfo) {
  Q_ASSERT(nullptr != usrInfo);
  s_instance->m_pUserInfo = usrInfo;
}

void YDHelper::setTestStart(bool b) { s_instance->m_isTestStart = b; }

QString YDHelper::getMD5(const QString &str) {
  Q_ASSERT(!str.isEmpty());
  return QCryptographicHash::hash(str.toLatin1(), QCryptographicHash::Md5)
      .toHex();
}

void YDHelper::UpdateTabName(YDTask *task) {
  Q_ASSERT(nullptr != s_instance->m_pMain);
  s_instance->m_pMain->UpdateTabName(task);
}

void YDHelper::updateCoorData(yd::COORD &coor, const QStringList &info) {
  QString axName = info[0];
  auto type = 0;
  auto axlist = YDProjectManage::getAxisList();
  auto motionType = MULTI_AXIS_COORDS_TYPE_ABSOLUTE_MOVE;
  switch (type) {
    case 0:
      motionType = MULTI_AXIS_COORDS_TYPE_ABSOLUTE_MOVE;
      break;
    case 1:
      motionType = MULTI_AXIS_COORDS_TYPE_RELATIVE_MOVE;
      break;
    case 2:
      motionType = MULTI_AXIS_COORDS_TYPE_JOG_MOVE;
      break;
    default:
      break;
  }

  auto targetway = info[2] == YDHelper::tr("数值") ? 0 : 1;
  auto target = info[3];

  auto moveway = info[4] == YDHelper::tr("百分比") ? 0 : 1;
  auto move = info[5];

  for (auto ax : axlist) {
    auto name = STRTQSTR(ax->axis_name);
    if (name == axName) {
      coor.uiDeviceId = ax->device_id;
      coor.usCard = ax->card_index;
      coor.usAxis = ax->axis_index;
      coor.ucType = motionType;
      if (targetway == 0) {
        coor.refTarget.ullReferId = 0;
        coor.refTarget.dblValue = target.toDouble();
      } else {
        coor.refTarget.dblValue = 0;
        coor.refTarget.ullReferId = YDProjectManage::getVirtualVarId(target);
      }

      if (moveway == 0) {
        coor.refVelocity.ullReferId = 0;
        move = move.mid(0, move.size() - 1);
        coor.refVelocity.dblValue = move.toDouble();
      } else {
        coor.refVelocity.dblValue = 0;
        coor.refVelocity.ullReferId = YDProjectManage::getVirtualVarId(move);
      }
    }
  }
}

QString YDHelper::CoorData2QStr(yd::COORD &coor) {
  QString str;
  auto axlist = YDProjectManage::getAxisList();
  for (auto ax : axlist) {
    if (ax->device_id == coor.uiDeviceId && ax->card_index == coor.usCard &&
        ax->axis_index == coor.usAxis) {
      str += QString("%1@").arg(STRTQSTR(ax->axis_name.c_str()));
      switch (coor.ucType) {
        case MULTI_AXIS_COORDS_TYPE_ABSOLUTE_MOVE:
          str += QString("%1@").arg(YDHelper::tr("绝对运动"));
          break;
        case MULTI_AXIS_COORDS_TYPE_RELATIVE_MOVE:
          str += "1@";
          break;
        case MULTI_AXIS_COORDS_TYPE_JOG_MOVE:
          str += "2@";
          break;
      }

      if (coor.refTarget.dblValue == 0) {
        str += QString("%1@").arg(YDHelper::tr("变量"));
        str += QString("%1@").arg(
            YDProjectManage::getVarName(coor.refTarget.ullReferId));
      } else {
        str += QString("%1@").arg(YDHelper::tr("数值"));
        str += QString("%1@").arg(coor.refTarget.dblValue);
      }

      if (coor.refVelocity.ullReferId == 0) {
        str += QString("%1@").arg(YDHelper::tr("百分比"));
        str += QString("%1%").arg(coor.refVelocity.dblValue);
      } else {
        str += QString("%1@").arg(YDHelper::tr("变量"));
        str += QString("%1").arg(
            YDProjectManage::getVarName(coor.refVelocity.ullReferId));
      }

      break;
    }
  }

  return str;
}

void YDHelper::copyData(char a[], const char *b, int size) {
  memset(a, 0, VARIABLE_VALUE_LENGTH);
  for (int i = 0; i < size; ++i) a[i] = b[i];
}

void YDHelper::setDebugMode(bool b) { s_instance->m_debugMode = b; }

void YDHelper::calculateTime() {
  if (!s_instance->m_isStart) {
    s_instance->m_timer->restart();
  } else {
    float time = (double)s_instance->m_timer->nsecsElapsed() / (double)1000000;
    qDebug() << "time= " << time << "ms";
  }
  s_instance->m_isStart = !s_instance->m_isStart;
}

QStringList YDHelper::getAvaliableFram(const std::vector<std::string> &fram) {
  QStringList list;
  for (auto s : fram) {
    int v = s[s.size() - 3] - '0';
    if (v > 3) list.push_back(STRTQSTR(s.c_str()));
  }

  return list;
}

QString YDHelper::genarateName() {
  QString name = YDHelper::tr("自定义脚本");

  char ch = s_instance->m_random->bounded(0, 25) + 'A';
  name += ch;

  ch = s_instance->m_random->bounded(0, 25) + 'a';
  name += ch;

  ch = s_instance->m_random->bounded(0, 25) + 'a';
  name += ch;

  return QString("%1_%2").arg(name).arg(++s_instance->m_nameIndex);
}

QString YDHelper::genarateTail() {
  QString name;

  char ch = s_instance->m_random->bounded(0, 25) + 'A';
  name += ch;

  ch = s_instance->m_random->bounded(0, 25) + 'a';
  name += ch;

  ch = s_instance->m_random->bounded(0, 25) + 'a';
  name += ch;

  ch = s_instance->m_random->bounded(0, 25) + 'a';
  name += ch;

  return QString("%1_%2").arg(name).arg(++s_instance->m_nameIndex);
}

QString YDHelper::readFile(const QString &name) {
  QString data;
  QFile file(name);
  if (file.open(QFile::ReadOnly)) {
    s_instance->m_stream->setDevice(&file);
    data = s_instance->m_stream->readAll();
  }
  file.close();
  return data;
}

void YDHelper::writeFile(const QString &name, const QString &data) {
  QFile file(name);
  if (file.open(QFile::WriteOnly)) {
    s_instance->m_stream->setDevice(&file);
    (*s_instance->m_stream) << data;
  }
  file.close();
}

void YDHelper::resizeModel(QListWidget *list) {
  for (int i = 0; i < list->count(); ++i) {
    auto item = list->item(i);
    YDModuleCast cast;
    cast.i = qvariant_cast<qintptr>(item->data(Qt::UserRole));
    auto ptr = cast.ptr;
    auto w = item->sizeHint().width();
    auto h = ptr->high();
    item->setSizeHint(QSize(w, h));
    switch (ptr->type()) {
      case Module::Times_Loop: {
        ptr->resize();
      } break;
      case Module::If_Condition: {
        ptr->resize();
      } break;
      case Module::IfElse_Condition: {
        ptr->resize();
      } break;
      case Module::Condition_Loop: {
        ptr->resize();
      } break;
      default:
        break;
    }
  }
}

QString YDHelper::moduleLog(const YDModule *module) {
  QString moduleType = "";
  switch (module->type()) {
    case Module::Abs_Motion:
      moduleType = "绝对运动";
      break;
    case Module::Rel_Motion:
      moduleType = "相对运动";
      break;
    case Module::Jog_Motion:
      moduleType = "Jog运动";
      break;
    case Module::Mul_Motion:
      moduleType = "多轴运动";
      break;
    case Module::BackZ_Motion:
      moduleType = "回零运动";
      break;
    case Module::Stop_Motion:
      moduleType = "停止运动";
      break;
    case Module::Wait_Motion:
      moduleType = "到位等待";
      break;
    case Module::Control_DO:
      moduleType = "控制DO输出";
      break;
    case Module::Control_AO:
      moduleType = "控制AO输出";
      break;
    case Module::Cylinder:
      moduleType = "气油缸";
      break;
    case Module::Condition:
      moduleType = "判断条件";
      break;
    case Module::If_Condition:
      moduleType = "If判断条件";
      break;
    case Module::IfElse_Condition:
      moduleType = "If-Else判断条件";
      break;
    case Module::Times_Loop:
      moduleType = "次数循环";
      break;
    case Module::Condition_Loop:
      moduleType = "条件循环";
      break;
    case Module::Jump_Loop:
      moduleType = "跳出循环";
      break;
    case Module::Delay_Wait:
      moduleType = "延时等待";
      break;
    case Module::SubTask_Call:
      moduleType = "任务调用";
      break;
    case Module::Programable:
      moduleType = "可编程控件";
      break;
    case Module::Wait_Complete:
      moduleType = "任务完成等待";
      break;
    case Module::Alarm_Confirm:
      moduleType = "报警确认";
      break;
    case Module::Jump_To_Task:
      moduleType = "跳转控件";
      break;
    default:
      break;
  }

  return QString("%1: %2").arg(moduleType, module->name());
}
