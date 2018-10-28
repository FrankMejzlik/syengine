
#include "NetworkManager.h"

NetworkManager::NetworkManager(BaseModule &parentModule):
  BaseModule(parentModule)
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

bool NetworkManager::Initialize()
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
  DLog(eLogType::Success, "NetworkManager instance initialized.");
  return true;
}

bool NetworkManager::Terminate()
{
  // Class specific terminate


  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "NetworkManager instance terminated.");
  return true;
}

void NetworkManager::ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene)
{}
