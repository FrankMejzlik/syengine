#include "MouseManager.h"

using namespace WeSp;

MouseManager::MouseManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  DLog(eLogType::Success, "\t MouseManager instance created.");
}

MouseManager::~MouseManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t MouseManager instance destroyed.");
}

bool MouseManager::Initialize()
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
  DLog(eLogType::Success, "\t MouseManager instance initialized.");
  return true;
}

bool MouseManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t MouseManager instance terminated.");
  return true;
}