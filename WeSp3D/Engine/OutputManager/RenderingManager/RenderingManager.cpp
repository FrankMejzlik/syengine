#include "RenderingManager.h"

using namespace WeSp;

RenderingManager::RenderingManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Add submodules for this module.
  _subModules.insert(std::make_pair(ID_WINDOW_MANAGER, std::make_shared<WindowManager>(*this)));
  
  DLog(eLogType::Success, "RenderingManager instance created.");
}

RenderingManager::~RenderingManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "RenderingManager instance destroyed.");
}

bool RenderingManager::Initialize()
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
  DLog(eLogType::Success, "RenderingManager instance initialized.");
  return true;
}

bool RenderingManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "RenderingManager instance terminated.");
  return true;
}

std::shared_ptr<Window> WeSp::RenderingManager::ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height)
{
  return WINDOW_MANAGER->ConstructWindow(windowType, windowTitle, width, height);
}
