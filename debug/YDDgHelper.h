#ifndef YDDGHELPER_H
#define YDDGHELPER_H

#include <QString>

#include "ProtocolClientImpl.h"
#include "ProtocolImp.h"

class YDDgHelper {
 public:
  YDDgHelper();
  ~YDDgHelper();

 public:
  static bool createInstance();

  static bool isInitialized(const QString& file, const QString& ip,
                            uint16 port);

  static bool getIProtocolClient();

  static bool connect(uint8 ucMaxRetries);

  static int32 getDIStates(uint32 uiDeviceId,
                           std::map<uint64, bool>& mapId2Status);

  static int32 sendDOState(uint32 uiDeviceId, uint16 usIndex, uint16 usType,
                           bool bStatus);

  static int32 getDOStates(uint32 uiDeviceId,
                           std::map<uint64, bool>& mapId2Status);

  static int32 getAxisState(uint32 uiDeviceId, uint16 usAxis,
                            yd::proto::AxisState* pAxisState);

  static int32 enableAxis(uint32 uiDeviceId, uint16 usAxis, bool bEnable);

  static int32 clearAxisStatus(uint32 uiDeviceId, uint16 usAxis);

  static int32 zeroAxisPosition(uint32 uiDeviceId, uint16 usAxis);

  static int32 startHomeMove(uint32 uiDeviceId, uint16 usAxis);

  static int32 setAxisVelocities(uint32 uiDeviceId, uint16 usAxis,
                                 yd::dev::MCAxisMoveSetup* pMCAxisMoveSetup);

  static int32 startJogMove(uint32 uid, uint16 aid, bool b,
                            const std::string& v, uint8 dir);

  static int32 stopAxisMove(uint32 uid, uint16 aid, bool b);

  static int32 startRelativeMove(uint32 uid, uint16 aid, bool b,
                                 const std::string& dv, bool vus,
                                 const std::string& vv, uint8 dir);

  static int32 getCylinderState(uint32 uid, yd::proto::DirectionState* state1,
                                yd::proto::DirectionState* state2);

  static int32 controlCylinder(uint32 uid, uint8 dir);

  static int32 setSingleVariableValue(uint64 uid, const std::string& v);

  static int32 getGroupedVariableValues(
      uint16 id, yd::proto::MapId2VariableRTValue& value);

  static int32 getLogicControllerStatus(uint8& ucStatus, uint8& ucMode);

  static int32 startLogicController();

  static int32 stopLogicController();

  static int32 suspendLogicController();

  static int32 restoreLogicController();

  static int32 logicControllerSwitchToManualMode();

  static int32 logicControllerSwitchToAutoMode();

  static int32 startLogicTaskDebug(uint32 id, const std::string& config);

  static int32 stopLogicTaskDebug(uint32 id);

  static int32 getTaskState(uint32 id, yd::proto::TaskState* state);

  static int32 getLogicStates(const std::vector<uint32>& ids,
                              yd::proto::LogicStates* states);

  // 启动回原点
  static int32 ExecuteHomeMove();

  // 启动主任务
  static int32 StartMainLogicTask();

  // 暂停主任务
  static int32 SuspendMainLogicTask();

  // 结束主任务
  static int32 StopMainLogicTask();

  // 下载项目配置
  static int32 DownloadProject(const std::string& strDirectory,
                               const std::string& strProjectName);

  // 上传项目配置
  static int32 UploadProject(const std::string& strDirectory,
                             std::string& strProjectName);

  // 获取后台日志信息
  static int32 GetLogMessages(uint64 ullBegin, uint64 ullEnd,
                              std::vector<std::string>& listMessage);

 private:
  static YDDgHelper* s_i;

  yd::CProtocolClientImplPtr m_pProtocolClientImpl;
  yd::proto::IProtocolClient* m_pProtocolClient;
};

#endif  // YDDGHELPER_H
