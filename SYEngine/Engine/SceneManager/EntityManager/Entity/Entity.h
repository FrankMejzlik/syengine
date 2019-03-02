#pragma once

#include <unordered_map>
#include <memory>
#include <map>
#include <array>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "common.h"
#include "IEngineContextInterface.h"
#include "IGuidCounted.h"
#include "ISceneContextInterface.h"
#include "IComponentsInterface.h"
#include "PhysicsManager.h"
#include "Scene.h"
#include "ComponentManager.h"

namespace SYE 
{
class Collider;

class Component;
class Model;
class Scene;
class Transform;
class PhysicsBody;
class EntityManager;
class EngineContext;
class SceneContext;


/**
 * Base class for every entity that can be part of Scene.
 *
 * Every Entity MUST have pointer to it's ComponentManager instance.
 */
class Entity:
  public IGuidCounted, public IErrorLogging, 
  public IEngineContextInterface, public ISceneContextInterface,
  public IComponentsInterface
{
  // Structures
public:
  /**
   * Types of Entities
   *
   * WORLD is Entity placed in 3D Scenes.
   * SCREEN is Entity placed in 2D UiLayers.
   */
  enum eType
  {
    WORLD,
    SCREEN
  };


public:
  Entity() = delete;
  Entity(Scene* pOwnerScene, Entity* pParentEntity);
  virtual ~Entity() noexcept;

  Scene* GetOwnerScenePtr() const { return _pOwnerScene; }
  
  PhysicsBody* GetPhysicsBodyPtr() const;

  void SaveEntity();

  eType SetType(eType newValue);
  eType GetType() const;

  Entity* SetParent(Entity* newValue);
  Entity* GetParentPtr() const;
  void AddChild(Entity* pNewChild);
  void RemoveChild(Entity* pNewChild);
  const std::map<size_t, Entity*>& GetChildrenConstRef() const;

  void SetIsStatic(bool newValue) { _isStatic = newValue; }
  bool IsStatic() const { return _isStatic; }

  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& GetPrimaryComponentSlotsRef() { return _primaryComponentSlots; }

  template <typename ComponentType>
  ComponentType* AddComponent()
  {
    // Instantiate new Component
    ComponentType* pNewComponent = GetComponentManagerPtr()->CreateComponent<ComponentType>(this);
    
    // Try to attach it to this Entity
    bool result = AttachComponent<ComponentType>(pNewComponent);
    
    // If cannot attach to this Component
    if (!result)
    {
      PUSH_EDITOR_ERROR(
        eEngineError::AddingComponentToEntityFailed,
        "Adding Component '" + std::to_string(pNewComponent->GetGuid()) + "' to Entity '" + std::to_string(GetGuid()) + "' failed.",
        ""
      );

      // Destroy it
      GetComponentManagerPtr()->DestroyComponent(pNewComponent);
    }

    return pNewComponent;
  }
  bool RemoveComponent(Component* pComponentToDelete);

  template <typename EntityType>
  EntityType* AddEntity()
  {
    // Spawn new Entity
    EntityType* pNewEntity = GetEntityManagerPtr()->CreateEntity<EntityType>(_pOwnerScene, this);

    // Try to attach it to self
    if (!AttachEntity(pNewEntity))
    {
      PUSH_EDITOR_ERROR(
        eEngineError::AddingEntityToEntityFailed,
        "Adding Entity '" + pNewEntity->GetGuid() + "' to Entity '" + GetGuid() + "' failed.",
        ""
      );

      // Detroy this Entity
      GetEntityManagerPtr()->DestroyEntity(pNewEntity);

      return nullptr;
    }

    return pNewEntity;
  }
  bool RemoveEntity(Entity* pEntityToDelete);

protected:
  void EntityRefreshQuickRefs();

  template <typename ComponentType>
  ComponentType* AttachComponent(ComponentType* pNewComponent)
  {
    size_t slotIndex = pNewComponent->GetSlotIndex();
    bool isSingletonSlot = false;

    // Check if is singleton slot Component
    for (size_t i = 0; i < COMPONENT_SLOT_SINGLETONS_COUNT; ++i)
    {
      if (slotIndex == gSingletonSlots[i])
      {
        isSingletonSlot = true;
      }
    }

    // If singleton slot.
    if (isSingletonSlot)
    {
      // If there is some Component already
      if (_primaryComponentSlots[slotIndex].size() > 0)
      {
        PUSH_EDITOR_ERROR(
          eEngineError::AttachingMultipleSingletonSlotComponents,
          "Entity " + std::to_string(this->GetGuid()) + " cannot have more of " + std::to_string(slotIndex) + "slot index Components.",
          ""
        );

        return nullptr;
      }
    }
    // Insert it into your slot
    _primaryComponentSlots[slotIndex].insert(std::make_pair(pNewComponent->GetGuid(), pNewComponent));

    // Try to register this Component to Scene
    bool result = _pOwnerScene->RegisterComponent(pNewComponent);

    // If this component is already registered
    if (!result)
    {
      PUSH_EDITOR_ERROR(
        eEngineError::DuplicateComponentOnEntity,
        "Entity " + std::to_string(this->GetGuid()) + " already has Component with ID " + std::to_string(pNewComponent->GetGuid()),
        ""
      );

      return nullptr;
    }

    // Trigger refresh on all Components
    EntityRefreshQuickRefs();

    return static_cast<ComponentType*>(pNewComponent);
  }
  bool DetachComponent(Component* pComponent);

  bool AttachEntity(Entity* pEntity);
  bool DetachEntity(Entity* pEntity);


  // Attributes
protected:
  /** Scene instance this Entity belongs to */
  Scene* _pOwnerScene;

  /** 
   * Parent Entity 
   *
   * If 'nullptr' then this has no parent.
   */
  Entity* _pParentEntity;

  /** Child Entities */
  std::map<size_t, Entity*> _childEntities;

  /** If this Entity is not going to change during time */
  bool _isStatic;

  /** Type of this Entity. */
  eType _type;

  /** 
   * Table of active primary Components on this Entity 
   *
   * Indices of slots are configured at config_components.h.
   * Some slots are singletons, e.g. there can be only one light source per Component.
   */
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> _primaryComponentSlots;
  
};

} // namespace SYE