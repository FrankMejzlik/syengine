#include "ShadowManager.h"

using namespace WeSp;

ShadowManager::ShadowManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  //_subModules.insert(std::make_pair(ID_AI_MANAGER, std::make_shared<AIManager>(this)));
  //_subModules.insert(std::make_pair(ID_LOGIC_MANAGER, std::make_shared<LogicManager>(this)));

  DLog(eLogType::Success, "ShadowManager instance created.");
}

ShadowManager::~ShadowManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "ShadowManager instance destroyed.");
}

bool ShadowManager::Initialize()
{
  // Initialize submodules.
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "ShadowManager instance initialized.");
  return true;
}

bool ShadowManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "ShadowManager instance terminated.");
  return true;
}