
#include "NetworkManager.h"

NetworkManager::NetworkManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::cSuccess, "NetworkManager instance created.");
}

NetworkManager::~NetworkManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "NetworkManager instance destroyed.");
}

bool NetworkManager::Initialize()
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
  DLog(eLogType::cSuccess, "NetworkManager instance initialized.");
  return true;
}

bool NetworkManager::Terminate()
{
  // Class specific terminate


  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "NetworkManager instance terminated.");
  return true;
}

bool NetworkManager::InitializeScene([[maybe_unused]] Scene* pScene)
{

  return true;
}

void NetworkManager::ProcessScene([[maybe_unused]] dfloat deltaTime, [[maybe_unused]] Scene* pScene)
{

}
