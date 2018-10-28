#include "LogicManager.h"

using namespace WeSp;

LogicManager::LogicManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  DLog(eLogType::Success, "\t LogicManager instance created.");
}

LogicManager::~LogicManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t LogicManager instance destroyed.");
}

bool LogicManager::Initialize()
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
  DLog(eLogType::Success, "\t LogicManager instance initialized.");
  return true;
}

bool LogicManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t LogicManager instance terminated.");
  return true;
}

void LogicManager::ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene)
{}
