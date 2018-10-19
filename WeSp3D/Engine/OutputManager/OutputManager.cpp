#include "OutputManager.h"

OutputManager::OutputManager(Engine* pParentInstance):
  IMainEngineModule(pParentInstance)
{
  DLog(eLogType::Success, "OutputManager instance created.");
}

OutputManager::~OutputManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "OutputManager instance destroyed.");
}

bool OutputManager::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // Call parent Initialize method
  if (!IMainEngineModule::Initialize(modules))
  {
    DLog(eLogType::Error, "Initialization of base Initialize in OutputManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "OutputManager instance initialized.");
  return true;
}

bool OutputManager::Terminate()
{
  // Class specific terminate

  if (!IMainEngineModule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "Error terminating base of EntitiManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "OutputManager instance terminated.");
  return true;
}