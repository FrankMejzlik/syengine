#include "InputManager.h"

InputManager::InputManager(Engine* pParentInstance):
  IMainEngineModule(pParentInstance)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_KEYBOARD_MANAGER, std::make_shared<KeyboardManager>(this)));
  _subModules.insert(std::make_pair(ID_MOUSE_MANAGER, std::make_shared<MouseManager>(this)));
  _subModules.insert(std::make_pair(ID_CONTROLLER_MANAGER, std::make_shared<ControllerManager>(this)));

  DLog(eLogType::Success, "InputManager instance created.");
}

InputManager::~InputManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "InputManager instance destroyed.");
}

bool InputManager::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // Call parent Initialize method
  if (!IMainEngineModule::Initialize(modules))
  {
    DLog(eLogType::Error, "Initialization of base Initialize in InputManager failed.");
    return false;
  }

  // Class specific initialization
  // -- Goes here
  // Class specific initialization

  // Initialize submodules
  for (std::map<int, std::shared_ptr<IInputManagerSubmodule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize(_subModules);
  }

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "InputManager instance initialized.");
  return true;
}

bool InputManager::Terminate()
{
  // Class specific terminate

  if (!IMainEngineModule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "Error terminating base of EntitiManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "InputManager instance terminated.");
  return true;
}