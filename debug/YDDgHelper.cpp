#include "YDDgHelper.h"

#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QtGlobal>

YDDgHelper *YDDgHelper::s_i = nullptr;

YDDgHelper::YDDgHelper()
    : m_pProtocolClientImpl{nullptr}, m_pProtocolClient{nullptr} {
  Q_ASSERT(nullptr == s_i);
  s_i = this;
}

YDDgHelper::~YDDgHelper() {
  if (s_i->m_pProtocolClient) s_i->m_pProtocolClient->Unitialize();
  if (s_i->m_pProtocolClientImpl) s_i->m_pProtocolClientImpl->Uninitialize();
}

bool YDDgHelper::createInstance() {
  if (nullptr == s_i->m_pProtocolClientImpl) {
    s_i->m_pProtocolClientImpl = yd::CProtocolClientImpl::CreateInstance();
    if (nullptr == s_i->m_pProtocolClientImpl) {
      QMessageBox::warning(nullptr, QObject::tr("错误"),
                           QObject::tr("创建网关访问库失败!"));
      return false;
    }
  }
  return true;
}

bool YDDgHelper::isInitialized(const QString &, const QString &strip,
                               uint16 port) {
  auto ipstr = strip.toUtf8().toStdString();
  auto ip = ipstr.data();
  if (!s_i->m_pProtocolClientImpl->IsInitialized()) {
    if (!s_i->m_pProtocolClientImpl->Initialize(
            1, (const char *)"test", "MachineController",
            "404B56D51D24931D9326CD3C7280C944", (const char *)ip, (uint16)port,
            5000)) {
      QMessageBox::warning(nullptr, QObject::tr("错误"),
                           QObject::tr("初始化网关访问库失败！!"));
      return false;
    }
  }
  return true;
}

bool YDDgHelper::getIProtocolClient() {
  if (!s_i->m_pProtocolClientImpl->GetIProtocolClient(s_i->m_pProtocolClient)) {
    QMessageBox::warning(nullptr, QObject::tr("错误"),
                         QObject::tr("获取网关访问库失败！!"));
    return false;
  }

  return true;
}

bool YDDgHelper::connect(uint8 ucMaxRetries) {
  if (!s_i->m_pProtocolClient->Connect(ucMaxRetries)) {
    QMessageBox::warning(nullptr, QObject::tr("错误"),
                         QObject::tr("连接网关失败！!"));
    return false;
  }
  return true;
}

int32 YDDgHelper::getDIStates(uint32 id, std::map<uint64, bool> &map) {
  return s_i->m_pProtocolClient->GetDIStates(id, map);
}

int32 YDDgHelper::sendDOState(uint32 uiDeviceId, uint16 usIndex, uint16 usType,
                              bool bStatus) {
  return s_i->m_pProtocolClient->SendDOControl(uiDeviceId, usIndex, usType,
                                               bStatus);
}

int32 YDDgHelper::getDOStates(uint32 id, std::map<uint64, bool> &map) {
  return s_i->m_pProtocolClient->GetDOStates(id, map);
}

int32 YDDgHelper::getAxisState(uint32 did, uint16 aid,
                               yd::proto::AxisState *axs) {
  return s_i->m_pProtocolClient->GetAxisState(did, aid, axs);
}

int32 YDDgHelper::enableAxis(uint32 did, uint16 aid, bool b) {
  return s_i->m_pProtocolClient->EnableAxis(did, aid, b);
}

int32 YDDgHelper::clearAxisStatus(uint32 did, uint16 aid) {
  return s_i->m_pProtocolClient->ClearAxisStatus(did, aid);
}

int32 YDDgHelper::zeroAxisPosition(uint32 did, uint16 aid) {
  return s_i->m_pProtocolClient->ZeroAxisPosition(did, aid);
}

int32 YDDgHelper::startHomeMove(uint32 did, uint16 aid) {
  return s_i->m_pProtocolClient->StartHomeMove(did, aid);
}

int32 YDDgHelper::setAxisVelocities(uint32 did, uint16 aid,
                                    yd::dev::MCAxisMoveSetup *ams) {
  return s_i->m_pProtocolClient->SetAxisVelocities(did, aid, ams);
}

int32 YDDgHelper::startJogMove(uint32 uid, uint16 aid, bool b,
                               const std::string &v, uint8 dir) {
  return s_i->m_pProtocolClient->StartJogMove(uid, aid, b, v, dir);
}

int32 YDDgHelper::stopAxisMove(uint32 uid, uint16 aid, bool b) {
  return s_i->m_pProtocolClient->StopAxisMove(uid, aid, b);
}

int32 YDDgHelper::startRelativeMove(uint32 uid, uint16 aid, bool b,
                                    const std::string &dv, bool vus,
                                    const std::string &vv, uint8 dir) {
  return s_i->m_pProtocolClient->StartRelativeMove(uid, aid, b, dv, vus, vv,
                                                   dir);
}

int32 YDDgHelper::getCylinderState(uint32 uid,
                                   yd::proto::DirectionState *state1,
                                   yd::proto::DirectionState *state2) {
  return s_i->m_pProtocolClient->GetCylinderState(uid, state1, state2);
}

int32 YDDgHelper::controlCylinder(uint32 uid, uint8 dir) {
  return s_i->m_pProtocolClient->ControlCylinder(uid, dir);
}

int32 YDDgHelper::setSingleVariableValue(uint64 uid, const std::string &str) {
  return s_i->m_pProtocolClient->SetSingleVariableValue(uid, str);
}

int32 YDDgHelper::getGroupedVariableValues(
    uint16 id, yd::proto::MapId2VariableRTValue &value) {
  return s_i->m_pProtocolClient->GetGroupedVariableValues(id, value);
}

int32 YDDgHelper::getLogicControllerStatus(uint8 &state, uint8 &mode) {
  return s_i->m_pProtocolClient->GetLogicControllerStatus(state, mode);
}

int32 YDDgHelper::startLogicController() {
  return s_i->m_pProtocolClient->StartLogicController();
}

int32 YDDgHelper::stopLogicController() {
  return s_i->m_pProtocolClient->StopLogicController();
}

int32 YDDgHelper::suspendLogicController() {
  return s_i->m_pProtocolClient->SuspendLogicController();
}

int32 YDDgHelper::restoreLogicController() {
  return s_i->m_pProtocolClient->RestoreLogicController();
}

int32 YDDgHelper::logicControllerSwitchToManualMode() {
  return s_i->m_pProtocolClient->LogicControllerSwitchToManualMode();
}

int32 YDDgHelper::logicControllerSwitchToAutoMode() {
  return s_i->m_pProtocolClient->LogicControllerSwitchToAutoMode();
}

int32 YDDgHelper::startLogicTaskDebug(uint32 id, const std::string &config) {
  return s_i->m_pProtocolClient->StartLogicTaskDebug(id, config);
}

int32 YDDgHelper::stopLogicTaskDebug(uint32 id) {
  return s_i->m_pProtocolClient->StopLogicTaskDebug(id);
}

int32 YDDgHelper::getTaskState(uint32 id, yd::proto::TaskState *state) {
  return s_i->m_pProtocolClient->GetTaskState(id, state);
}

int32 YDDgHelper::getLogicStates(const std::vector<uint32> &ids,
                                 yd::proto::LogicStates *states) {
  return s_i->m_pProtocolClient->GetLogicStates(ids, states);
}

int32 YDDgHelper::ExecuteHomeMove() {
  return s_i->m_pProtocolClient->ExecuteHomeMove();
}

int32 YDDgHelper::StartMainLogicTask() {
  return s_i->m_pProtocolClient->StartMainLogicTask();
}

int32 YDDgHelper::SuspendMainLogicTask() {
  return s_i->m_pProtocolClient->SuspendMainLogicTask();
}

int32 YDDgHelper::StopMainLogicTask() {
  return s_i->m_pProtocolClient->StopMainLogicTask();
}

int32 YDDgHelper::DownloadProject(const std::string &strDirectory,
                                  const std::string &strProjectName) {
  return s_i->m_pProtocolClient->DownloadProject(strDirectory, strProjectName);
}

int32 YDDgHelper::UploadProject(const std::string &strDirectory,
                                std::string &strProjectName) {
  return s_i->m_pProtocolClient->UploadProject(strDirectory, strProjectName);
}

int32 YDDgHelper::GetLogMessages(uint64 ullBegin, uint64 ullEnd,
                                 std::vector<std::string> &listMessage) {
  return s_i->m_pProtocolClient->GetLogMessages(ullBegin, ullEnd, listMessage);
}
