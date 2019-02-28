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

class Scene;
class Entity;
class ComponentManager;
class PhysicsManager;
class Component;

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
    CAPSULE_COLLIDER = 101,
    CONVEX_MESH_COLLIDER = 102,
    MATERIAL = 110,
    SHININESS = 111,
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
    Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    bool isPrimary = true, bool isActive = true,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::COMPONENT
  );
  virtual ~Component() noexcept;

  virtual void Refresh();
  virtual void SaveComponent();

  virtual bool EnlistComponent(Component* pNewComponent);
  virtual bool DelistComponent(Component* pComponent);

  PhysicsManager* GetPhysicsManager();

  Entity* GetOwnerEntityPtr() const;
  Entity* SetOwnerEntityPtr(Entity* newOwnerPtr);

  Scene* GetOwnerScenePtr() const;

  bool IsPrimary() const;
  bool SetIsPrimary(bool newValue);
  bool IsActive() const;
  bool SetIsActive(bool newValue);
  bool IsDefault() const;
  bool SetIsDefault(bool newValue);
  size_t GetSlotIndex() const { return static_cast<size_t>(_slotIndex); };
  size_t GetType() const { return static_cast<size_t>(_type); }

  void SetOwnerComponentPtr(Component* pComponent);


  

protected:

protected:
  /** Pointer to Entity that owns this Component. */
  Entity* _pOwnerEntity;

  /** Pointer to Component that owns this instance */
  Component* _pOwnerComponent;

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

  /** 
   * Reference to table of active primary Components on owning Entity 
   *
   * Indices of slots are configured at config_components.h.
   * Some slots are singletons, e.g. there can be only one light source per Component.
   */
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& _primaryComponentSlots;
  
private:

};

}