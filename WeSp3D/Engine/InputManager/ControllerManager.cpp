#include "ControllerManager.h"

using namespace WeSp;

ControllerManager::ControllerManager(InputManager* pParentInstance):
  IInputManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t ControllerManager instance created.");
}

ControllerManager::~ControllerManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t ControllerManager instance destroyed.");
}

bool ControllerManager::Initialize(std::map<int, std::shared_ptr<IInputManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!IInputManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in ControllerManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t ControllerManager instance initialized.");
  return true;
}

bool ControllerManager::Terminate()
{
  // Class specific terminate

  if (!IInputManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of ControllerManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t ControllerManager instance terminated.");
  return true;
}