#include "ScriptManager.h"

using namespace SYE;

ScriptManager::ScriptManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  DLog(eLogType::Success, "\t ScriptManager instance created.");
}

ScriptManager::~ScriptManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t ScriptManager instance destroyed.");
}

bool ScriptManager::Initialize()
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
  DLog(eLogType::Success, "\t ScriptManager instance initialized.");
  return true;
}

bool ScriptManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t ScriptManager instance terminated.");
  return true;
}