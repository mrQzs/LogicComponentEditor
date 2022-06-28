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

  static void getProcesses(std::vector<uint32>& ids,
                           std::vector<yd::lg::LogicProcess*>& list);

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

  static int32 updateScript(const std::string& strOldScriptName,
                            adv::ExtendScript* pExtendScript);

  static int32 deleteScript(const std::string& strScriptName);

  static std::string getExtendableScriptCodeFilePath(
      const std::string& strScriptName, uint8 ucCompilerType);

  static void compileExtendableScript(const std::string& sname, uint8 ctype,
                                      const std::string& fram, uint8 cpu,
                                      std::string& sinfo);

  static bool enumuerateProjects(std::vector<std::string>& listProjectNames);

  // 项目是否存在
  static bool isProjectExisting(const std::string& strProjectName);

  // 项目是否打开
  static bool isProjectOpened();

  static bool isProjectOpened(const std::string& strProjectName);

  // 另存项目
  static bool saveProjectAs(const std::string& strProjectNewName);

  static bool saveProjectAs(const std::string& strProjectOldName,
                            const std::string& strProjectNewName);

  // 关闭项目
  static bool closeProject();

  // 获取当前打开的项目
  static QString getCurrentProject();

  // 重命名项目
  static bool renameProject(const std::string& strProjectNewName);

  static bool renameProject(const std::string& strProjectOldName,
                            const std::string& strProjectNewName);

  // 删除项目
  static bool deleteProject();

  static bool deleteProject(const std::string& strProjectName);

  // 枚举配方名称
  static bool enumuerateRecipes(std::vector<std::string>& listRecipeNames);

  // 配方是否存在
  static bool isRecipeExisting(const std::string& strRecipeName);

  // 配方是否打开
  static bool isRecipeOpened();

  static bool isRecipeOpened(const std::string& strRecipeName);

  // 新建配方
  static bool createRecipe(const std::string& strRecipeName);

  // 打开配方
  static bool openRecipe(const std::string& strRecipeName);

  // 保存配方
  static bool saveRecipe();

  // 另存配方
  static bool saveRecipeAs(const std::string& strRecipeNewName);

  static bool saveRecipeAs(const std::string& strRecipeOldName,
                           const std::string& strRecipeNewName);

  // 获取当前打开的项目
  static QString getCurrentRecipe();

  // 重命名配方
  static bool renameRecipe(const std::string& strRecipeNewName);

  static bool renameRecipe(const std::string& strRecipeOldName,
                           const std::string& strRecipeNewName);

  // 删除配方
  static bool deleteRecipe();

  static bool deleteRecipe(const std::string& strRecipeName);

  // 是否变更
  static bool IsChanged();

  // 获取错误
  static const char* GetErrorMsg();

  // 清理
  static void Clear();

  // 设置默认配方
  static bool SetDefaultRecipe(const std::string& strRecipeName);

  // 获取默认配方
  static const char* GetDefaultRecipe();

  // 设置回零脚本类型
  static bool SetHomeMoveScriptType(uint8 ucScriptType);

  // 获取回零脚本类型
  static uint8 GetHomeMoveScriptType();

  // 在线调试功能是否打开
  static bool IsOnlineDebugOpened();

  // 打开/关闭在线调试功能
  static bool OpenOnlineDebug(bool bOpen);

  // 获取数据网关参数
  static bool GetDataGateway(std::string& strAddress, uint16& usPort,
                             uint32& uiTimeout);

  // 设置数据网关参数
  static bool SetDataGateway(const std::string& strAddress, uint16 usPort,
                             uint32 uiTimeout);

  // 获取数据接收器参数
  static bool GetDataReceivers(
      std::vector<prj::DataServer*>& listDataReceivers);

  // 添加数据接收器参数
  static bool AddDataReceiver(const std::string& strAddress, uint16 usPort,
                              uint32 uiTimeout);

  //+++++++++++++++++++++++++++++++++++

  // 变量是否存在
  static bool IsGlobalVarExisting(uint64 ullGlobalVarId);
  static bool IsGlobalVarExisting(const std::string& strGlobalVarName);

  // 创建变量
  static bool CreateGlobalVar(uint16 usMainGroupId, uint16 usSubGroupId,
                              uint8 ucValueType,
                              vr::SystemVariable*& pGlobalVar);
  static bool CreateGlobalVars(
      uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType,
      uint8 ucNumber, std::vector<yd::vr::SystemVariable*>& listGlobalVars);

  // 获取变量
  static bool GetGlobalVar(uint64 ullGlobalVarId,
                           vr::SystemVariable*& pGlobalVar);
  static bool GetAllGlobalVars(
      std::vector<yd::vr::SystemVariable*>& listGlobalVars);
  static std::vector<yd::vr::SystemVariable*>& GetGroupedGlobalVars(
      uint16 usMainGroupId);
  static bool GetGroupedGlobalVars(
      uint16 usGroupId, std::vector<yd::vr::SystemVariable*>& listGlobalVars);

  // 删除指定变量
  static bool DeleteGlobalVar(uint64 ullGlobalVarId);

  // 更新变量名称：-1--更新失败/0--更新成功/1--名称重复
  static int32 UpdateGlobalVarName(uint64 ullGlobalVarIdToUpdate,
                                   const std::string& strNewGlobalVarName);

  // 指定变量分组
  static bool GroupGlobalVar(uint64 ullGlobalVarId, uint16 usMainGroupId,
                             uint16 usSubGroupId);
  static bool GroupGlobalVars(std::vector<uint64>& listGlobalVarIds,
                              uint16 usMainGroupId, uint16 usSubGroupId);

  // 删除指定分组变量
  static bool DeleteGroupGlobalVars(uint16 usGroupId);

  // 更新变量值
  static bool UpdateGlobalVarValue(uint64 ullGlobalVarId,
                                   const std::string& strGlobalVarValue);

  //+++++++++++++++++++++++++++++++++++

  // 变量是否存在
  static bool IsReciVarExisting(uint64 ullReciVarId);
  static bool IsReciVarExisting(const std::string& strReciVarName);

  // 创建变量
  static bool CreateReciVar(uint16 usMainGroupId, uint16 usSubGroupId,
                            uint8 ucValueType, vr::SystemVariable*& pReciVar);
  static bool CreateReciVars(
      uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType,
      uint8 ucNumber, std::vector<yd::vr::SystemVariable*>& listReciVars);

  // 获取变量
  static bool GetReciVar(uint64 ullReciVarId, vr::SystemVariable*& pReciVar);
  static bool GetAllReciVars(
      std::vector<yd::vr::SystemVariable*>& listReciVars);
  static std::vector<yd::vr::SystemVariable*>& GetGroupedReciVars(
      uint16 usMainGroupId);
  static bool GetGroupedReciVars(
      uint16 usGroupId, std::vector<yd::vr::SystemVariable*>& listReciVars);

  // 删除指定变量
  static bool DeleteReciVar(uint64 ullReciVarId);

  // 更新变量名称：-1--更新失败/0--更新成功/1--名称重复
  static int32 UpdateReciVarName(uint64 ullReciVarIdToUpdate,
                                 const std::string& strNewReciVarName);

  // 指定变量分组
  static bool GroupReciVar(uint64 ullReciVarId, uint16 usMainGroupId,
                           uint16 usSubGroupId);
  static bool GroupReciVars(std::vector<uint64>& listReciVarIds,
                            uint16 usMainGroupId, uint16 usSubGroupId);

  // 删除指定分组变量
  static bool DeleteGroupReciVars(uint16 usGroupId);

  // 更新变量值
  static bool UpdateReciVarValue(uint64 ullReciVarId,
                                 const std::string& strReciVarValue);

  //+++++++++++++++++++++++++++++++++++

  // 变量是否存在
  static bool IsTempVarExisting(uint64 ullTempVarId);
  static bool IsTempVarExisting(const std::string& strTempVarName);

  // 创建变量
  static bool CreateTempVar(uint16 usMainGroupId, uint16 usSubGroupId,
                            uint8 ucValueType, vr::SystemVariable*& pTempVar);
  static bool CreateTempVars(
      uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType,
      uint8 ucNumber, std::vector<yd::vr::SystemVariable*>& listTempVars);

  // 获取变量
  static bool GetTempVar(uint64 ullTempVarId, vr::SystemVariable*& pTempVar);

  static bool GetAllTempVars(
      std::vector<yd::vr::SystemVariable*>& listTempVars);

  static std::vector<yd::vr::SystemVariable*>& GetGroupedTempVars(
      uint16 usMainGroupId);

  static bool GetGroupedTempVars(
      uint16 usGroupId, std::vector<yd::vr::SystemVariable*>& listTempVars);

  // 删除指定变量
  static bool DeleteTempVar(uint64 ullTempVarId);

  // 更新变量名称：-1--更新失败/0--更新成功/1--名称重复
  static int32 UpdateTempVarName(uint64 ullTempVarIdToUpdate,
                                 const std::string& strNewTempVarName);

  // 指定变量分组
  static bool GroupTempVar(uint64 ullTempVarId, uint16 usMainGroupId,
                           uint16 usSubGroupId);
  static bool GroupTempVars(std::vector<uint64>& listTempVarIds,
                            uint16 usMainGroupId, uint16 usSubGroupId);

  // 删除指定分组变量
  static bool DeleteGroupTempVars(uint16 usGroupId);

  // 更新变量值
  static bool UpdateTempVarValue(uint64 ullTempVarId,
                                 const std::string& strTempVarValue);

  //+++++++++++++++++++++++++++++++++++

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
