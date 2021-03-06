#ifndef YDPROJECTMANAGE_H
#define YDPROJECTMANAGE_H

#include <QMap>
#include <QString>

#include "CompilerImpl.h"
#include "ProjectManagerImp.h"
#include "yd_compiler.h"

using namespace yd;

class YDModule;
class YDTask;
class YDVariable;
class YDVariableGroupModel;
class YDVariable;
class YDSafeVariableGroupModel;
class YDSafeVariable;
class QWidget;

class YDProjectManage {
 public:
  YDProjectManage();

  ~YDProjectManage();

 public:
  void initCode();

  static QString getVbCode();

  static QString getVcCode();

  static QString getBPVbCode();

  static QString getBPVCCode();

 public:
  static bool init();

  static bool CreateProject(const std::string& strProjectName);

  static bool openProject(const std::string& strProjectName);

  static void setProjectPath(const QString& path);

  static void saveModuleData(uint32 id, const QList<YDModule*>& modules);

  static void saveProject();

  static void setVariableGruopModle(YDVariableGroupModel* model);

  static void updateVariableGroupModel();

  static void deleteTaskProcess(uint32 taskId, uint32 processId);

  static void GetTaskNames(std::map<uint32, std::string>& name);

  static QString getTaskName(uint32 taskId);

  static bool deleteMotionDevice(uint32 uiDeviceId);

  static QString getFileName();

  static void getTaskXmlizedProcesses(uint32 id, std::string& xmlstr);

  static void getMotionAxisMoveSetups(
      std::vector<yd::dev::MCAxisMoveSetup*>& list);

  static void createCondition(uint32 id, lg::Condition*& pcon);

  static void deleteCondition(uint32 id, uint32 cid);

  static void createSafeVariableCondition(uint64 id, lg::Condition*& pc);

  static void deleteSafeVariableCondition(uint64 id, uint32 cid);

  static void createAxisInplaceWait(uint32 id, lg::AxisInplaceWait*& pip);

  static void deleteAxisInplaceWait(uint32 id, uint32 iid);

  static void getProcess(uint32 id, lg::LogicProcess*& process);

  static std::map<uint32, std::string>& getProcessNames();

 public:
  static QString getVarName(uint64 id);

  static uint64 getVarId(const QString& name);

  static QString getVirtualVarName(uint64 id);

  static uint64 getVirtualVarId(const QString& name);

  static QString getSafeVirtualVarName(uint64 id);

  static uint64 getSafeVirtualVarId(const QString& name);

  static YDModule* getModule(uint8 type);

  static YDTask* getYDTaskRoot();

  static YDVariable* getVarRoot();

  static YDSafeVariable* getSafeVarRoot();

  static void saveTabWParent();

  static void restoreTabwParent();

  static void setTabWNull();

  static std::vector<yd::vr::SafeVariable*>& getGroupedSafeVariables(uint16 id);

  static std::vector<yd::dev::DeviceType*>& getPredefinedDeviceTypes();

  static bool createMotionDevice(const std::string& name, dev::DeviceType* type,
                                 dev::MCDevice*& dev);

  static bool createCylinder(const std::string& name, dev::DeviceType* type,
                             dev::Cylinder*& dev);

  static bool deleteCylinder(uint32 uiDeviceId);
  static bool deleteCylinder(const std::string& strDeviceName);

  static bool updateMCDeviceVariables(dev::MCDevice*& pMCDevice);

  static bool updateCylinderVariables(dev::Cylinder*& cly);

  static bool createVariableMainGroup(yd::vr::VariableGroup*& gp);

  static bool createVariableSubGroup(uint16 id, vr::VariableGroup*& gp);

  static bool deleteVariableGroup(uint16 id);

  static void getGlobalGroupSysVar(uint16 id,
                                   std::vector<yd::vr::SystemVariable*>& list);

  static void getGroupedSafeVariables(uint16 id,
                                      std::vector<yd::vr::SafeVariable*>& list);

 public:
  static std::vector<yd::dev::MCAxisInfo*>& getAxisList();

  static std::vector<yd::vr::SystemVariable*>& getAllVariables();

  static std::vector<yd::vr::SystemVariable*>& getAllVariables(uint16 id);

  static std::vector<yd::vr::SystemVariable*>& getAllVirtualVariables();

  static std::vector<yd::vr::SafeVariable*>& getAllSafeVariables();

  static std::vector<yd::dev::MCDevice*>& getMotionDevices();

  static std::vector<yd::dev::Cylinder*>& getCylinders();

  static std::vector<yd::dev::IOInfo*>& getDIInfos();

  static std::vector<yd::dev::IOInfo*>& getDOInfos();

  static std::vector<yd::dev::IOInfo*>& getAIInfos();

  static std::vector<yd::dev::IOInfo*>& getAOInfos();

 public:
  static int32 updateVariableGroupName(uint16 gid, const std::string& gname);

  static int32 UpdateVariableName(uint64 vid, const std::string& vname);

  static int32 updateLogicTaskName(uint32 tid, const std::string& tname);

  static int32 updateLogicProcessName(uint32 tid, uint32 pid,
                                      const std::string& pname);

  static int32 updateMotionDeviceName(uint32 did, const std::string& dname);

  static int32 updateMotionAxisName(uint32 did, uint16 aindex,
                                    const std::string& aname);

  static int32 updateCylinderName(uint32 did, const std::string& cyname);

  static int32 updateDIName(uint32 did, uint8 dtype, uint16 diindex,
                            const std::string& dname);

  static int32 updateDOName(uint32 did, uint8 dtype, uint16 doindex,
                            const std::string& dname);

  static int32 updateAIName(uint32 did, uint8 dtype, uint16 aiindex,
                            const std::string& aname);

  static int32 updateAOName(uint32 did, uint8 dtype, uint16 aoindex,
                            const std::string& aname);

  /**********************************************************/

  static void createTask(yd::lg::LogicTask*& task);

  static void deleteTask(uint32 taskId);

  static void createSubTask(uint32 taskId, lg::LogicSubTask*& subtask);

  static void deleteSubTask(uint32 taskId, uint32 subtaskId);

  static void createTaskProcess(uint32 id, lg::LogicProcess*& lp);

  static void getTaskProcesses(uint32 taskId,
                               std::vector<yd::lg::LogicProcess*>& list);

  static void getSubTaskProcesses(uint32 subTaskId,
                                  std::vector<yd::lg::LogicProcess*>& list);

  static bool getProcesses(uint32 uiParentId,
                           std::vector<uint32>& listProcessIds,
                           std::vector<yd::lg::LogicProcess*>& listProcesses);

  // Motion
  static void attachAbsoluteMoveModule(uint32 id,
                                       lg::AbsoluteMoveModule*& module);

  static void attachRelativeMoveModule(uint32 id,
                                       lg::RelativeMoveModule*& module);

  static void attachJogMoveModule(uint32 id, lg::JogMoveModule*& module);

  static void attachMultiAxisesMoveModule(uint32 id,
                                          lg::MultAxisesMoveModule*& module);

  static void attachHomeMoveModule(uint32 id, lg::HomeMoveModule*& module);

  static void attachStopMoveModule(uint32 id, lg::StopMoveModule*& module);

  static void attachInplaceWaitModule(uint32 id,
                                      lg::InplaceWaitModule*& module);

  // IO
  static void attachDOControlModule(uint32 id, lg::DOControlModule*& module);

  static void attachAOControlModule(uint32 id, lg::AOControlModule*& module);

  static void attachCylinderModule(uint32 id, lg::CylinderModule*& module);

  // condition
  static void getIfElseProcess(uint32 processId, lg::IfElseProcess*& process);

  static void getIfProcess(uint32 processId, lg::IfProcess*& process);

  static void attachCounterLoopModule(uint32 id,
                                      lg::CounterLoopModule*& module);

  static void getConditionLoopProcess(uint32 id,
                                      lg::ConditionLoopProcess*& process);

  static void attachBreakModule(uint32 id, lg::BreakModule*& module);

  static void attachDelayModule(uint32 id, lg::DelayModule*& module);

  // other
  static void attachTaskCallerModule(uint32 id, lg::TaskCallerModule*& module);

  static void attachMessageModule(uint32 id, lg::MessageModule*& module);

  static void attachTaskStateWaitModule(uint32 id,
                                        lg::TaskStateWaitModule*& module);

  static void attachProgramModule(uint32 id, lg::ProgramModule*& module);

  static void attachJumpToModule(uint32 id, lg::JumpToModule*& module);

  //########################

  static void createTaskIfElseProcess(uint32 id, lg::IfElseProcess*& process);

  static void createTaskIfProcess(uint32 id, lg::IfProcess*& process);

  static void createTaskConditionLoopProcess(
      uint32 id, lg::ConditionLoopProcess*& process);

  static void createGlobalVar(uint16 usMainGroupId, uint16 usSubGroupId,
                              uint8 ucValueType,
                              vr::SystemVariable*& pVariable);

  static void createSafeVariable(uint16 mainId, uint16 subId,
                                 vr::SafeVariable*& safeVar);

  static void initComplier();

  static void enumFrameworks(uint8 ucTargetCPU,
                             std::vector<std::string>& listFrameworks);

  static std::string getProgrammableProcessCodeFilePath(
      const std::string& strProcessName, uint8 ucCompilerType);

  static void compileProgrammableProcess(const std::string& pname, uint8 ctype,
                                         const std::string& fram, uint8 cpu,
                                         std::string& cinfo);

  static bool isExisting(const std::string& strScriptName);

  static bool getScript(const std::string& sname, adv::ExtendScript*& esc);

  static std::vector<adv::ExtendScript*>& getScripts();

  static int32 createScript(const std::string& strScriptName,
                            adv::ExtendScript*& pExtendScript);

  static int32 updateScript(adv::ExtendScript* pExtendScript);

  static int32 deleteScript(const std::string& strScriptName);

  static std::string getExtendableScriptCodeFilePath(
      const std::string& strScriptName, uint8 ucCompilerType);

  static void compileExtendableScript(const std::string& sname, uint8 ctype,
                                      const std::string& fram, uint8 cpu,
                                      std::string& sinfo);

  static bool enumuerateProjects(std::vector<std::string>& listProjectNames);

  // ??????????????????
  static bool isProjectExisting(const std::string& strProjectName);

  // ??????????????????
  static bool isProjectOpened();

  static bool isProjectOpened(const std::string& strProjectName);

  // ????????????
  static bool saveProjectAs(const std::string& strProjectNewName);

  static bool saveProjectAs(const std::string& strProjectOldName,
                            const std::string& strProjectNewName);

  // ????????????
  static bool closeProject();

  // ???????????????????????????
  static QString getCurrentProject();

  // ???????????????
  static bool renameProject(const std::string& strProjectNewName);

  static bool renameProject(const std::string& strProjectOldName,
                            const std::string& strProjectNewName);

  // ????????????
  static bool deleteProject();

  static bool deleteProject(const std::string& strProjectName);

  // ??????????????????
  static bool enumuerateRecipes(std::vector<std::string>& listRecipeNames);

  // ??????????????????
  static bool isRecipeExisting(const std::string& strRecipeName);

  // ??????????????????
  static bool isRecipeOpened();

  static bool isRecipeOpened(const std::string& strRecipeName);

  // ????????????
  static bool createRecipe(const std::string& strRecipeName);

  // ????????????
  static bool openRecipe(const std::string& strRecipeName);

  // ????????????
  static bool saveRecipe();

  // ????????????
  static bool saveRecipeAs(const std::string& strRecipeNewName);

  static bool saveRecipeAs(const std::string& strRecipeOldName,
                           const std::string& strRecipeNewName);

  // ???????????????????????????
  static QString getCurrentRecipe();

  // ???????????????
  static bool renameRecipe(const std::string& strRecipeNewName);

  static bool renameRecipe(const std::string& strRecipeOldName,
                           const std::string& strRecipeNewName);

  // ????????????
  static bool deleteRecipe();

  static bool deleteRecipe(const std::string& strRecipeName);

  // ????????????
  static bool IsChanged();

  // ????????????
  static const char* GetErrorMsg();

  // ??????
  static void Clear();

  // ??????????????????
  static bool SetDefaultRecipe(const std::string& strRecipeName);

  // ??????????????????
  static const char* GetDefaultRecipe();

  // ????????????????????????
  static bool SetHomeMoveScriptType(uint8 ucScriptType);

  // ????????????????????????
  static uint8 GetHomeMoveScriptType();

  // ??????????????????????????????
  static bool IsOnlineDebugOpened();

  // ??????/????????????????????????
  static bool OpenOnlineDebug(bool bOpen);

  // ????????????????????????
  static bool GetDataGateway(std::string& strAddress, uint16& usPort,
                             uint32& uiTimeout);

  // ????????????????????????
  static bool SetDataGateway(const std::string& strAddress, uint16 usPort,
                             uint32 uiTimeout);

  // ???????????????????????????
  static bool GetDataReceivers(
      std::vector<prj::DataServer*>& listDataReceivers);

  // ???????????????????????????
  static bool AddDataReceiver(const std::string& strAddress, uint16 usPort,
                              uint32 uiTimeout);

  //+++++++++++++++++++++++++++++++++++

  // ??????????????????
  static bool IsGlobalVarExisting(uint64 ullGlobalVarId);
  static bool IsGlobalVarExisting(const std::string& strGlobalVarName);

  // ????????????
  static bool CreateGlobalVar(uint16 usMainGroupId, uint16 usSubGroupId,
                              uint8 ucValueType,
                              vr::SystemVariable*& pGlobalVar);
  static bool CreateGlobalVars(
      uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType,
      uint8 ucNumber, std::vector<yd::vr::SystemVariable*>& listGlobalVars);

  // ????????????
  static bool GetGlobalVar(uint64 ullGlobalVarId,
                           vr::SystemVariable*& pGlobalVar);
  static bool GetAllGlobalVars(
      std::vector<yd::vr::SystemVariable*>& listGlobalVars);
  static std::vector<yd::vr::SystemVariable*>& GetGroupedGlobalVars(
      uint16 usMainGroupId);
  static bool GetGroupedGlobalVars(
      uint16 usGroupId, std::vector<yd::vr::SystemVariable*>& listGlobalVars);

  // ??????????????????
  static bool DeleteGlobalVar(uint64 ullGlobalVarId);

  // ?????????????????????-1--????????????/0--????????????/1--????????????
  static int32 UpdateGlobalVarName(uint64 ullGlobalVarIdToUpdate,
                                   const std::string& strNewGlobalVarName);

  // ??????????????????
  static bool GroupGlobalVar(uint64 ullGlobalVarId, uint16 usMainGroupId,
                             uint16 usSubGroupId);
  static bool GroupGlobalVars(std::vector<uint64>& listGlobalVarIds,
                              uint16 usMainGroupId, uint16 usSubGroupId);

  // ????????????????????????
  static bool DeleteGroupGlobalVars(uint16 usGroupId);

  // ???????????????
  static bool UpdateGlobalVarValue(uint64 ullGlobalVarId,
                                   const std::string& strGlobalVarValue);

  //+++++++++++++++++++++++++++++++++++

  // ??????????????????
  static bool IsReciVarExisting(uint64 ullReciVarId);
  static bool IsReciVarExisting(const std::string& strReciVarName);

  // ????????????
  static bool CreateReciVar(uint16 usMainGroupId, uint16 usSubGroupId,
                            uint8 ucValueType, vr::SystemVariable*& pReciVar);
  static bool CreateReciVars(
      uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType,
      uint8 ucNumber, std::vector<yd::vr::SystemVariable*>& listReciVars);

  // ????????????
  static bool GetReciVar(uint64 ullReciVarId, vr::SystemVariable*& pReciVar);
  static bool GetAllReciVars(
      std::vector<yd::vr::SystemVariable*>& listReciVars);
  static std::vector<yd::vr::SystemVariable*>& GetGroupedReciVars(
      uint16 usMainGroupId);
  static bool GetGroupedReciVars(
      uint16 usGroupId, std::vector<yd::vr::SystemVariable*>& listReciVars);

  // ??????????????????
  static bool DeleteReciVar(uint64 ullReciVarId);

  // ?????????????????????-1--????????????/0--????????????/1--????????????
  static int32 UpdateReciVarName(uint64 ullReciVarIdToUpdate,
                                 const std::string& strNewReciVarName);

  // ??????????????????
  static bool GroupReciVar(uint64 ullReciVarId, uint16 usMainGroupId,
                           uint16 usSubGroupId);
  static bool GroupReciVars(std::vector<uint64>& listReciVarIds,
                            uint16 usMainGroupId, uint16 usSubGroupId);

  // ????????????????????????
  static bool DeleteGroupReciVars(uint16 usGroupId);

  // ???????????????
  static bool UpdateReciVarValue(uint64 ullReciVarId,
                                 const std::string& strReciVarValue);

  //+++++++++++++++++++++++++++++++++++

  // ??????????????????
  static bool IsTempVarExisting(uint64 ullTempVarId);
  static bool IsTempVarExisting(const std::string& strTempVarName);

  // ????????????
  static bool CreateTempVar(uint16 usMainGroupId, uint16 usSubGroupId,
                            uint8 ucValueType, vr::SystemVariable*& pTempVar);
  static bool CreateTempVars(
      uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType,
      uint8 ucNumber, std::vector<yd::vr::SystemVariable*>& listTempVars);

  // ????????????
  static bool GetTempVar(uint64 ullTempVarId, vr::SystemVariable*& pTempVar);

  static bool GetAllTempVars(
      std::vector<yd::vr::SystemVariable*>& listTempVars);

  static std::vector<yd::vr::SystemVariable*>& GetGroupedTempVars(
      uint16 usMainGroupId);

  static bool GetGroupedTempVars(
      uint16 usGroupId, std::vector<yd::vr::SystemVariable*>& listTempVars);

  // ??????????????????
  static bool DeleteTempVar(uint64 ullTempVarId);

  // ?????????????????????-1--????????????/0--????????????/1--????????????
  static int32 UpdateTempVarName(uint64 ullTempVarIdToUpdate,
                                 const std::string& strNewTempVarName);

  // ??????????????????
  static bool GroupTempVar(uint64 ullTempVarId, uint16 usMainGroupId,
                           uint16 usSubGroupId);
  static bool GroupTempVars(std::vector<uint64>& listTempVarIds,
                            uint16 usMainGroupId, uint16 usSubGroupId);

  // ????????????????????????
  static bool DeleteGroupTempVars(uint16 usGroupId);

  // ???????????????
  static bool UpdateTempVarValue(uint64 ullTempVarId,
                                 const std::string& strTempVarValue);

  //+++++++++++++++++++++++++++++++++++

  static bool DeleteSafeVar(uint64 ullTempVarId);

  //+++++++++++++++++++++++++++++++++++

  // ????????????????????????
  static bool GetDeviceType(uint32 uiDeviceId, dev::DeviceType*& pDeviceType);

  // ????????????????????????
  static const char* GetDeviceName(uint32 uiDeviceId);

  // ????????????????????????id
  static uint32 GetDeviceTypeId(uint32 uiDeviceId);

  // ??????????????????????????????
  static const char* GetDeviceTypeName(uint32 uiDeviceId);

  //+++++++++++++++++++++++++++++++++++

  // ??????????????????
  static bool GetDevice(uint32 uiDeviceId, dev::Device*& pDevice);

  static bool GetDevice(const std::string& strDeviceName,
                        dev::Device*& pDevice);

 private:
  QString m_fileName;
  QString m_projectPath;
  YDTask* m_root;
  YDVariableGroupModel* m_varModel;
  YDVariable* m_varRoot;
  YDSafeVariableGroupModel* m_safeModel;
  YDSafeVariable* m_safeVarRoot;

 private:
  QString m_vbCode;
  QString m_vcCode;
  QString m_bpVBCode;
  QString m_bpVCCode;

 private:
  static YDProjectManage* s_instance;
  std::shared_ptr<CProjectAccessorImpl> m_projectAccessorImpl;
  IProjectManager* m_projectManager;
  usr::IUserManager* m_userManager;
  dev::IDeviceManager* m_deviceManager;
  lg::ILogicManager* m_logicManager;
  vr::IVariableGroupManager* m_varGroupManage;
  adv::IExtendScriptManager* m_scriptManage;
  std::vector<yd::dev::MCAxisInfo*> m_axisInfoList;
  std::vector<yd::vr::SystemVariable*> m_allVars;
  std::vector<yd::vr::SystemVariable*> m_virtualVars;
  std::vector<yd::dev::MCDevice*> m_devices;
  std::vector<yd::vr::SystemVariable*> m_doVars;
  std::vector<yd::vr::SystemVariable*> m_aoVars;
  std::vector<yd::vr::VariableGroup*> m_varFirstGroup;
  std::vector<yd::vr::SystemVariable*> m_showVars;
  std::vector<yd::vr::SafeVariable*> m_showSafeVars;
  std::vector<yd::dev::DeviceType*> m_deviceTypes;
  std::vector<yd::dev::IOInfo*> m_diInfos;
  std::vector<yd::dev::IOInfo*> m_doInfos;
  std::vector<yd::dev::IOInfo*> m_aiInfos;
  std::vector<yd::dev::IOInfo*> m_aoInfos;
  std::vector<yd::dev::Cylinder*> m_cylinders;
  std::vector<yd::vr::SafeVariable*> m_safeVars;
  std::vector<yd::vr::SystemVariable*> m_allVSVars;
  QMap<YDTask*, QWidget*> m_wpMap;
  lg::LogicTask* m_logicTask;
  std::shared_ptr<CCompilerImpl> m_complierImpl;
  yd::ICompiler* m_compiler;
  std::vector<adv::ExtendScript*> m_scriptList;
  std::map<uint32, std::string> m_mapId2Name;
  yd::vr::IGlobalVariableManager* m_globalVarManage;
  yd::vr::IRecipeVariableManager* m_reciperVarManage;
  yd::vr::ILocalVariableManager* m_localVarManage;
  yd::vr::ISafeVariableManager* m_safeVarManage;
  std::vector<yd::vr::SystemVariable*> m_globalVars;
  std::vector<yd::vr::SystemVariable*> m_reciperVars;
  std::vector<yd::vr::SystemVariable*> m_localVars;
  std::vector<yd::vr::SystemVariable*> m_list;
  yd::prj::IWorkingParamManager* m_workParaManage;

  std::vector<yd::vr::SystemVariable*> m_listGloabalVar;
  std::vector<yd::vr::SystemVariable*> m_listReciVar;
  std::vector<yd::vr::SystemVariable*> m_listTempVar;
};

#endif  // YDPROJECTMANAGE_H
