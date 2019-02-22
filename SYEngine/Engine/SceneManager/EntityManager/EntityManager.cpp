#include "EntityManager.h"

using namespace SYE;

EntityManager::EntityManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  _subModules.insert(std::make_pair(ID_COMPONENT_MANAGER, std::make_unique<ComponentManager>(*this)));

  DLog(eLogType::Success, "\t EntityManager instance created.");
}

EntityManager::~EntityManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t EntityManager instance destroyed.");
}

bool EntityManager::Initialize()
{

  // Class specific initialization

  // Initialize submodules.
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  SetModuleState(eModuleState::OK);
  DLog(eLogType::Success, "\t EntityManager instance initialized.");
  return true;
}

bool EntityManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t EntityManager instance terminated.");
  return true;
}

Entity* EntityManager::CreateEntity(Scene* pOwnerScene)
{
  // Instantiate new Entity
  std::unique_ptr<Entity> newEntity = std::make_unique<Entity>(pOwnerScene, COMPONENT_MANAGER);

  return InsertEntity(std::move(newEntity));
}

Entity* EntityManager::InsertEntity(std::unique_ptr<Entity>&& pNewEntity)
{
  auto result = _entities.insert(std::make_pair(pNewEntity->GetGuid(), std::move(pNewEntity)));

  return result.first->second.get();
}
