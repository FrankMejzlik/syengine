#include "Entity.h"
#include "Collider.h"
#include "Scene.h"

#include "PhysicsBody.h"
#include "EntityManager.h"

using namespace SYE;

Entity::Entity(Scene* pOwnerScene, EntityManager* pEntityManager, ComponentManager* pComponentManager) noexcept :
  _pParent(nullptr),
  _pEntityManager(pEntityManager),
  _pOwnerScene(pOwnerScene),
  _isStatic(true),
  _pComponentManager(pComponentManager),
  _type(Entity::eType::WORLD)
{
  // Enlist self in owner Scene
  _pOwnerScene->EnlistEntity(this);
}

Entity::~Entity()
{
  // Destroy all children Entities
  for (auto&& childPair : _children)
  {
    _pEntityManager->DestroyEntity(childPair.second);
  }

  // Destroy all Components that it owns
  for (auto&& componentPair : _components)
  {
    _pComponentManager->DestroyComponent(componentPair.second);
  }

  // Delist self from owning scene
  _pOwnerScene->DelistEntity(this);

}

ComponentManager* Entity::GetComponentManagerPtr()
{
  return _pComponentManager;
}


bool Entity::EnlistComponent(Component* pComponent)
{
  auto newPair = std::make_pair(pComponent->GetGuid(), pComponent);

  _primaryComponentSlots[pComponent->GetSlotIndex()].insert(newPair);

  // Try inserting it in its place to correct slot index
  auto result = _components.insert(newPair);

  if (result.second == false)
  {
    return false;
  }

  return false;
}

bool Entity::DelistComponent(Component* pComponent)
{
  // Delist it from Scene first
  _pOwnerScene->DelistComponent(pComponent);

  auto result = _components.erase(pComponent->GetGuid());
  
  _primaryComponentSlots[pComponent->GetSlotIndex()].erase(pComponent->GetGuid());

  return (result > 0);
}

PhysicsBody* Entity::GetPhysicsBodyPtr() const
{
  // Try to find this Component
  auto result = _primaryComponentSlots[COMPONENT_PHYSICS_BODY_SLOT].begin();

  // If item NOT found
  if (result == _primaryComponentSlots[COMPONENT_PHYSICS_BODY_SLOT].end())
  {
    return nullptr;
  }

  return static_cast<PhysicsBody*>(result->second);
}

PhysicsManager* Entity::GetPhysicsManager()
{
  return _pOwnerScene->GetPhysicsManagerPtr();
}

Entity::eType Entity::SetType(eType newValue)
{
  Entity::eType oldType = _type;
  _type = newValue;

  return oldType;
}

Entity::eType Entity::GetType() const
{
  return _type;
}

Entity* Entity::SetParent(Entity* newValue)
{
  Entity* oldParent = _pParent;
   _pParent = newValue;

  return oldParent;
}

Entity* Entity::GetParentPtr() const 
{ 
  return _pParent; 
}

void Entity::AddChild(Entity* pNewChild)
{
  _children.insert(std::pair(pNewChild->GetGuid(), pNewChild));
}

void Entity::RemoveChild(Entity* pNewChild)
{
  _children.erase(pNewChild->GetGuid());
}

const std::map<size_t, Entity*> Entity::GetChildren() const 
{ 
  return _children; 
}

void Entity::RefreshComponents()
{
  for (auto&& component : _components)
  {
    component.second->Refresh();
  }
}

