#include "EntityManager.h"

using namespace WeSp;

EntityManager::EntityManager(Engine* pParentInstance):
  IMainEngineModule(pParentInstance)
{
  DLog(eLogType::Success, "EntityManager instance created.");
}

EntityManager::~EntityManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "EntityManager instance destroyed.");
}

bool EntityManager::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // Call parent Initialize method
  if (!IMainEngineModule::Initialize(modules))
  {
    DLog(eLogType::Error, "Initialization of base Initialize in EntityManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "EntityManager instance initialized.");
  return true;
}

bool EntityManager::Terminate()
{
  // Class specific terminate

  if (!IMainEngineModule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "Error terminating base of EntitiManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "EntityManager instance terminated.");
  return true;
}

