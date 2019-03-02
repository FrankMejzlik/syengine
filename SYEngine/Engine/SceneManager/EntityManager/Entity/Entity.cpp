#include "Entity.h"
#include "Collider.h"
#include "Scene.h"

#include "PhysicsBody.h"
#include "EntityManager.h"

using namespace SYE;

Entity::Entity(Scene* pOwnerScene, Entity* pParentEntity):
  IEngineContextInterface(pOwnerScene->GetEngineContextPtr()),
  ISceneContextInterface(pOwnerScene->GetSceneContextPtr()),
  IComponentsInterface(_primaryComponentSlots),
  _pOwnerScene(pOwnerScene),
  _pParentEntity(pParentEntity),
  _isStatic(true),
  _type(Entity::eType::WORLD)
{}

Entity::~Entity() noexcept
{
  // Delete all children Entities recursively
  for (auto&& childPair : _childEntities)
  {
    RemoveEntity(childPair.second);
  }

  // Destroy all child Component recursively
  for (auto&& slotMap : _primaryComponentSlots)
  {
    for (auto&& componentPair : slotMap)
    {
      RemoveComponent(componentPair.second);
    }
  }
}

bool Entity::DetachComponent(Component* pComponent)
{
  // Delist it from Scene first
  _pOwnerScene->UnregisterComponent(pComponent);

  // Remove it from slot
  auto result = _primaryComponentSlots[pComponent->GetSlotIndex()].erase(pComponent->GetGuid());

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

void Entity::SaveEntity()
{
  // Update Entity refs
  EntityRefreshQuickRefs();
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
  Entity* oldParent = _pParentEntity;
   _pParentEntity = newValue;

  return oldParent;
}

Entity* Entity::GetParentPtr() const 
{ 
  return _pParentEntity; 
}

void Entity::AddChild(Entity* pNewChild)
{
  _childEntities.insert(std::pair(pNewChild->GetGuid(), pNewChild));
}

void Entity::RemoveChild(Entity* pNewChild)
{
  _childEntities.erase(pNewChild->GetGuid());
}

const std::map<size_t, Entity*>& Entity::GetChildrenConstRef() const 
{ 
  return _childEntities; 
}

bool Entity::RemoveComponent(Component* pComponentToDelete)
{
  // Detach it from Entity
  if (!DetachComponent(pComponentToDelete))
  {
    PUSH_EDITOR_ERROR(
      eEngineError::TryingToDeleteNonExistentEntityFromScene,
      "This Component '" + std::to_string(pComponentToDelete->GetGuid()) + "' does not exist on Entity '" + std::to_string(GetGuid()) + "' and thus cannot be deleted.",
      ""
    );

    return false;
  }

  // Tell EntityManager to destroy it
  bool result = GetComponentManagerPtr()->DestroyComponent(pComponentToDelete);
  if (!result)
  {
    PUSH_EDITOR_ERROR(
      eEngineError::UnableToDeleteComponentBecauseDestructionFailed,
      "This Component '" + std::to_string(pComponentToDelete->GetGuid()) + "' is detached from Entity  '" + std::to_string(GetGuid()) + "' but destruction failed. It is still allocated.",
      ""
    );
  }

  return true;
}

bool Entity::RemoveEntity(Entity* pEntityToDelete)
{
  // Detach it from Scene
  if (!DetachEntity(pEntityToDelete))
  {
    PUSH_EDITOR_ERROR(
      eEngineError::TryingToDeleteNonExistentEntityFromEntity,
      "This Entity '" + std::to_string(pEntityToDelete->GetGuid()) + "' does not exist on Entity '" + std::to_string(GetGuid()) + "' and thus cannot be deleted.",
      ""
    );

    return false;
  }

  // Tell EntityManager to destroy it
  bool result = GetEntityManagerPtr()->DestroyEntity(pEntityToDelete);
  if (!result)
  {
    PUSH_EDITOR_ERROR(
      eEngineError::UnableToDeleteEntityBecauseDestructionFailed,
      "This Entity '" + std::to_string(pEntityToDelete->GetGuid()) + "' is detached from Scene '" + std::to_string(GetGuid()) + "' but destruction failed. It is still allocated.",
      ""
    );
  }

  return true;
}

void Entity::EntityRefreshQuickRefs()
{
  // Refresh your refs
  RefreshQuickRefs();

  // Iterate through slots
  for (auto&& slotMap : _primaryComponentSlots)
  {
    // Iterate through Components in each slot
    for (auto&& component : slotMap)
    {
      component.second->RefreshQuickRefs();
    }
  }
}


bool Entity::AttachEntity(Entity* pEntity)
{
  // Insert it there
  auto result = _childEntities.insert(std::make_pair(pEntity->GetGuid(), pEntity));

  // If already existed
  if (result.second == false)
  {
    PUSH_EDITOR_ERROR(
      eEngineError::AttachingAlreadyExistingEntityToEntity,
      "This Entity '" + std::to_string(pEntity->GetGuid()) + "' is already attached to Entity instance with ID '" + std::to_string(GetGuid()) + "'.",
      ""
    );

    return false;
  }

  return true;
}

bool Entity::DetachEntity(Entity* pEntity)
{
  auto result = _childEntities.erase(pEntity->GetGuid());

  return (result > 0);
}
