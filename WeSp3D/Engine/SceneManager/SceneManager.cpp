
#include "SceneManager.h"

SceneManager::SceneManager(Engine* pParentInstance):
  IMainEngineModule(pParentInstance)
{
  DLog(eLogType::Success, "SceneManager instance created.");
}

SceneManager::~SceneManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "SceneManager instance destroyed.");
}

bool SceneManager::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // Call parent Initialize method
  if (!IMainEngineModule::Initialize(modules))
  {
    DLog(eLogType::Error, "Initialization of base Initialize in SceneManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "SceneManager instance initialized.");
  return true;
}

bool SceneManager::Terminate()
{
  // Class specific terminate

  if (!IMainEngineModule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "Error terminating base of EntitiManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "SceneManager instance terminated.");
  return true;
}