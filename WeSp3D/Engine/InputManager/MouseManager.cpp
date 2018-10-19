#include "MouseManager.h"

using namespace WeSp;

MouseManager::MouseManager(InputManager* pParentInstance):
  IInputManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t MouseManager instance created.");
}

MouseManager::~MouseManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t MouseManager instance destroyed.");
}

bool MouseManager::Initialize(std::map<int, std::shared_ptr<IInputManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!IInputManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in MouseManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t MouseManager instance initialized.");
  return true;
}

bool MouseManager::Terminate()
{
  // Class specific terminate

  if (!IInputManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of MouseManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t MouseManager instance terminated.");
  return true;
}