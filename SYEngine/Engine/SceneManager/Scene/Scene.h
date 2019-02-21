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

#if !NEW_SSSEC_IMPLEMENTED
// temp
#include "DirectionalLight.h"
#include "SpotLight.h"


// Entities.
#include "Camera.h"
#include "Quad.h"
#include "Block.h"
#endif

namespace SYE
{
#if !NEW_SSSEC_IMPLEMENTED
class _DirectionalLight;
class _PointLight;
class Camera;
class Collider;
#endif

class InputManager;

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

  
#if !NEW_SSSEC_IMPLEMENTED
public:


  const std::unordered_map<size_t, Entity*> &GetActiveModelsRefConst() const;
  const std::unordered_map<size_t, Collider*> &GetActiveColliders() const;
  const std::unordered_map<size_t, Entity*> &GetDirectionalLightsMapRefConst() const;
  const std::unordered_map<size_t, Entity*> &GetPointLightsMapRefConst() const;
  const std::unordered_map<size_t, Entity*> &GetSpotLightsMapRefConst() const;


  // Map of all Entities that have something to render out.
  std::unordered_map<size_t, Entity*> _activeModels;
  // Map of all active DirectionalLights.
  std::unordered_map<size_t, Entity*> _activeDirectionalLights;
  // Map of all active SpotLights.
  std::unordered_map<size_t, Entity*> _activePointLights;
  // Map of all active SpotLights.
  std::unordered_map<size_t, Entity*> _activeSpotLights;
  std::unordered_map<size_t, Collider*> _activeColliders;
  // Map of all Entities that have RigidBodies.
  std::unordered_map<size_t, Entity*> _activeWithRigidBodies;

  // Global Entity inserter.
  Entity* InsertEntity_(Entity* pEntityToInsert);
  bool DeleteEntity_(Entity* pEntityToDelete);

  Entity* InsertActiveColliders(Entity* entityToDelete);
  Entity* DeleteActiveColliders(Entity* entityToDelete);

  // Models to be rendered inserter.
  Entity* InsertActiveModel(Entity* entityToInsert);
  // Light insertors.
  Entity* InsertDirectionalLight(Entity* entityToInsert);
  Entity* InsertPointLight(Entity* entityToInsert);
  Entity* InsertSpotLight(Entity* entityToInsert);

  Block* _CreateBlock(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    dfloat width, dfloat height, dfloat length,
    bool bIsStatic = true
  );


  // Shortcut for create Entity, add components: camera, controller
  _Camera* CreateCamera(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 startUpDirection, float startYaw, float startPitch
  );

  // Shortcut for create Entity, add components: camera, controller, texture
  Quad* CreateQuad(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    dfloat width, dfloat height
  );

  WorldObject* CreateStaticModelFromFile(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    std::string_view filePath
  );

  _DirectionalLight* _CreateDirectionalLight(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour, glm::vec3 lightIntensities, 
    glm::vec3 shadowMapSize,
    glm::vec3 lightDirection
  );

  _PointLight* _CreatePointLight(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour,
    glm::vec3 lightIntensities,
    glm::vec3 shadowMapSize,
    glm::vec2 planeDimensions,
    glm::vec3 coefficients
  );

  _SpotLight* _CreateSpotLight(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour,
    glm::vec3 lightIntensities,
    glm::vec3 shadowMapSize,
    glm::vec2 planeDimensions,
    glm::vec3 coefficients,
    glm::vec3 lightDirection,
    dfloat coneAngle
  );

#endif

};

} // namespace SYE