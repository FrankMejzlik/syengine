#include "KeyboardManager.h"

using namespace SYE;

KeyboardManager::KeyboardManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{

  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::cSuccess, "\t KeyboardManager instance created.");
}

KeyboardManager::~KeyboardManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "\t KeyboardManager instance destroyed.");
}

bool KeyboardManager::Initialize()
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
  DLog(eLogType::cSuccess, "\t KeyboardManager instance initialized.");
  return true;
}

bool KeyboardManager::Terminate()
{
  // Class specific terminate


  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "\t KeyboardManager instance terminated.");
  return true;
}