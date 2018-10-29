#include "WindowManager.h"


WindowManager::WindowManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  //_subModules.insert(std::make_pair(ID_AI_MANAGER, std::make_shared<AIManager>(this)));
  //_subModules.insert(std::make_pair(ID_LOGIC_MANAGER, std::make_shared<LogicManager>(this)));

  DLog(eLogType::Success, "\t\t WindowManager instance created.");
}

WindowManager::~WindowManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t\t WindowManager instance destroyed.");
}

bool WindowManager::Initialize()
{
  // Initialize submodules.
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t\t WindowManager instance initialized.");
  return true;
}

bool WindowManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t\t WindowManager instance terminated.");
  return true;
}


std::shared_ptr<Window> WindowManager::ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height)
{
  // Construct new Window instance and push it into vector.
  _activeWindows.push_back(std::make_shared<Window>(nullptr, GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT));
  // Get new
  std::shared_ptr<Window> newWindow = _activeWindows.back();
  newWindow->Initialize();

  return newWindow;
}