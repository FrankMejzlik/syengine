#include "InputManager.h"

InputManager::InputManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
 /* _subModules.insert(std::make_pair(ID_KEYBOARD_MANAGER, std::make_shared<KeyboardManager>(*this)));
  _subModules.insert(std::make_pair(ID_MOUSE_MANAGER, std::make_shared<MouseManager>(*this)));
  _subModules.insert(std::make_pair(ID_CONTROLLER_MANAGER, std::make_shared<ControllerManager>(*this)));
*/
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

bool InputManager::Initialize()
{

  // Class specific initialization
  // -- Goes here
  // Class specific initialization

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
  DLog(eLogType::Success, "InputManager instance initialized.");
  return true;
}

bool InputManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "InputManager instance terminated.");
  return true;
}