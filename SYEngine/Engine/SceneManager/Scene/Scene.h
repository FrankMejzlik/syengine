#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "common.h"
#include "IGuidCounted.h"

#include "EntityManager.h"
#include "Entity.h"
#include "SceneContext.h"

// temp
#include "DirectionalLight.h"
#include "SpotLight.h"

// Entities.
#include "Camera.h"
#include "Quad.h"
#include "Block.h"

namespace SYE
{

class DirectionalLight;
class PointLight;
class Collider;

/**
 * Every Scene MUST have it's EntityController to call to.
 */
class Scene:
  public IGuidCounted
{
public:
  Scene() = delete;
  Scene(EntityManager* pEntityManager, std::string_view sceneName) noexcept;
  ~Scene() noexcept;

  _Camera* GetEditorCamera() const;
  std::string_view GetSceneName() const;
  size_t GetSceneNumberOfEntities() const;

  Block* CreateBlock(
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
  
  DirectionalLight* CreateDirectionalLight(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour, glm::vec3 lightIntensities, 
    glm::vec3 shadowMapSize,
    glm::vec3 lightDirection
  );

  PointLight* CreatePointLight(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour,
    glm::vec3 lightIntensities,
    glm::vec3 shadowMapSize,
    glm::vec2 planeDimensions,
    glm::vec3 coefficients
  );

  SpotLight* CreateSpotLight(
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

  const std::unordered_map<size_t, Entity*> &GetActiveModelsRefConst() const;
  const std::unordered_map<size_t, Collider*> &GetActiveColliders() const;
  const std::unordered_map<size_t, Entity*> &GetDirectionalLightsMapRefConst() const;
  const std::unordered_map<size_t, Entity*> &GetPointLightsMapRefConst() const;
  const std::unordered_map<size_t, Entity*> &GetSpotLightsMapRefConst() const;

private:
  SceneContext _sceneContext;
  // EntityManager instance dedicated for this Scene instance.
  EntityManager* _pEntityManager;
  // Pointer to default Engine Editor camera instance.
  _Camera* _pEditorCamera;
 
  // Map of all entities in this Scene.
  std::unordered_map<size_t, Entity*> _entities;

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
  Entity* InsertEntity(Entity* pEntityToInsert);
  bool DeleteEntity(Entity* pEntityToDelete);
  
  Entity* InsertActiveColliders(Entity* entityToDelete);
  Entity* DeleteActiveColliders(Entity* entityToDelete);
  
  // Models to be rendered inserter.
  Entity* InsertActiveModel(Entity* entityToInsert);
  // Light insertors.
  Entity* InsertDirectionalLight(Entity* entityToInsert);
  Entity* InsertPointLight(Entity* entityToInsert);
  Entity* InsertSpotLight(Entity* entityToInsert);
};

} // namespace SYE