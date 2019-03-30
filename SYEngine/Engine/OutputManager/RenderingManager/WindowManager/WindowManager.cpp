#include "WindowManager.h"


WindowManager::WindowManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::cSuccess, "\t\t WindowManager instance created.");
}

WindowManager::~WindowManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "\t\t WindowManager instance destroyed.");
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
  DLog(eLogType::cSuccess, "\t\t WindowManager instance initialized.");
  return true;
}

bool WindowManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "\t\t WindowManager instance terminated.");
  return true;
}


Window* WindowManager::ConstructWindow(eWindowType windowType, std::string_view windowTitle, size_t width, size_t height)
{
  UNREFERENCED_PARAMETER(windowTitle);
  UNREFERENCED_PARAMETER(height);
  UNREFERENCED_PARAMETER(width);
  UNREFERENCED_PARAMETER(windowType);

  // Instantiate new Window 
  std::unique_ptr<Window> pWindow = std::make_unique<Window>(GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT);

  // Try initializing this window
  int initResult = pWindow->Initialize();
  // Handle errors
  if (initResult > 0)
  { 
    PUSH_ENGINE_ERROR(
      eEngineError::WindowInitialilzationFailed,
      "Window '" + std::to_string(pWindow->GetGuid()) + "' initialization failed.",
      ""
    );

    return nullptr;
  }

  // Insert this Window into table
  auto result = _windows.insert(std::make_pair(pWindow->GetGuid(), std::move(pWindow)));
  
  // Return pointer to new Window
  return result.first->second.get();
}

bool WindowManager::DestroyWindow(Window* pWindow)
{
  // Remove this Window from table
  auto result = _windows.erase(pWindow->GetGuid());
  
  return (result > 0);
}
