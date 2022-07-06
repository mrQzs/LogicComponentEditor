#include "YDProjectManage.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QWidget>

#include "YDTask.h"
#include "YDVariable.h"
#include "common/YDHelper.h"
#include "common/YDLogger.h"
#include "modules/YDModules.h"

YDProjectManage *YDProjectManage::s_instance = nullptr;

YDProjectManage::YDProjectManage()
    : m_root{new YDTask},
      m_varRoot{new YDVariable},
      m_projectAccessorImpl{CProjectAccessorImpl::CreateInstance()},
      m_projectManager{nullptr},
      m_userManager{nullptr},
      m_deviceManager{nullptr},
      m_logicManager{nullptr},
      m_varGroupManage{nullptr},
      m_logicTask{nullptr},
      m_scriptManage{nullptr},
      m_compiler{nullptr},
      m_globalVarManage{nullptr},
      m_reciperVarManage{nullptr},
      m_localVarManage{nullptr},
      m_safeVarManage{nullptr},
      m_workParaManage{nullptr} {
  Q_ASSERT(nullptr == s_instance);
  s_instance = this;
  Q_ASSERT(m_projectAccessorImpl);
  initCode();
}

YDProjectManage::~YDProjectManage() {
  if (m_projectAccessorImpl->IsInitialized())
    m_projectAccessorImpl->Uninitialize();
}

void YDProjectManage::initCode() {
  QTextStream stream;
  QFile file(":/Code/VB");
  if (file.open(QFile::ReadOnly)) {
    stream.setDevice(&file);
    s_instance->m_vbCode = stream.readAll();
  }
  file.close();

  QFile file2(":/Code/VC");
  if (file2.open(QFile::ReadOnly)) {
    stream.setDevice(&file2);
    s_instance->m_vcCode = stream.readAll();
  }
  file2.close();

  QFile file3(":/Code/BPVB");
  if (file3.open(QFile::ReadOnly)) {
    stream.setDevice(&file3);
    s_instance->m_bpVBCode = stream.readAll();
  }
  file3.close();

  QFile file4(":/Code/BPVC");
  if (file4.open(QFile::ReadOnly)) {
    stream.setDevice(&file4);
    s_instance->m_bpVCCode = stream.readAll();
  }
  file4.close();
}

QString YDProjectManage::getVbCode() { return s_instance->m_vbCode; }

QString YDProjectManage::getVcCode() { return s_instance->m_vcCode; }

QString YDProjectManage::getBPVbCode() { return s_instance->m_bpVBCode; }

QString YDProjectManage::getBPVCCode() { return s_instance->m_bpVCCode; }

bool YDProjectManage::init() {
  std::string str{"test"};
  if (!s_instance->m_projectAccessorImpl->Initialize(CURRENT_VERSION, str,
                                                     CURRENT_CONFIG_FORMAT)) {
    return false;
  }
  if (s_instance->m_projectManager) s_instance->m_projectManager->Clear();
  if (s_instance->m_userManager) s_instance->m_userManager->Clear();
  if (s_instance->m_deviceManager) s_instance->m_deviceManager->Clear();
  if (s_instance->m_logicManager) s_instance->m_logicManager->Clear();
  if (s_instance->m_varGroupManage) s_instance->m_varGroupManage->Clear();
  if (s_instance->m_scriptManage) s_instance->m_scriptManage->Clear();
  if (s_instance->m_globalVarManage) s_instance->m_globalVarManage->Clear();
  if (s_instance->m_reciperVarManage) s_instance->m_reciperVarManage->Clear();
  if (s_instance->m_localVarManage) s_instance->m_localVarManage->Clear();
  if (s_instance->m_safeVarManage) s_instance->m_safeVarManage->Clear();
  if (s_instance->m_workParaManage) s_instance->m_workParaManage->Clear();

  s_instance->m_projectAccessorImpl->GetProjectManager(
      s_instance->m_projectManager);

  s_instance->m_projectManager->GetUserManager(s_instance->m_userManager);
  s_instance->m_projectManager->GetDeviceManager(s_instance->m_deviceManager);
  s_instance->m_projectManager->GetLogicManager(s_instance->m_logicManager);
  s_instance->m_projectManager->GetVariableGroupManager(
      s_instance->m_varGroupManage);
  s_instance->m_projectManager->GetExtendScriptManager(
      s_instance->m_scriptManage);

  s_instance->m_projectManager->GetGlobalVariableManager(
      s_instance->m_globalVarManage);
  s_instance->m_projectManager->GetRecipeVariableManager(
      s_instance->m_reciperVarManage);
  s_instance->m_projectManager->GetLocalVariableManager(
      s_instance->m_localVarManage);
  s_instance->m_projectManager->GetSafeVariableManager(
      s_instance->m_safeVarManage);

  s_instance->m_projectManager->GetWorkingParamManager(
      s_instance->m_workParaManage);

  Q_ASSERT(s_instance->m_projectManager);
  Q_ASSERT(s_instance->m_userManager);
  Q_ASSERT(s_instance->m_deviceManager);
  Q_ASSERT(s_instance->m_logicManager);
  Q_ASSERT(s_instance->m_varGroupManage);
  Q_ASSERT(s_instance->m_scriptManage);

  Q_ASSERT(s_instance->m_globalVarManage);
  Q_ASSERT(s_instance->m_reciperVarManage);
  Q_ASSERT(s_instance->m_scriptManage);
  Q_ASSERT(s_instance->m_scriptManage);

  Q_ASSERT(s_instance->m_workParaManage);

  initComplier();

  return true;
}

bool YDProjectManage::CreateProject(const std::string &name) {
  return s_instance->m_projectManager->CreateProject(name);
}

bool YDProjectManage::openProject(const std::string &name) {
  s_instance->m_projectManager->OpenProject(name);

  std::vector<yd::lg::LogicTask *> listLogicTasks;
  s_instance->m_logicManager->GetTasks(listLogicTasks);

  auto root = YDProjectManage::getYDTaskRoot();

  for (auto t : listLogicTasks) {
    auto task = new YDTask(t, root);
    task->initModules();
    root->addChild(task);
    std::vector<yd::lg::LogicSubTask *> listSubTasks;
    s_instance->m_logicManager->GetSubTasks(t->id, listSubTasks);
    task->initChilds(listSubTasks);
  }

  return true;
}

void YDProjectManage::setProjectPath(const QString &path) {
  s_instance->m_projectPath = path;
}

void YDProjectManage::saveModuleData(uint32 id,
                                     const QList<YDModule *> &modules) {
  for (int i = 0; i < modules.size(); ++i) {
    YDModule *m = modules[i];
    m->setParentId(id);
    if (0 == i) {
      m->setPreviousId(0);
      if (modules.size() > 1) {
        m->setNextId(modules[i + 1]->getLogicProcessId());
      } else
        m->setNextId(0);
    } else if (i > 0 && i <= modules.size() - 2) {
      m->setPreviousId(modules[i - 1]->getLogicProcessId());
      m->setNextId(modules[i + 1]->getLogicProcessId());
    } else {
      m->setPreviousId(modules[i - 1]->getLogicProcessId());
      m->setNextId(0);
    }
    modules[i]->getData();
  }
}

void YDProjectManage::saveProject() {
  auto root = YDProjectManage::getYDTaskRoot();
  auto childs = root->childs();
  for (auto s : childs) {
    QList<YDModule *> modules = s->getModules();
    s_instance->saveModuleData(s->id(), modules);
    auto subchilds = s->childs();
    for (auto sc : subchilds) {
      auto subModules = sc->getModules();
      s_instance->saveModuleData(sc->id(), subModules);
    }
  }

  if (s_instance->m_projectManager->SaveProject()) {
    YDLogger::info(QObject::tr("项目保存成功!"));
  }
}

void YDProjectManage::setVariableGruopModle(YDVariableGroupModel *model) {
  s_instance->m_varModel = model;
}

void YDProjectManage::updateVariableGroupModel() {
  s_instance->m_varGroupManage->GetMainGroups(s_instance->m_varFirstGroup);
  auto gp = s_instance->m_varFirstGroup;
  for (int i = 0; i < gp.size(); ++i) {
    auto id = gp[i]->group_id;
    std::vector<yd::vr::VariableGroup *> list;
    auto var = new YDVariable(gp[i], s_instance->m_varRoot);
    s_instance->m_varRoot->addChild(var);
    s_instance->m_varGroupManage->GetSubGroups(id, list);
    var->initChild(list);
  }
}

void YDProjectManage::deleteTaskProcess(uint32 taskId, uint32 processId) {
  s_instance->m_logicManager->DeleteTaskProcess(taskId, processId);
}

void YDProjectManage::GetTaskNames(std::map<uint32, std::string> &name) {
  s_instance->m_logicManager->GetTaskNames(name);
}

QString YDProjectManage::getTaskName(uint32 taskId) {
  std::map<uint32, std::string> name;
  GetTaskNames(name);
  return STRTQSTR(name[taskId]);
}

bool YDProjectManage::deleteMotionDevice(uint32 uiDeviceId) {
  return s_instance->m_deviceManager->DeleteMotionDevice(uiDeviceId);
}

QString YDProjectManage::getFileName() {
  return QString("%1.xml").arg(s_instance->m_fileName);
}

void YDProjectManage::getTaskXmlizedProcesses(uint32 id, std::string &xmlstr) {
  s_instance->m_logicManager->GetTaskXmlizedProcesses(id, xmlstr);
}

void YDProjectManage::getMotionAxisMoveSetups(
    std::vector<yd::dev::MCAxisMoveSetup *> &list) {
  s_instance->m_deviceManager->GetMotionAxisMoveSetups(list);
}

void YDProjectManage::createCondition(uint32 id, lg::Condition *&pcon) {
  s_instance->m_logicManager->CreateCondition(id, pcon);
}

void YDProjectManage::deleteCondition(uint32 id, uint32 cid) {
  s_instance->m_logicManager->DeleteCondition(id, cid);
}

void YDProjectManage::createSafeVariableCondition(uint64 id,
                                                  lg::Condition *&pc) {
  s_instance->m_safeVarManage->CreateCondition(id, pc);
}

void YDProjectManage::deleteSafeVariableCondition(uint64 id, uint32 cid) {
  s_instance->m_safeVarManage->DeleteCondition(id, cid);
}

void YDProjectManage::createAxisInplaceWait(uint32 id,
                                            lg::AxisInplaceWait *&pip) {
  s_instance->m_logicManager->CreateAxisInplaceWait(id, pip);
}

void YDProjectManage::deleteAxisInplaceWait(uint32 id, uint32 iid) {
  s_instance->m_logicManager->DeleteAxisInplaceWait(id, iid);
}

void YDProjectManage::getProcess(uint32 id, lg::LogicProcess *&process) {
  s_instance->m_logicManager->GetProcess(id, process);
}

std::map<uint32, std::string> &YDProjectManage::getProcessNames() {
  s_instance->m_logicManager->GetProcessNames(s_instance->m_mapId2Name);
  return s_instance->m_mapId2Name;
}

QString YDProjectManage::getVarName(uint64 id) {
  QString str;
  auto list = YDProjectManage::getAllVariables();
  for (auto v : list) {
    if (id == v->variable_id) {
      str = STRTQSTR(v->variable_name);
      break;
    }
  }
  return str;
}

uint64 YDProjectManage::getVarId(const QString &name) {
  uint64 id = 0;
  auto list = YDProjectManage::getAllVariables();
  for (auto v : list) {
    if (name == STRTQSTR(v->variable_name)) {
      id = v->variable_id;
      break;
    }
  }
  return id;
}

QString YDProjectManage::getVirtualVarName(uint64 id) {
  QString str;
  auto list = YDProjectManage::getAllVirtualVariables();
  for (auto v : list) {
    if (id == v->variable_id) {
      str = STRTQSTR(v->variable_name);
      break;
    }
  }
  return str;
}

uint64 YDProjectManage::getVirtualVarId(const QString &name) {
  uint64 id = 0;
  auto list = YDProjectManage::getAllVirtualVariables();
  for (auto v : list) {
    if (name == STRTQSTR(v->variable_name)) {
      id = v->variable_id;
      break;
    }
  }
  return id;
}

QString YDProjectManage::getSafeVirtualVarName(uint64 id) {
  QString str;
  auto list = YDProjectManage::getAllSafeVariables();
  for (auto v : list) {
    if (id == v->variable_id) {
      str = STRTQSTR(v->variable_name);
      break;
    }
  }
  return str;
}

uint64 YDProjectManage::getSafeVirtualVarId(const QString &name) {
  uint64 id = 0;
  auto list = YDProjectManage::getAllSafeVariables();
  for (auto v : list) {
    if (name == STRTQSTR(v->variable_name)) {
      id = v->variable_id;
      break;
    }
  }
  return id;
}

YDModule *YDProjectManage::getModule(uint8 type) {
  YDModule *module = nullptr;
  switch (type) {
    case LOGIC_PROCESS_ABSOLUTE_MOVE:
      module = new YDAbsMotion;
      break;
    case LOGIC_PROCESS_RELATIVE_MOVE:
      module = new YDRelMotion;
      break;
    case LOGIC_PROCESS_JOG_MOVE:
      module = new YDJogMotion;
      break;
    case LOGIC_PROCESS_MULTIAXISES_MOVE:
      module = new YDMulMotion;
      break;
    case LOGIC_PROCESS_HOME_MOVE:
      module = new YDBackZMotion;
      break;
    case LOGIC_PROCESS_STOP_MOVE:
      module = new YDStopMotion;
      break;
    case LOGIC_PROCESS_INPLACE_WAIT:
      module = new YDWaitMotion;
      break;
    case LOGIC_PROCESS_DO_CONTROL:
      module = new YDControlDO;
      break;
    case LOGIC_PROCESS_AO_CONTROL:
      module = new YDControlAO;
      break;
    case LOGIC_PROCESS_CYLINDER:
      module = new YDCylinder;
      break;
    case LOGIC_PROCESS_IF:
      module = new YDIfCondition;
      break;
    case LOGIC_PROCESS_IF_ELSE:
      module = new YDIfElseCondition;
      break;
    case LOGIC_PROCESS_COUNTER_LOOP:
      module = new YDTimesLoop;
      break;
    case LOGIC_PROCESS_CONDITION_LOOP:
      module = new YDConditionLoop;
      break;
    case LOGIC_PROCESS_BREAK:
      module = new YDJumpLoop;
      break;
    case LOGIC_PROCESS_DELAY:
      module = new YDDelayWait;
      break;
    case LOGIC_PROCESS_TASK_CALLER:
      module = new YDSubTaskCall;
      break;
    case LOGIC_PROCESS_TASK_STATE_WAIT:
      module = new YDWaitComplete;
      break;
    case LOGIC_PROCESS_MESSAGE:
      module = new YDAlarmConfirm;
      break;
    case LOGIC_PROCESS_PROGRAMABLE:
      module = new YDProgramable;
      break;
    case LOGIC_PROCESS_JUMP_TO:
      module = new YDJumpToTask;
      break;
    default:
      break;
  }

  return module;
}

YDTask *YDProjectManage::getYDTaskRoot() { return s_instance->m_root; }

YDVariable *YDProjectManage::getVarRoot() { return s_instance->m_varRoot; }

YDSafeVariable *YDProjectManage::getSafeVarRoot() {
  return s_instance->m_safeVarRoot;
}

void YDProjectManage::saveTabWParent() {
  s_instance->m_wpMap.clear();
  auto root = YDProjectManage::getYDTaskRoot();
  auto childs = root->childs();
  for (auto s : childs) {
    s_instance->m_wpMap[s] = s->widget()->parentWidget();
    s->widget()->setParent(nullptr);
    QCoreApplication::removePostedEvents(s->widget());

    auto subchilds = s->childs();
    for (auto sc : subchilds) {
      s_instance->m_wpMap[sc] = sc->widget()->parentWidget();
      sc->widget()->setParent(nullptr);
      QCoreApplication::removePostedEvents(sc->widget());
    }
  }
}

void YDProjectManage::restoreTabwParent() {
  auto root = YDProjectManage::getYDTaskRoot();
  auto childs = root->childs();
  for (auto s : childs) {
    QCoreApplication::removePostedEvents(s->widget());
    s->widget()->setParent(s_instance->m_wpMap[s]);

    auto subchilds = s->childs();
    for (auto sc : subchilds) {
      QCoreApplication::removePostedEvents(sc->widget());
      sc->widget()->setParent(s_instance->m_wpMap[sc]);
    }
  }
}

void YDProjectManage::setTabWNull() {
  auto root = YDProjectManage::getYDTaskRoot();
  auto childs = root->childs();
  for (auto s : childs) {
    s->widget()->setParent(nullptr);
    auto subchilds = s->childs();
    for (auto sc : subchilds) {
      sc->widget()->setParent(nullptr);
    }
  }
}

std::vector<yd::vr::SafeVariable *> &YDProjectManage::getGroupedSafeVariables(
    uint16 id) {
  s_instance->m_safeVarManage->GetGroupedVariables(id,
                                                   s_instance->m_showSafeVars);
  return s_instance->m_showSafeVars;
}

std::vector<yd::dev::DeviceType *>
    &YDProjectManage::getPredefinedDeviceTypes() {
  s_instance->m_deviceManager->GetPredefinedDeviceTypes(
      s_instance->m_deviceTypes);
  return s_instance->m_deviceTypes;
}

bool YDProjectManage::createMotionDevice(const std::string &name,
                                         dev::DeviceType *type,
                                         dev::MCDevice *&dev) {
  return s_instance->m_deviceManager->CreateMotionDevice(name, type, dev);
}

bool YDProjectManage::createCylinder(const std::string &name,
                                     dev::DeviceType *type,
                                     dev::Cylinder *&dev) {
  return s_instance->m_deviceManager->CreateCylinder(name, type, dev);
}

bool YDProjectManage::deleteCylinder(uint32 uiDeviceId) {
  return s_instance->m_deviceManager->DeleteCylinder(uiDeviceId);
}

bool YDProjectManage::deleteCylinder(const std::string &strDeviceName) {
  return s_instance->m_deviceManager->DeleteCylinder(strDeviceName);
}

bool YDProjectManage::updateMCDeviceVariables(dev::MCDevice *&dev) {
  return true;
}

bool YDProjectManage::updateCylinderVariables(dev::Cylinder *&cly) {
  return true;
}

bool YDProjectManage::createVariableMainGroup(yd::vr::VariableGroup *&gp) {
  return s_instance->m_varGroupManage->CreateMainGroup(gp);
}

bool YDProjectManage::createVariableSubGroup(uint16 id,
                                             vr::VariableGroup *&gp) {
  return s_instance->m_varGroupManage->CreateSubGroup(id, gp);
}

bool YDProjectManage::deleteVariableGroup(uint16 id) {
  return s_instance->m_varGroupManage->DeleteGroup(id);
}

void YDProjectManage::getGlobalGroupSysVar(
    uint16 id, std::vector<yd::vr::SystemVariable *> &list) {
  s_instance->m_globalVarManage->GetGroupedVariables(id, list);
}

void YDProjectManage::getGroupedSafeVariables(
    uint16 id, std::vector<yd::vr::SafeVariable *> &list) {
  s_instance->m_safeVarManage->GetGroupedVariables(id, list);
}

std::vector<yd::dev::MCAxisInfo *> &YDProjectManage::getAxisList() {
  s_instance->m_deviceManager->GetMotionAxisInfos(s_instance->m_axisInfoList);
  return s_instance->m_axisInfoList;
}

std::vector<yd::vr::SystemVariable *> &YDProjectManage::getAllVariables() {
  s_instance->m_projectManager->GetAllVariables(s_instance->m_allVars);
  return s_instance->m_allVars;
}

std::vector<yd::vr::SystemVariable *> &YDProjectManage::getAllVariables(
    uint16 id) {
  s_instance->m_list.clear();
  std::vector<yd::vr::SystemVariable *> glist;
  s_instance->m_globalVarManage->GetGroupedVariables(id, glist);
  std::vector<yd::vr::SystemVariable *> rlist;
  s_instance->m_reciperVarManage->GetGroupedVariables(id, rlist);
  std::vector<yd::vr::SystemVariable *> llist;
  s_instance->m_localVarManage->GetGroupedVariables(id, llist);

  for (auto v : glist) s_instance->m_list.push_back(v);
  for (auto v : rlist) s_instance->m_list.push_back(v);
  for (auto v : llist) s_instance->m_list.push_back(v);

  return s_instance->m_list;
}

std::vector<yd::vr::SystemVariable *>
    &YDProjectManage::getAllVirtualVariables() {
  s_instance->m_virtualVars.clear();
  s_instance->m_globalVarManage->GetAllVariables(s_instance->m_globalVars);
  s_instance->m_reciperVarManage->GetAllVariables(s_instance->m_reciperVars);
  s_instance->m_localVarManage->GetAllVariables(s_instance->m_localVars);

  for (auto v : s_instance->m_globalVars)
    s_instance->m_virtualVars.push_back(v);

  for (auto v : s_instance->m_reciperVars)
    s_instance->m_virtualVars.push_back(v);

  for (auto v : s_instance->m_localVars) s_instance->m_virtualVars.push_back(v);

  return s_instance->m_virtualVars;
}

std::vector<yd::vr::SafeVariable *> &YDProjectManage::getAllSafeVariables() {
  s_instance->m_safeVarManage->GetAllVariables(s_instance->m_safeVars);
  return s_instance->m_safeVars;
}

std::vector<yd::dev::MCDevice *> &YDProjectManage::getMotionDevices() {
  s_instance->m_deviceManager->GetMotionDevices(s_instance->m_devices);
  return s_instance->m_devices;
}

std::vector<yd::dev::Cylinder *> &YDProjectManage::getCylinders() {
  s_instance->m_deviceManager->GetCylinders(s_instance->m_cylinders);
  return s_instance->m_cylinders;
}

std::vector<yd::dev::IOInfo *> &YDProjectManage::getDIInfos() {
  s_instance->m_deviceManager->GetDIInfos(s_instance->m_diInfos);
  return s_instance->m_diInfos;
}

std::vector<yd::dev::IOInfo *> &YDProjectManage::getDOInfos() {
  s_instance->m_deviceManager->GetDOInfos(s_instance->m_doInfos);
  return s_instance->m_doInfos;
}

std::vector<yd::dev::IOInfo *> &YDProjectManage::getAIInfos() {
  s_instance->m_deviceManager->GetAIInfos(s_instance->m_aiInfos);
  return s_instance->m_aiInfos;
}

std::vector<yd::dev::IOInfo *> &YDProjectManage::getAOInfos() {
  s_instance->m_deviceManager->GetAOInfos(s_instance->m_aoInfos);
  return s_instance->m_aoInfos;
}

/**********************************************************/

int32 YDProjectManage::updateVariableGroupName(uint16 gid,
                                               const std::string &gname) {
  return s_instance->m_projectManager->UpdateVariableGroupName(gid, gname);
}

int32 YDProjectManage::UpdateVariableName(uint64 vid,
                                          const std::string &vname) {
  return s_instance->m_projectManager->UpdateVariableName(vid, vname);
}

int32 YDProjectManage::updateLogicTaskName(uint32 tid,
                                           const std::string &tname) {
  return s_instance->m_projectManager->UpdateLogicTaskName(tid, tname);
}

int32 YDProjectManage::updateLogicProcessName(uint32 tid, uint32 pid,
                                              const std::string &pname) {
  return s_instance->m_projectManager->UpdateLogicProcessName(tid, pid, pname);
}

int32 YDProjectManage::updateMotionDeviceName(uint32 did,
                                              const std::string &dname) {
  return s_instance->m_projectManager->UpdateMotionDeviceName(did, dname);
}

int32 YDProjectManage::updateMotionAxisName(uint32 did, uint16 aindex,
                                            const std::string &aname) {
  return s_instance->m_projectManager->UpdateMotionAxisName(did, aindex, aname);
}

int32 YDProjectManage::updateCylinderName(uint32 did,
                                          const std::string &cyname) {
  return s_instance->m_projectManager->UpdateCylinderName(did, cyname);
}

int32 YDProjectManage::updateDIName(uint32 did, uint8 dtype, uint16 diindex,
                                    const std::string &dname) {
  return s_instance->m_projectManager->UpdateDIName(did, dtype, diindex, dname);
}

int32 YDProjectManage::updateDOName(uint32 did, uint8 dtype, uint16 doindex,
                                    const std::string &dname) {
  return s_instance->m_projectManager->UpdateDOName(did, dtype, doindex, dname);
}

int32 YDProjectManage::updateAIName(uint32 did, uint8 dtype, uint16 aiindex,
                                    const std::string &aname) {
  return s_instance->m_projectManager->UpdateAIName(did, dtype, aiindex, aname);
}

int32 YDProjectManage::updateAOName(uint32 did, uint8 dtype, uint16 aoindex,
                                    const std::string &aname) {
  return s_instance->m_projectManager->UpdateAOName(did, dtype, aoindex, aname);
}

/**********************************************************/

void YDProjectManage::createTask(yd::lg::LogicTask *&task) {
  s_instance->m_logicManager->CreateTask(task);
}

void YDProjectManage::deleteTask(uint32 taskId) {
  s_instance->m_logicManager->DeleteTask(taskId);
}

void YDProjectManage::createSubTask(uint32 taskId, lg::LogicSubTask *&subtask) {
  s_instance->m_logicManager->CreateSubTask(taskId, subtask);
}

void YDProjectManage::deleteSubTask(uint32 taskId, uint32 subtaskId) {
  s_instance->m_logicManager->DeleteSubTask(taskId, subtaskId);
}

void YDProjectManage::createTaskProcess(uint32 id, lg::LogicProcess *&lp) {
  s_instance->m_logicManager->CreateTaskProcess(id, lp);
}

void YDProjectManage::getTaskProcesses(
    uint32 taskId, std::vector<yd::lg::LogicProcess *> &list) {
  s_instance->m_logicManager->GetTaskProcesses(taskId, list);
}

void YDProjectManage::getSubTaskProcesses(
    uint32 subTaskId, std::vector<yd::lg::LogicProcess *> &list) {
  s_instance->m_logicManager->GetSubTaskProcesses(subTaskId, list);
}

bool YDProjectManage::getProcesses(uint32 pid, std::vector<uint32> &ids,
                                   std::vector<yd::lg::LogicProcess *> &list) {
  return s_instance->m_logicManager->GetProcesses(pid, ids, list);
}

// Motion
void YDProjectManage::attachAbsoluteMoveModule(
    uint32 id, lg::AbsoluteMoveModule *&module) {
  s_instance->m_logicManager->AttachAbsoluteMoveModule(id, module);
}

void YDProjectManage::attachRelativeMoveModule(
    uint32 id, lg::RelativeMoveModule *&module) {
  s_instance->m_logicManager->AttachRelativeMoveModule(id, module);
}

void YDProjectManage::attachJogMoveModule(uint32 id,
                                          lg::JogMoveModule *&module) {
  s_instance->m_logicManager->AttachJogMoveModule(id, module);
}

void YDProjectManage::attachMultiAxisesMoveModule(
    uint32 id, lg::MultAxisesMoveModule *&module) {
  s_instance->m_logicManager->AttachMultiAxisesMoveModule(id, module);
}

void YDProjectManage::attachHomeMoveModule(uint32 id,
                                           lg::HomeMoveModule *&module) {
  s_instance->m_logicManager->AttachHomeMoveModule(id, module);
}

void YDProjectManage::attachStopMoveModule(uint32 id,
                                           lg::StopMoveModule *&module) {
  s_instance->m_logicManager->AttachStopMoveModule(id, module);
}

void YDProjectManage::attachInplaceWaitModule(uint32 id,
                                              lg::InplaceWaitModule *&module) {
  s_instance->m_logicManager->AttachInplaceWaitModule(id, module);
}

// IO
void YDProjectManage::attachDOControlModule(uint32 id,
                                            lg::DOControlModule *&module) {
  s_instance->m_logicManager->AttachDOControlModule(id, module);
}

void YDProjectManage::attachAOControlModule(uint32 id,
                                            lg::AOControlModule *&module) {
  s_instance->m_logicManager->AttachAOControlModule(id, module);
}

void YDProjectManage::attachCylinderModule(uint32 id,
                                           lg::CylinderModule *&module) {
  s_instance->m_logicManager->AttachCylinderModule(id, module);
}

// Condition
void YDProjectManage::getIfElseProcess(uint32 processId,
                                       lg::IfElseProcess *&process) {
  s_instance->m_logicManager->GetIfElseProcess(processId, process);
}

void YDProjectManage::getIfProcess(uint32 processId, lg::IfProcess *&process) {
  s_instance->m_logicManager->GetIfProcess(processId, process);
}

void YDProjectManage::attachCounterLoopModule(uint32 id,
                                              lg::CounterLoopModule *&module) {
  s_instance->m_logicManager->AttachCounterLoopModule(id, module);
}

void YDProjectManage::getConditionLoopProcess(
    uint32 id, lg::ConditionLoopProcess *&process) {
  s_instance->m_logicManager->GetConditionLoopProcess(id, process);
}

void YDProjectManage::attachBreakModule(uint32 id, lg::BreakModule *&module) {
  s_instance->m_logicManager->AttachBreakModule(id, module);
}

void YDProjectManage::attachDelayModule(uint32 id, lg::DelayModule *&module) {
  s_instance->m_logicManager->AttachDelayModule(id, module);
}

// Other
void YDProjectManage::attachTaskCallerModule(uint32 id,
                                             lg::TaskCallerModule *&module) {
  s_instance->m_logicManager->AttachTaskCallerModule(id, module);
}

void YDProjectManage::attachMessageModule(uint32 id,
                                          lg::MessageModule *&module) {
  s_instance->m_logicManager->AttachMessageModule(id, module);
}

void YDProjectManage::attachTaskStateWaitModule(
    uint32 id, lg::TaskStateWaitModule *&module) {
  s_instance->m_logicManager->AttachTaskStateWaitModule(id, module);
}

void YDProjectManage::attachProgramModule(uint32 id,
                                          lg::ProgramModule *&module) {
  s_instance->m_logicManager->AttachProgramModule(id, module);
}

void YDProjectManage::attachJumpToModule(uint32 id, lg::JumpToModule *&module) {
  s_instance->m_logicManager->AttachJumpToModule(id, module);
}

//########################

void YDProjectManage::createTaskIfElseProcess(uint32 id,
                                              lg::IfElseProcess *&process) {
  s_instance->m_logicManager->CreateTaskIfElseProcess(id, process);
}

void YDProjectManage::createTaskIfProcess(uint32 id, lg::IfProcess *&process) {
  s_instance->m_logicManager->CreateTaskIfProcess(id, process);
}

void YDProjectManage::createTaskConditionLoopProcess(
    uint32 id, lg::ConditionLoopProcess *&process) {
  s_instance->m_logicManager->CreateTaskConditionLoopProcess(id, process);
}

void YDProjectManage::createGlobalVar(uint16 usMainGroupId, uint16 usSubGroupId,
                                      uint8 ucValueType,
                                      vr::SystemVariable *&pVariable) {
  s_instance->m_globalVarManage->CreateVariable(usMainGroupId, usSubGroupId,
                                                ucValueType, pVariable);
}

void YDProjectManage::createSafeVariable(uint16 mainId, uint16 subId,
                                         vr::SafeVariable *&safeVar) {
  s_instance->m_safeVarManage->CreateVariable(mainId, subId, safeVar);
}

void YDProjectManage::initComplier() {
  if (nullptr == s_instance->m_compiler) {
    s_instance->m_complierImpl = yd::CCompilerImpl::CreateInstance();
    s_instance->m_complierImpl->Initialize(0, "v1");
    s_instance->m_complierImpl->GetCompiler(s_instance->m_compiler);

    Q_ASSERT(s_instance->m_compiler);
  }
}

void YDProjectManage::enumFrameworks(uint8 cpu,
                                     std::vector<std::string> &fram) {
  s_instance->m_compiler->EnumFrameworks(cpu, fram);
}

std::string YDProjectManage::getProgrammableProcessCodeFilePath(
    const std::string &name, uint8 comp) {
  return s_instance->m_compiler->GetProgrammableProcessCodeFilePath(name, comp);
}

void YDProjectManage::compileProgrammableProcess(const std::string &pname,
                                                 uint8 ctype,
                                                 const std::string &fram,
                                                 uint8 cpu,
                                                 std::string &cinfo) {
  s_instance->m_compiler->CompileProgrammableProcess(pname, ctype, fram, cpu,
                                                     cinfo);
}

bool YDProjectManage::isExisting(const std::string &sname) {
  return s_instance->m_scriptManage->IsExisting(sname);
}

bool YDProjectManage::getScript(const std::string &sname,
                                adv::ExtendScript *&esc) {
  return s_instance->m_scriptManage->GetScript(sname, esc);
}

std::vector<adv::ExtendScript *> &YDProjectManage::getScripts() {
  s_instance->m_scriptManage->GetScripts(s_instance->m_scriptList);
  return s_instance->m_scriptList;
}

int32 YDProjectManage::createScript(const std::string &sname,
                                    adv::ExtendScript *&esc) {
  return s_instance->m_scriptManage->CreateScript(sname, esc);
}

int32 YDProjectManage::updateScript(adv::ExtendScript *pExtendScript) {
  return s_instance->m_scriptManage->UpdateScript(pExtendScript);
}

int32 YDProjectManage::deleteScript(const std::string &sname) {
  return s_instance->m_scriptManage->DeleteScript(sname);
}

std::string YDProjectManage::getExtendableScriptCodeFilePath(
    const std::string &name, uint8 comp) {
  return s_instance->m_compiler->GetExtendableScriptCodeFilePath(name, comp);
}

void YDProjectManage::compileExtendableScript(const std::string &sname,
                                              uint8 ctype,
                                              const std::string &fram,
                                              uint8 cpu, std::string &sinfo) {
  s_instance->m_compiler->CompileExtendableScript(sname, ctype, fram, cpu,
                                                  sinfo);
}

bool YDProjectManage::enumuerateProjects(
    std::vector<std::string> &listProjectNames) {
  return s_instance->m_projectManager->EnumuerateProjects(listProjectNames);
}

bool YDProjectManage::isProjectExisting(const std::string &strProjectName) {
  return s_instance->m_projectManager->IsProjectExisting(strProjectName);
}

bool YDProjectManage::isProjectOpened() {
  return s_instance->m_projectManager->IsProjectOpened();
}

bool YDProjectManage::isProjectOpened(const std::string &strProjectName) {
  return s_instance->m_projectManager->IsProjectOpened(strProjectName);
}

bool YDProjectManage::saveProjectAs(const std::string &strProjectNewName) {
  return s_instance->m_projectManager->SaveProjectAs(strProjectNewName);
}

bool YDProjectManage::saveProjectAs(const std::string &strProjectOldName,
                                    const std::string &strProjectNewName) {
  return s_instance->m_projectManager->SaveProjectAs(strProjectOldName,
                                                     strProjectNewName);
}

bool YDProjectManage::closeProject() {
  return s_instance->m_projectManager->CloseProject();
}

QString YDProjectManage::getCurrentProject() {
  auto data = s_instance->m_projectManager->GetCurrentProject();
  return STRTQSTR(data);
}

bool YDProjectManage::renameProject(const std::string &strProjectNewName) {
  return s_instance->m_projectManager->RenameProject(strProjectNewName);
}

bool YDProjectManage::renameProject(const std::string &strProjectOldName,
                                    const std::string &strProjectNewName) {
  return s_instance->m_projectManager->RenameProject(strProjectOldName,
                                                     strProjectNewName);
}

bool YDProjectManage::deleteProject() {
  return s_instance->m_projectManager->DeleteProject();
}

bool YDProjectManage::deleteProject(const std::string &strProjectName) {
  return s_instance->m_projectManager->DeleteProject(strProjectName);
}

bool YDProjectManage::enumuerateRecipes(
    std::vector<std::string> &listRecipeNames) {
  return s_instance->m_projectManager->EnumuerateRecipes(listRecipeNames);
}

bool YDProjectManage::isRecipeExisting(const std::string &strRecipeName) {
  return s_instance->m_projectManager->IsRecipeExisting(strRecipeName);
}

bool YDProjectManage::isRecipeOpened() {
  return s_instance->m_projectManager->IsRecipeOpened();
}

bool YDProjectManage::isRecipeOpened(const std::string &strRecipeName) {
  return s_instance->m_projectManager->IsRecipeOpened(strRecipeName);
}

bool YDProjectManage::createRecipe(const std::string &strRecipeName) {
  return s_instance->m_projectManager->CreateRecipe(strRecipeName);
}

bool YDProjectManage::openRecipe(const std::string &strRecipeName) {
  return s_instance->m_projectManager->OpenRecipe(strRecipeName);
}

bool YDProjectManage::saveRecipe() {
  return s_instance->m_projectManager->SaveRecipe();
}

bool YDProjectManage::saveRecipeAs(const std::string &strRecipeNewName) {
  return s_instance->m_projectManager->SaveRecipeAs(strRecipeNewName);
}

bool YDProjectManage::saveRecipeAs(const std::string &strRecipeOldName,
                                   const std::string &strRecipeNewName) {
  return s_instance->m_projectManager->SaveRecipeAs(strRecipeOldName,
                                                    strRecipeNewName);
}

QString YDProjectManage::getCurrentRecipe() {
  auto data = s_instance->m_projectManager->GetCurrentRecipe();
  return STRTQSTR(data);
}

bool YDProjectManage::renameRecipe(const std::string &strRecipeNewName) {
  return s_instance->m_projectManager->RenameRecipe(strRecipeNewName);
}

bool YDProjectManage::renameRecipe(const std::string &strRecipeOldName,
                                   const std::string &strRecipeNewName) {
  return s_instance->m_projectManager->RenameRecipe(strRecipeOldName,
                                                    strRecipeNewName);
}

bool YDProjectManage::deleteRecipe() {
  return s_instance->m_projectManager->DeleteRecipe();
}

bool YDProjectManage::deleteRecipe(const std::string &strRecipeName) {
  return s_instance->m_projectManager->DeleteRecipe(strRecipeName);
}

bool YDProjectManage::IsChanged() {
  return s_instance->m_workParaManage->IsChanged();
}

const char *YDProjectManage::GetErrorMsg() {
  return s_instance->m_workParaManage->GetErrorMsg();
}

void YDProjectManage::Clear() { s_instance->m_workParaManage->Clear(); }

bool YDProjectManage::SetDefaultRecipe(const std::string &strRecipeName) {
  return s_instance->m_workParaManage->SetDefaultRecipe(strRecipeName);
}

const char *YDProjectManage::GetDefaultRecipe() {
  return s_instance->m_workParaManage->GetDefaultRecipe();
}

bool YDProjectManage::SetHomeMoveScriptType(uint8 ucScriptType) {
  return s_instance->m_workParaManage->SetHomeMoveScriptType(ucScriptType);
}

uint8 YDProjectManage::GetHomeMoveScriptType() {
  return s_instance->m_workParaManage->GetHomeMoveScriptType();
}

bool YDProjectManage::IsOnlineDebugOpened() {
  return s_instance->m_workParaManage->IsOnlineDebugOpened();
}

bool YDProjectManage::OpenOnlineDebug(bool bOpen) {
  return s_instance->m_workParaManage->OpenOnlineDebug(bOpen);
}

bool YDProjectManage::GetDataGateway(std::string &strAddress, uint16 &usPort,
                                     uint32 &uiTimeout) {
  return s_instance->m_workParaManage->GetDataGateway(strAddress, usPort,
                                                      uiTimeout);
}

bool YDProjectManage::SetDataGateway(const std::string &strAddress,
                                     uint16 usPort, uint32 uiTimeout) {
  return s_instance->m_workParaManage->SetDataGateway(strAddress, usPort,
                                                      uiTimeout);
}

bool YDProjectManage::GetDataReceivers(
    std::vector<prj::DataServer *> &listDataReceivers) {
  return s_instance->m_workParaManage->GetDataReceivers(listDataReceivers);
}

bool YDProjectManage::AddDataReceiver(const std::string &strAddress,
                                      uint16 usPort, uint32 uiTimeout) {
  return s_instance->m_workParaManage->AddDataReceiver(strAddress, usPort,
                                                       uiTimeout);
}

//+++++++++++++++++++++++++++++++++++

bool YDProjectManage::IsGlobalVarExisting(uint64 ullGlobalVarId) {
  return s_instance->m_globalVarManage->IsVariableExisting(ullGlobalVarId);
}

bool YDProjectManage::IsGlobalVarExisting(const std::string &strGlobalVarName) {
  return s_instance->m_globalVarManage->IsVariableExisting(strGlobalVarName);
}

bool YDProjectManage::CreateGlobalVar(uint16 usMainGroupId, uint16 usSubGroupId,
                                      uint8 ucValueType,
                                      vr::SystemVariable *&pGlobalVar) {
  return s_instance->m_globalVarManage->CreateVariable(
      usMainGroupId, usSubGroupId, ucValueType, pGlobalVar);
}

bool YDProjectManage::CreateGlobalVars(
    uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType,
    uint8 ucNumber, std::vector<yd::vr::SystemVariable *> &listGlobalVars) {
  return s_instance->m_globalVarManage->CreateVariables(
      usMainGroupId, usSubGroupId, ucValueType, ucNumber, listGlobalVars);
}

bool YDProjectManage::GetGlobalVar(uint64 ullGlobalVarId,
                                   vr::SystemVariable *&pGlobalVar) {
  return s_instance->m_globalVarManage->GetVariable(ullGlobalVarId, pGlobalVar);
}

bool YDProjectManage::GetAllGlobalVars(
    std::vector<yd::vr::SystemVariable *> &listGlobalVars) {
  return s_instance->m_globalVarManage->GetAllVariables(listGlobalVars);
}

std::vector<yd::vr::SystemVariable *> &YDProjectManage::GetGroupedGlobalVars(
    uint16 usMainGroupId) {
  s_instance->m_globalVarManage->GetGroupedVariables(
      usMainGroupId, s_instance->m_listGloabalVar);

  return s_instance->m_listGloabalVar;
}

bool YDProjectManage::GetGroupedGlobalVars(
    uint16 usGroupId, std::vector<yd::vr::SystemVariable *> &listGlobalVars) {
  return s_instance->m_globalVarManage->GetGroupedVariables(usGroupId,
                                                            listGlobalVars);
}

bool YDProjectManage::DeleteGlobalVar(uint64 ullGlobalVarId) {
  return s_instance->m_globalVarManage->DeleteVariable(ullGlobalVarId);
}

int32 YDProjectManage::UpdateGlobalVarName(
    uint64 ullGlobalVarIdToUpdate, const std::string &strNewGlobalVarName) {
  return s_instance->m_globalVarManage->UpdateVariableName(
      ullGlobalVarIdToUpdate, strNewGlobalVarName);
}

bool YDProjectManage::GroupGlobalVar(uint64 ullGlobalVarId,
                                     uint16 usMainGroupId,
                                     uint16 usSubGroupId) {
  return s_instance->m_globalVarManage->GroupVariable(
      ullGlobalVarId, usMainGroupId, usSubGroupId);
}

bool YDProjectManage::GroupGlobalVars(std::vector<uint64> &listGlobalVarIds,
                                      uint16 usMainGroupId,
                                      uint16 usSubGroupId) {
  return s_instance->m_globalVarManage->GroupVariables(
      listGlobalVarIds, usMainGroupId, usSubGroupId);
}

bool YDProjectManage::DeleteGroupGlobalVars(uint16 usGroupId) {
  return s_instance->m_globalVarManage->DeleteGroupVariables(usGroupId);
}

bool YDProjectManage::UpdateGlobalVarValue(
    uint64 ullGlobalVarId, const std::string &strGlobalVarValue) {
  return s_instance->m_globalVarManage->UpdateVariableValue(ullGlobalVarId,
                                                            strGlobalVarValue);
}

//+++++++++++++++++++++++++++++++++++
bool YDProjectManage::IsReciVarExisting(uint64 ullReciVarId) {
  return s_instance->m_reciperVarManage->IsVariableExisting(ullReciVarId);
}

bool YDProjectManage::IsReciVarExisting(const std::string &strReciVarName) {
  return s_instance->m_reciperVarManage->IsVariableExisting(strReciVarName);
}

bool YDProjectManage::CreateReciVar(uint16 usMainGroupId, uint16 usSubGroupId,
                                    uint8 ucValueType,
                                    vr::SystemVariable *&pReciVar) {
  return s_instance->m_reciperVarManage->CreateVariable(
      usMainGroupId, usSubGroupId, ucValueType, pReciVar);
}

bool YDProjectManage::CreateReciVars(
    uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType,
    uint8 ucNumber, std::vector<yd::vr::SystemVariable *> &listReciVars) {
  return s_instance->m_reciperVarManage->CreateVariables(
      usMainGroupId, usSubGroupId, ucValueType, ucNumber, listReciVars);
}

bool YDProjectManage::GetReciVar(uint64 ullReciVarId,
                                 vr::SystemVariable *&pReciVar) {
  return s_instance->m_reciperVarManage->GetVariable(ullReciVarId, pReciVar);
}

bool YDProjectManage::GetAllReciVars(
    std::vector<yd::vr::SystemVariable *> &listReciVars) {
  return s_instance->m_reciperVarManage->GetAllVariables(listReciVars);
}

std::vector<yd::vr::SystemVariable *> &YDProjectManage::GetGroupedReciVars(
    uint16 usMainGroupId) {
  s_instance->m_reciperVarManage->GetGroupedVariables(
      usMainGroupId, s_instance->m_listReciVar);
  return s_instance->m_listReciVar;
}

bool YDProjectManage::GetGroupedReciVars(
    uint16 usGroupId, std::vector<yd::vr::SystemVariable *> &listReciVars) {
  return s_instance->m_reciperVarManage->GetGroupedVariables(usGroupId,
                                                             listReciVars);
}

bool YDProjectManage::DeleteReciVar(uint64 ullReciVarId) {
  return s_instance->m_reciperVarManage->DeleteVariable(ullReciVarId);
}

int32 YDProjectManage::UpdateReciVarName(uint64 ullReciVarIdToUpdate,
                                         const std::string &strNewReciVarName) {
  return s_instance->m_reciperVarManage->UpdateVariableName(
      ullReciVarIdToUpdate, strNewReciVarName);
}

bool YDProjectManage::GroupReciVar(uint64 ullReciVarId, uint16 usMainGroupId,
                                   uint16 usSubGroupId) {
  return s_instance->m_reciperVarManage->GroupVariable(
      ullReciVarId, usMainGroupId, usSubGroupId);
}

bool YDProjectManage::GroupReciVars(std::vector<uint64> &listReciVarIds,
                                    uint16 usMainGroupId, uint16 usSubGroupId) {
  return s_instance->m_reciperVarManage->GroupVariables(
      listReciVarIds, usMainGroupId, usSubGroupId);
}

bool YDProjectManage::DeleteGroupReciVars(uint16 usGroupId) {
  return s_instance->m_reciperVarManage->DeleteGroupVariables(usGroupId);
}

bool YDProjectManage::UpdateReciVarValue(uint64 ullReciVarId,
                                         const std::string &strReciVarValue) {
  return s_instance->m_reciperVarManage->UpdateVariableValue(ullReciVarId,
                                                             strReciVarValue);
}
//+++++++++++++++++++++++++++++++++++
bool YDProjectManage::IsTempVarExisting(uint64 ullTempVarId) {
  return s_instance->m_localVarManage->IsVariableExisting(ullTempVarId);
}

bool YDProjectManage::IsTempVarExisting(const std::string &strTempVarName) {
  return s_instance->m_localVarManage->IsVariableExisting(strTempVarName);
}

bool YDProjectManage::CreateTempVar(uint16 usMainGroupId, uint16 usSubGroupId,
                                    uint8 ucValueType,
                                    vr::SystemVariable *&pTempVar) {
  return s_instance->m_localVarManage->CreateVariable(
      usMainGroupId, usSubGroupId, ucValueType, pTempVar);
}

bool YDProjectManage::CreateTempVars(
    uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType,
    uint8 ucNumber, std::vector<yd::vr::SystemVariable *> &listTempVars) {
  return s_instance->m_localVarManage->CreateVariables(
      usMainGroupId, usSubGroupId, ucValueType, ucNumber, listTempVars);
}

bool YDProjectManage::GetTempVar(uint64 ullTempVarId,
                                 vr::SystemVariable *&pTempVar) {
  return s_instance->m_localVarManage->GetVariable(ullTempVarId, pTempVar);
}

bool YDProjectManage::GetAllTempVars(
    std::vector<yd::vr::SystemVariable *> &listTempVars) {
  return s_instance->m_localVarManage->GetAllVariables(listTempVars);
}

std::vector<yd::vr::SystemVariable *> &YDProjectManage::GetGroupedTempVars(
    uint16 usMainGroupId) {
  s_instance->m_localVarManage->GetGroupedVariables(usMainGroupId,
                                                    s_instance->m_listTempVar);
  return s_instance->m_listTempVar;
}

bool YDProjectManage::GetGroupedTempVars(
    uint16 usGroupId, std::vector<yd::vr::SystemVariable *> &listTempVars) {
  return s_instance->m_localVarManage->GetGroupedVariables(usGroupId,
                                                           listTempVars);
}

bool YDProjectManage::DeleteTempVar(uint64 ullTempVarId) {
  return s_instance->m_localVarManage->DeleteVariable(ullTempVarId);
}

int32 YDProjectManage::UpdateTempVarName(uint64 ullTempVarIdToUpdate,
                                         const std::string &strNewTempVarName) {
  return s_instance->m_localVarManage->UpdateVariableName(ullTempVarIdToUpdate,
                                                          strNewTempVarName);
}

bool YDProjectManage::GroupTempVar(uint64 ullTempVarId, uint16 usMainGroupId,
                                   uint16 usSubGroupId) {
  return s_instance->m_localVarManage->GroupVariable(
      ullTempVarId, usMainGroupId, usSubGroupId);
}

bool YDProjectManage::GroupTempVars(std::vector<uint64> &listTempVarIds,
                                    uint16 usMainGroupId, uint16 usSubGroupId) {
  return s_instance->m_localVarManage->GroupVariables(
      listTempVarIds, usMainGroupId, usSubGroupId);
}

bool YDProjectManage::DeleteGroupTempVars(uint16 usGroupId) {
  return s_instance->m_localVarManage->DeleteGroupVariables(usGroupId);
}

bool YDProjectManage::UpdateTempVarValue(uint64 ullTempVarId,
                                         const std::string &strTempVarValue) {
  return s_instance->m_localVarManage->UpdateVariableValue(ullTempVarId,
                                                           strTempVarValue);
}

bool YDProjectManage::DeleteSafeVar(uint64 ullTempVarId) {
  return s_instance->m_safeVarManage->DeleteVariable(ullTempVarId);
}

bool YDProjectManage::GetDeviceType(uint32 uiDeviceId,
                                    dev::DeviceType *&pDeviceType) {
  return s_instance->m_deviceManager->GetDeviceType(uiDeviceId, pDeviceType);
}

const char *YDProjectManage::GetDeviceName(uint32 uiDeviceId) {
  return s_instance->m_deviceManager->GetDeviceName(uiDeviceId);
}

uint32 YDProjectManage::GetDeviceTypeId(uint32 uiDeviceId) {
  return s_instance->m_deviceManager->GetDeviceTypeId(uiDeviceId);
}

const char *YDProjectManage::GetDeviceTypeName(uint32 uiDeviceId) {
  return s_instance->m_deviceManager->GetDeviceTypeName(uiDeviceId);
}

bool YDProjectManage::GetDevice(uint32 uiDeviceId, dev::Device *&pDevice) {
  return s_instance->m_deviceManager->GetDevice(uiDeviceId, pDevice);
}

bool YDProjectManage::GetDevice(const std::string &strDeviceName,
                                dev::Device *&pDevice) {
  return s_instance->m_deviceManager->GetDevice(strDeviceName, pDevice);
}
