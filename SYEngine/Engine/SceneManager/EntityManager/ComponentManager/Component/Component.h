#pragma once

#include <memory>
#include <vector>
#include <map>

#include "common.h"
#include "IEngineContextInterface.h"
#include "IComponentsInterface.h"
#include "ISceneContextInterface.h"
#include "IGuidCounted.h"
#include "IErrorLogging.h"
#include "BaseModule.h"
#include "MathLibrary.h"


namespace SYE
{

class Scene;
class Entity;
class ComponentManager;
class PhysicsManager;

class Component:
  public IGuidCounted, public IErrorLogging, 
  public IEngineContextInterface, public ISceneContextInterface,
  public IComponentsInterface
{
public:
  enum class eType
  {
    TRANSFORM = 10,
    COMPONENT = 20,
    LOGIC = 30,
    MESH = 40,
    MODEL = 50,
    SKELETAL_MODEL = 60,
    SHADER = 70,
    COLLIDER = 80,
    BLOCK_COLLIDER = 90,
    SPHERE_COLLIDER = 100,
    CAPSULE_COLLIDER = 101,
    CONVEX_HULL_COLLIDER = 102,
    MATERIAL = 110,
    SHININESS = 111,
    BASIC_MATERIAL = 112,
    TEXTURE = 120,
    MESH_RENDERER = 130,
    PHYSICS_BODY = 139,
    RIGID_BODY = 140,
    SOFT_BODY = 141,
    PHYSICS_MATERIAL = 150,
    SKYBOX = 160,
    SOUND = 170,
    CAMERA = 180,
    NUM_TYPES = 190,
    LIGHT = 200,
    DIRECTIONAL_LIGHT = 210,
    POINT_LIGHT = 220,
    SPOT_LIGHT = 230,
    SCRIPT_HANDLER = 231,
    SCRIPT = 240
  };

  enum eSlotIndex
  {
    UNDEFINED = 0,
    TRANSFORM = COMPONENT_TRANSFORM_SLOT,
    DIRECTIONAL_LIGHT_SOURCE = COMPONENT_DIRECTIONAL_LIGHT_SOURCE_SLOT,
    POINT_LIGHT_SOURCE = COMPONENT_POINT_LIGHT_SOURCE_SLOT,
    SPOT_LIGHT_SOURCE = COMPONENT_SPOT_LIGHT_SOURCE_SLOT,
    SCRIPT_HANDLER = COMPONENT_SCRIPT_HANDLER_SLOT,
    CAMERA = COMPONENT_CAMERA_SLOT,
    PHYSICS_BODY = COMPONENT_PHYSICS_BODY_SLOT,
    PHYSICS_COLLIDER = COMPONENT_PHYSICS_COLLIDER_SLOT,
    MESH_RENDERER = COMPONENT_MESH_RENDERER_SLOT
  };

public:
  Component() = delete;
  Component(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    bool isPrimary = true, bool isActive = true,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::COMPONENT
  );
  ~Component() noexcept;

  virtual void SaveComponent();


  Entity* GetOwnerEntityPtr() const;
  Entity* SetOwnerEntityPtr(Entity* newOwnerPtr);

  Scene* GetOwnerScenePtr() const;

  bool IsPrimary() const;
  bool SetIsPrimary(bool newValue);
  bool IsActive() const;
  bool SetIsActive(bool newValue);

  size_t GetSlotIndex() const { return static_cast<size_t>(_slotIndex); };
  size_t GetType() const { return static_cast<size_t>(_type); }

  void SetOwnerComponentPtr(Component* pComponent);


protected:
  /** Pointer to Scene that owns this Component */
  Scene* _pOwnerScene;

  /** Pointer to Entity that owns this Component */
  Entity* _pOwnerEntity;

  /** Pointer to Component that owns this instance */
  Component* _pOwnerComponent;

  /** If this Component can be directly placed on Entity. */
  bool _isPrimary;

  /** If this Component is active */
  bool _isActive;

  /** What slot it belongs to on Entity */
  eSlotIndex _slotIndex;

  /** Type of Component */
  eType _type;

  
};

}