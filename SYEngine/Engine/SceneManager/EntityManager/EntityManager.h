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

  EntityManager(BaseModule &parentModule);
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
  Entity* CreateEntity(Scene* pOwnerScene);


protected:
private:
  Entity* InsertEntity(std::unique_ptr<Entity>&& pNewEntity);


private:
  std::map<size_t, std::unique_ptr<Entity>> _entities;


};

}