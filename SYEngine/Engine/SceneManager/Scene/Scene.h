#pragma once

#include <memory>
#include <string>
#include <map>
#include <unordered_map>
#include <array>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "common.h"
#include "IErrorLogging.h"
#include "IGuidCounted.h"
#include "SceneContext.h"

#include "MathLibrary.h"


namespace SYE
{

class InputManager;
class Camera;
class Window;
class PhysicsScene;
class PhysicsManager;
class PhysicsBody;
class Entity;
class EntityManager;
class Component;

/**
 * Every Scene MUST have it's EntityController to call to.
 */
class Scene:
  public IGuidCounted, public IErrorLogging
{
  // Methods
public:
  Scene() = delete;
  Scene(EntityManager* pEntityManager);
  ~Scene() noexcept;

  template <typename EntityType>
  EntityType* AddEntity()
  {
    Entity* pNewEntity = _pEntityManager->CreateEntity<EntityType>(this);

    return pNewEntity;
  }

  bool DeleteEntity(Entity* pEntityToDelete);

  Entity* CreateCamera(
    Vector3f positionVector, 
    Vector3f startUpDirection, dfloat startYaw, dfloat startPitch,
    bool isEditor = false
  );

  Entity* CreateQuad(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    dfloat width, dfloat height,
    bool isStatic
  );

  Entity* CreateBlock(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    dfloat width, dfloat height, dfloat length,
    bool isStatic = true,
    dfloat mass = 0.0f
  );

  Entity* CreateDirectionalLight(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
    Vector3f direction,
    bool isStatic = true
  );

  Entity* CreatePointLight(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
    dfloat nearPlane, dfloat farPlane,
    Vector3f coefficients,
    bool isStatic = true
  );

  Entity* CreateSpotLight(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
    dfloat nearPlane, dfloat farPlane,
    Vector3f coefficients,
    Vector3f direction,
    dfloat coneAngle,
    bool isStatic = true
  );

  /**
   * Casts ray from specified position in specified direction and returns <PBody hit, hit Point>
   */
  std::pair<PhysicsBody*, Vector3f> Raycast(Vector3f from, Vector3f direction) const;

  void SetInputManagerPtr(InputManager* pInputManager) { _pInputManager = pInputManager; }
  InputManager* GetInputManagerPtr() const { return _pInputManager; }

  void SetPhysicsManagerPtr(PhysicsManager* pPhysicsManager) { _pPhysicsManager = pPhysicsManager; }
  PhysicsManager* GetPhysicsManagerPtr() const { return _pPhysicsManager; }

  Camera* GetEditorCamera() const;
  std::string_view GetSceneName() const;

  void SetMainWindowPtr(Window* pMainWindow) { _pMainWindow = pMainWindow; };
  Window* GetMainWindowPtr() const { return _pMainWindow; };

  void SetPhysicsScenePtr(PhysicsScene* pPhysicsScene);
  PhysicsScene* GetPhysicsScenePtr() const;


  size_t GetSceneNumberOfEntities() const;
  std::unordered_map<size_t, Entity*> GetEntitiesRef()
  {
    return _entities;
  }
  /** Active Components categorized to important slots based on what module needs to acces them. */
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> GetActiveComponentsBySlotsRef() { return _activeComponentBySlots; }


  void ShootBox(const Vector3f& cameraPosition, const Vector3f& direction);
  
  size_t MapTypeToSlot(size_t type);

  bool EnlistComponent(Component* pNewComponent);
  bool DelistComponent(Component* pComponent);
  /** 
   * Adds pointer to this instance everywhere it needs to
   */
  bool EnlistEntity(Entity* pEntity);
  /** 
   * Nulls pointer to this instance everywhere EnlistEntity added it
   */
  bool DelistEntity(Entity* pEntity);

  // Attributes
private:
  SceneContext _sceneContext;
  /** EntityManager instance dedicated for this Scene instance */
  EntityManager* _pEntityManager;
  /** Pointer to servicing InputManager for this Scene */
  InputManager* _pInputManager;

  /** Pointer to corresponding PhysicsManager */
  PhysicsManager* _pPhysicsManager;

  /** Pointer to default Engine Editor camera instance */
  Camera* _pEditorCamera;

  /** Pointer to main Window instance that this Scene is being rendered to */
  Window* _pMainWindow;

  /** Pointer to PhysicsScene that corresponds to this Scene */
  PhysicsScene* _pPhysicsScene;
 
  // Map of all entities in this Scene.
  std::unordered_map<size_t, Entity*> _entities;

  /** 
  * Table of active primary Components on this Entity 
  *
  * Indices of slots are configured at config_components.h.
  * Some slots are singletons, e.g. there can be only one light source per Component.
  */
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> _activeComponentBySlots;

 
};

} // namespace SYE