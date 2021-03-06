#include "LogicManager.h"

#include "ScriptManager.h"

using namespace SYE;

LogicManager::LogicManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  _subModules.insert(std::make_pair(ID_SCRIPT_MANAGER, std::make_unique<ScriptManager>(*this, _pEngineContext)));
  //_subModules.insert(std::make_pair(ID_AI_MANAGER, std::make_unique<AiManager>(*this, _pEngineContext)));

  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::cSuccess, "\t LogicManager instance created.");
}

LogicManager::~LogicManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "\t LogicManager instance destroyed.");
}

bool LogicManager::Initialize()
{
  // Initialize submodules.
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization

  SetModuleState(eModuleState::OK);
  DLog(eLogType::cSuccess, "\t LogicManager instance initialized.");
  return true;
}

bool LogicManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "\t LogicManager instance terminated.");
  return true;
}

void LogicManager::TriggerOnInitScene(Scene* pScene)
{
  SCRIPT_MANAGER->TriggerOnInitializeScene(pScene);
}

bool LogicManager::InitializeScene(Scene* pScene)
{
  bool result = true;

  // Initialize in submodules
  result = result && SCRIPT_MANAGER->InitializeScene(pScene);
  //result = result && AI_MANAGER->InitializeScene(pScene);

  return result;
}

void LogicManager::ProcessScene([[maybe_unused]][[maybe_unused]] dfloat deltaTime, Scene* pScene)
{

  // Call submodules
  SCRIPT_MANAGER->ProcessScene(deltaTime, pScene);
  //AI_MANAGER->ProcessScene(deltaTime, pScene);

}
