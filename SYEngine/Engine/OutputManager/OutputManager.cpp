#include "OutputManager.h"

OutputManager::OutputManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_RENDERING_MANAGER, std::make_unique<RenderingManager>(*this)));
  

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

bool OutputManager::Initialize()
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

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "OutputManager instance initialized.");
  return true;
}

bool OutputManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "OutputManager instance terminated.");
  return true;
}


void OutputManager::ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene, std::shared_ptr<Window> pTargetWindow)
{
  RENDERING_MANAGER->RenderScene(pScene, pTargetWindow);
}

std::shared_ptr<Window> OutputManager::ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height)
{
  return RENDERING_MANAGER->ConstructWindow(windowType, windowTitle, width, height);
}