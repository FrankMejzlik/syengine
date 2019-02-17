#pragma once

#include <memory>
#include <vector>
#include <map>

#include "config_components.h"
#include "IGuidCounted.h"
#include "IErrorLogging.h"
#include "BaseModule.h"
#include "MathLibrary.h"


namespace SYE
{
class Entity;
class ComponentManager;

class Component:
  public IGuidCounted, public IErrorLogging
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
    MESH_COLLIDER = 101,
    MATERIAL = 110,
    TEXTURE = 120,
    MESH_RENDERER = 130,
    RIGIDBODY = 140,
    SOFTBODY = 141,
    PHYSICS_MATERIAL = 150,
    SKYBOX = 160,
    SOUND = 170,
    CAMERA = 180,
    NUM_TYPES = 190,
    LIGHT = 200,
    DIRECTIONAL_LIGHT = 210,
    POINT_LIGHT = 220,
    SPOT_LIGHT = 230,
    SCRIPT = 240
  };

  enum eSlotIndex
  {
    UNDEFINED = 0,
    TRANSFORM = COMPONENT_TRANSFORM_SLOT,
    DIRECTIONAL_LIGHT_SOURCE = COMPONENT_DIRECTIONAL_LIGHT_SOURCE_SLOT,
    POINT_LIGHT_SOURCE = COMPONENT_POINT_LIGHT_SOURCE_SLOT,
    SPOT_LIGHT_SOURCE = COMPONENT_SPOT_LIGHT_SOURCE_SLOT,
    SCRIPT = COMPONENT_SCRIPT_SLOT,
    CAMERA = COMPONENT_CAMERA_SLOT,
    PHYSICS_BODY = COMPONENT_PHYSICS_BODY_SLOT,
    PHYSICS_COLLIDER = COMPONENT_PHYSICS_COLLIDER_SLOT,
    MESH_RENDERER = COMPONENT_MESH_RENDERER_SLOT
  };

public:
  Component() = delete;
  Component(
    Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef,
    bool isPrimary = true, bool isActive = true,
    eSlotIndex slotIndex = UNDEFINED 
  ) noexcept;
  virtual ~Component() noexcept = default;

  Entity* GetOwnerEntityPtr() const;
  Entity* SetOwnerEntityPtr(Entity* newOwnerPtr);

  bool IsPrimary() const;
  bool SetIsPrimary(bool newValue);
  bool IsActive() const;
  bool SetIsActive(bool newValue);
  bool IsDefault() const;
  bool SetIsDefault(bool newValue);
  size_t GetSlotIndex() const { return static_cast<size_t>(_slotIndex); };
  size_t GetType() const { return static_cast<size_t>(_type); }

protected:

protected:
  /** Pointer to Entity that owns this Component. */
  Entity* _pOwnerEntity;

  /** ComponentManager dedicated to this */
  ComponentManager* _pComponentManager;

  /** If this Component can be directly placed on Entity. */
  bool _isPrimary;

  /** If this Component is active */
  bool _isActive;

  /** If is in default state*/
  bool _isDefault;

  /** What slot it belongs to on Entity */
  eSlotIndex _slotIndex;

  /** Type of Component */
  eType _type;

  /** ComponentManager submodules that every Component can use */
  const std::map< int, std::unique_ptr<BaseModule> >& _subModules;
  
};

}