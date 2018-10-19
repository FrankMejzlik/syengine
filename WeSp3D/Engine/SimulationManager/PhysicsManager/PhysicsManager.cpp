#include "PhysicsManager.h"

using namespace WeSp;

PhysicsManager::PhysicsManager(SimulationManager* pParentInstance):
  ISimulationManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t PhysicsManager instance created.");
}

PhysicsManager::~PhysicsManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t PhysicsManager instance destroyed.");
}

bool PhysicsManager::Initialize(std::map<int, std::shared_ptr<ISimulationManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!ISimulationManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in PhysicsManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t PhysicsManager instance initialized.");
  return true;
}

bool PhysicsManager::Terminate()
{
  // Class specific terminate

  if (!ISimulationManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of PhysicsManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t PhysicsManager instance terminated.");
  return true;
}