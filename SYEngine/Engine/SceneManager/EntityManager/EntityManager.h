#pragma once

#include "common.h"
#include "BaseModule.h"

#include "ComponentManager.h"
#include "Entity.h"

using namespace SYE;

namespace SYE 
{

class Scene;

class EntityManager :
  public BaseModule
{
public:
  EntityManager() = delete;

  EntityManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~EntityManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  /**
   * Create empty new Entity instance
   *
   * New Entity instance is created. Entity is then
   * capable of attaching PRIMARY Components to itself.
   *
   * Entity can be either of type WORLD or SCREEN.
   * @param   Scene*    Pointer to Scene instance that will own this Entity.
   * @return  Entity*   Observer pointer to new Entity instance.
   *
   * @see   class Entity
   * @see   class ComponentManager
   * @see   class Component
   */
  template <typename EntityType>
  EntityType* CreateEntity(Scene* pOwnerScene, Entity* pParentEntity = nullptr)
  {
    // Instantiate new Entity
    std::unique_ptr<EntityType> newEntity = std::make_unique<EntityType>(pOwnerScene, pParentEntity);

    return InsertEntity(std::move(newEntity));
  }

  bool DestroyEntity(Entity* pEntity);


protected:
private:
  template <typename EntityType>
  EntityType* InsertEntity(std::unique_ptr<EntityType>&& pNewEntity)
  {
    auto result = _entities.insert(std::make_pair(pNewEntity->GetGuid(), std::move(pNewEntity)));

    return result.first->second.get();
  }

private:
  std::map<size_t, std::unique_ptr<Entity>> _entities;


};

}