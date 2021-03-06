
#include "AiManager.h"

#include "Scene.h"

using namespace SYE;

AiManager::AiManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::cSuccess, "\t AiManager instance created.");
}

AiManager::~AiManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "\t AiManager instance destroyed.");
}

bool AiManager::Initialize()
{
  // Initialize submodules.
  for (auto it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }
  // Class specific initialization

  SetModuleState(eModuleState::OK);
  DLog(eLogType::cSuccess, "\t AiManager instance initialized.");
  return true;
}

bool AiManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "\t AiManager instance terminated.");
  return true;
}

bool AiManager::InitializeScene([[maybe_unused]] Scene * pScene)
{

  return true;
}

void AiManager::ProcessScene([[maybe_unused]] dfloat deltaTime, [[maybe_unused]] Scene* pScene)
{

  //LOG_NOT_IMPLEMENTED;
}