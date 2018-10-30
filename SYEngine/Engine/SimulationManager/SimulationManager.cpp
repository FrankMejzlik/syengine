
#include "SimulationManager.h"

SimulationManager::SimulationManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  /*_subModules.insert(std::make_pair(ID_AI_MANAGER, std::make_shared<AIManager>(this)));
  _subModules.insert(std::make_pair(ID_LOGIC_MANAGER, std::make_shared<LogicManager>(this)));
  _subModules.insert(std::make_pair(ID_PHYSICS_MANAGER, std::make_shared<PhysicsManager>(this)));*/

  DLog(eLogType::Success, "SimulationManager instance created.");
}

SimulationManager::~SimulationManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "SimulationManager instance destroyed.");
}

bool SimulationManager::Initialize()
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

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "SimulationManager instance initialized.");
  return true;
}

bool SimulationManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "SimulationManager instance terminated.");
  return true;
}

void SimulationManager::ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene)
{}