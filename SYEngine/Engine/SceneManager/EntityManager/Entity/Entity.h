#pragma once

#include <unordered_map>
#include <memory>
#include <map>
#include <array>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "config_components.h"
#include "common.h"
#include "IGuidCounted.h"

#include "ComponentManager.h"

namespace SYE 
{
class Collider;

class Component;
class Model;
class Scene;
class Transform;


/**
 * Base class for every entity that can be part of Scene.
 *
 * Every Entity MUST have pointer to it's ComponentManager instance.
 */
class Entity:
  public IGuidCounted, public IErrorLogging
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

  Entity(Scene* pOwnerScene, ComponentManager* pComponentManager) noexcept;

  virtual ~Entity();

  ComponentManager* GetComponentManagerPtr();
  Scene* GetOwnerScenePtr() const { return _pOwnerScene; }
  
  eType SetType(eType newValue);
  eType GetType() const;

  Entity* SetParent(Entity* newValue);
  Entity* GetParentPtr() const;
  void AddChild(Entity* pNewChild);
  void RemoveChild(Entity* pNewChild);
  const std::map<size_t, Entity*> GetChildren() const;

  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& GetPrimaryComponentSlotsRef() { return _primaryComponentSlots; }

  template <typename ComponentType>
  ComponentType* AddComponent()
  {
    ComponentType* pNewComponent = _pComponentManager->CreateComponent<ComponentType>(this);
    
    // Try to attach it to this Entity
    ComponentType* resultPtr = AttachComponent<ComponentType>(pNewComponent);
    
    // If cannot attach to this Component
    if (resultPtr == nullptr)
    {
      // Destroy it
      _pComponentManager->RemoveComponent(pNewComponent);
    }

    // If attached, enlist it in active components in scene in order to be processed
    _pOwnerScene->EnlistComponent(pNewComponent);

    // Trigger refresh on all Components
    RefreshComponents();

    return pNewComponent;
  }

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

    bool isDuplicate = false;
    auto newPair = std::make_pair(pNewComponent->GetGuid(), pNewComponent);

    // Try inserting it in its place to correct slot index
    auto result = _primaryComponentSlots[slotIndex].insert(newPair);
    if (result.second == false)
    {
      isDuplicate = true;
    }

    // Insert it into list of all Components that this Entity owns
    result = _components.insert(newPair);
    if (result.second == false)
    {
      isDuplicate = true;
    }

    // If was duplicate in some list, something is not right
    if (isDuplicate)
    {
      PUSH_EDITOR_ERROR(
        eEngineError::DuplicateComponentOnEntity,
        "Entity " + std::to_string(this->GetGuid()) + " already has Component with ID " + std::to_string(pNewComponent->GetGuid()),
        ""
      );
    } 

    return static_cast<ComponentType*>(&(*(result.first->second)));
  }

protected:
  void RefreshComponents();


  // Attributes
protected:
  

  /** Pointer to ComponentManager that is dedicated for this Entity. */
  ComponentManager* _pComponentManager;
  Scene* _pOwnerScene;

  /** Type of this Entity. */
  eType _type;

  /** 
   * Parent Entity 
   *
   * If 'nullptr' then this has no parent.
   */
  Entity* _pParent;

  /** Child Entities */
  std::map<size_t, Entity*> _children;

  /** 
   * Table of active primary Components on this Entity 
   *
   * Indices of slots are configured at config_components.h.
   * Some slots are singletons, e.g. there can be only one light source per Component.
   */
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> _primaryComponentSlots;

  /** List of all components on this Entity */
  std::map<size_t, Component*> _components;
  
#if !NEW_SSSEC_IMPLEMENTED
public:

  Entity(
    ComponentManager* pComponentManager,
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector
  ) noexcept;

  std::string _name;
  bool _bIsToRender;
  bool _bHasColliders;
  void SetBIsToRender(const bool newValue);
  bool GetBIsToRender() const;

  bool GetBHasColliders() const { return _bHasColliders; };

  Collider* AddCollider(Collider* pNewCollider);
  bool DeleteCollider(Collider* pNewCollider);

  const std::unordered_map<size_t, Collider*> &GetColliders() const;


  void SetEntityName(std::string_view name);
  std::string GetEntityName() const;
  glm::vec3 GetPositionVector() const;
  bool SetPositionVector(const glm::vec3 positionVector);
  glm::vec3 GetRotationVector() const;;
  bool SetRotationVector(const glm::vec3 rotationVector);
  glm::vec3 GetScaleVector() const;
  bool SetScaleVector(const glm::vec3 scaleVector);
  const glm::vec3& GetPositionVectorRefConst() const;
  const glm::vec3& GetRotationVectorRefConst() const;
  const glm::vec3& GetScaleVectorRefConst() const;


  // Position relative to origin in world
  glm::vec3 _positionVector;
  // Rotation angles in radians by particular axes
  glm::vec3 _rotationVector;
  // Scale factor for every direction
  glm::vec3 _scaleVector;

  /** All components attached to this Entity */
  std::map<std::string, Component*> _componentList;
  std::map<std::string, Model*> _modelsToRenderList;
  std::unordered_map<size_t, Collider*> _colliders;
  Component* _pModel;

  Component* GetModel() const { return _pModel; };

#endif



};

} // namespace SYE