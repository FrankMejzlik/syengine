
#include "AiManager.h"

#include "Scene.h"

using namespace SYE;

AiManager::AiManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  DLog(eLogType::Success, "\t AiManager instance created.");
}

AiManager::~AiManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t AiManager instance destroyed.");
}

bool AiManager::Initialize()
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
  DLog(eLogType::Success, "\t AiManager instance initialized.");
  return true;
}

bool AiManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t AiManager instance terminated.");
  return true;
}

void AiManager::InitializeScene(Scene * pScene)
{
  UNREFERENCED_PARAMETER(pScene);
  
  LOG_NOT_IMPLEMENTED;
}

void AiManager::ProcessScene(dfloat deltaTime, Scene* pScene)
{
  UNREFERENCED_PARAMETER(deltaTime);
  UNREFERENCED_PARAMETER(pScene);

  //LOG_NOT_IMPLEMENTED;
}