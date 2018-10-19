#include "LogicManager.h"

using namespace WeSp;

LogicManager::LogicManager(SimulationManager* pParentInstance):
  ISimulationManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t LogicManager instance created.");
}

LogicManager::~LogicManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t LogicManager instance destroyed.");
}

bool LogicManager::Initialize(std::map<int, std::shared_ptr<ISimulationManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!ISimulationManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in LogicManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t LogicManager instance initialized.");
  return true;
}

bool LogicManager::Terminate()
{
  // Class specific terminate

  if (!ISimulationManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of LogicManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t LogicManager instance terminated.");
  return true;
}