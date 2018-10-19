
#include "NetworkManager.h"

NetworkManager::NetworkManager(Engine* pParentInstance):
  IMainEngineModule(pParentInstance)
{
  DLog(eLogType::Success, "NetworkManager instance created.");
}

NetworkManager::~NetworkManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "NetworkManager instance destroyed.");
}

bool NetworkManager::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // Call parent Initialize method
  if (!IMainEngineModule::Initialize(modules))
  {
    DLog(eLogType::Error, "Initialization of base Initialize in NetworkManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "NetworkManager instance initialized.");
  return true;
}

bool NetworkManager::Terminate()
{
  // Class specific terminate

  if (!IMainEngineModule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "Error terminating base of EntitiManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "NetworkManager instance terminated.");
  return true;
}
