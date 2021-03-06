#include "OutputManager.h"

OutputManager::OutputManager(BaseModule &parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_RENDERING_MANAGER, std::make_unique<RenderingManager>(*this, _pEngineContext)));
  
  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::cSuccess, "OutputManager instance created.");
}

OutputManager::~OutputManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "OutputManager instance destroyed.");
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

  SetModuleState(eModuleState::OK);
  DLog(eLogType::cSuccess, "OutputManager instance initialized.");
  return true;
}

bool OutputManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "OutputManager instance terminated.");
  return true;
}


bool OutputManager::InitializeScene([[maybe_unused]] Scene* pScene)
{


  RENDERING_MANAGER->InitializeScene(pScene);

  return true;
}

void OutputManager::ProcessScene([[maybe_unused]] dfloat deltaTime, Scene* pScene, Window* pTargetWindow)
{
  RENDERING_MANAGER->RenderScene(pScene, pTargetWindow);
}

Window* OutputManager::ConstructWindow(eWindowType windowType, std::string_view windowTitle, size_t width, size_t height)
{
  return RENDERING_MANAGER->ConstructWindow(windowType, windowTitle, width, height);
}

bool OutputManager::DestroyWindow(Window* pWindow)
{
  return RENDERING_MANAGER->DestroyWindow(pWindow);
}