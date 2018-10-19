#include "AIManager.h"

using namespace WeSp;

AIManager::AIManager(SimulationManager* pParentInstance):
  ISimulationManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t AIManager instance created.");
}

AIManager::~AIManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t AIManager instance destroyed.");
}

bool AIManager::Initialize(std::map<int, std::shared_ptr<ISimulationManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!ISimulationManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in AIManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t AIManager instance initialized.");
  return true;
}

bool AIManager::Terminate()
{
  // Class specific terminate

  if (!ISimulationManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of AIManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t AIManager instance terminated.");
  return true;
}