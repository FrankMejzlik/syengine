
#include "SimulationManager.h"

SimulationManager::SimulationManager(Engine* pParentInstance):
  IMainEngineModule(pParentInstance)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_AI_MANAGER, std::make_shared<AIManager>(this)));
  _subModules.insert(std::make_pair(ID_LOGIC_MANAGER, std::make_shared<LogicManager>(this)));
  _subModules.insert(std::make_pair(ID_PHYSICS_MANAGER, std::make_shared<PhysicsManager>(this)));

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

bool SimulationManager::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // Call parent Initialize method
  if (!IMainEngineModule::Initialize(modules))
  {
    DLog(eLogType::Error, "Initialization of base Initialize in SimulationManager failed.");
    return false;
  }

  // Class specific initialization
  // -- Goes here
  // Class specific initialization

  // Initialize submodules
  for (std::map<int, std::shared_ptr<ISimulationManagerSubmodule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize(_subModules);
  }

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "SimulationManager instance initialized.");
  return true;
}

bool SimulationManager::Terminate()
{
  // Class specific terminate

  if (!IMainEngineModule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "Error terminating base of EntitiManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "SimulationManager instance terminated.");
  return true;
}