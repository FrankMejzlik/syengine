#include "WindowManager.h"


WindowManager::WindowManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
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
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization

  SetModuleState(eModuleState::OK);
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


Window* WindowManager::ConstructWindow(eWindowType windowType, std::string_view windowTitle, size_t width, size_t height)
{
  UNREFERENCED_PARAMETER(windowTitle);
  UNREFERENCED_PARAMETER(height);
  UNREFERENCED_PARAMETER(width);
  UNREFERENCED_PARAMETER(windowType);

  // Construct new Window instance and push it into vector.
  _windows.push_back(std::make_unique<Window>(GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT));

  // Get new window ptr.
  Window* newWindow = _windows.back().get();
  newWindow->Initialize();

  return newWindow;
}