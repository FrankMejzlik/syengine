#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "common.h"
#include "IGuidCounted.h"
#include "SceneContext.h"

#include "EntityManager.h"
#include "Entity.h"

#include "MathLibrary.h"


namespace SYE
{
class InputManager;
class Camera;
class Window;

/**
 * Every Scene MUST have it's EntityController to call to.
 */
class Scene:
  public IGuidCounted
{
  // Methods
public:
  Scene() = delete;
  Scene(EntityManager* pEntityManager, std::string_view sceneName) noexcept;
  ~Scene() noexcept;

  Entity* InsertEntity(Entity* pEntityToInsert);
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
    bool isStatic = true
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

  
  void SetInputManagerPtr(InputManager* pInputManager) { _pInputManager = pInputManager; }
  InputManager* GetInputManagerPtr() const { return _pInputManager; }

  Camera* GetEditorCamera() const;
  std::string_view GetSceneName() const;

  void SetMainWindowPtr(Window* pMainWindow) { _pMainWindow = pMainWindow; };
  Window* GetMainWindowPtr() const { return _pMainWindow; };

  size_t GetSceneNumberOfEntities() const;
  std::unordered_map<size_t, Entity*> GetEntitiesRef()
  {
    return _entities;
  }
  /** Active Components categorized to important slots based on what module needs to acces them. */
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> GetActiveComponentsBySlotsRef() { return _activeComponentBySlots; }

  size_t MapTypeToSlot(size_t type);
  void EnlistComponent(Component* pNewComponent);
  void DelistComponent(Component* pNewComponent);

  // Attributes
private:
  SceneContext _sceneContext;
  /** EntityManager instance dedicated for this Scene instance */
  EntityManager* _pEntityManager;
  /** Pointer to servicing InputManager for this Scene */
  InputManager* _pInputManager;

  /** Pointer to default Engine Editor camera instance */
  Camera* _pEditorCamera;

  /** Pointer to main Window instance that this Scene is being rendered to */
  Window* _pMainWindow;
 
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