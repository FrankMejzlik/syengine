
#include "SimulationManager.h"

SimulationManager::SimulationManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_PHYSICS_MANAGER, std::make_unique<PhysicsManager>(*this, _pEngineContext)));

  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::cSuccess, "SimulationManager instance created.");
}

SimulationManager::~SimulationManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "SimulationManager instance destroyed.");
}

bool SimulationManager::Initialize()
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

  SetModuleState(eModuleState::OK);
  DLog(eLogType::cSuccess, "SimulationManager instance initialized.");
  return true;
}

bool SimulationManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "SimulationManager instance terminated.");
  return true;
}

bool SimulationManager::InitializeScene(Scene* pScene)
{
  bool result = true;

  result = result && PHYSICS_MANAGER->InitializeScene(pScene);

  return result;
}

void SimulationManager::ProcessScene(dfloat deltaTime, Scene* pScene)
{

  // Construct physics scene.
  PHYSICS_MANAGER->ProcessScene(deltaTime, pScene);


}
