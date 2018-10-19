#include "KeyboardManager.h"

using namespace WeSp;

KeyboardManager::KeyboardManager(InputManager* pParentInstance):
  IInputManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t KeyboardManager instance created.");
}

KeyboardManager::~KeyboardManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t KeyboardManager instance destroyed.");
}

bool KeyboardManager::Initialize(std::map<int, std::shared_ptr<IInputManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!IInputManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in KeyboardManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t KeyboardManager instance initialized.");
  return true;
}

bool KeyboardManager::Terminate()
{
  // Class specific terminate

  if (!IInputManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of KeyboardManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t KeyboardManager instance terminated.");
  return true;
}