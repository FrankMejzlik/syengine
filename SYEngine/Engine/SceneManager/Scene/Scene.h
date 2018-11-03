#pragma once

#include <memory>
#include <string>
#include <unordered_map>


#include <glm/glm.hpp>


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

  Scene(std::shared_ptr<EntityManager> pEntityManager, std::string sceneName);
  ~Scene();

  std::shared_ptr<Camera>GetEditorCamera() const;
  std::string GetSceneName() const;
  size_t GetSceneNumberOfEntities() const;
  // Shortcut for create Entity, add components: camera, controller
  std::shared_ptr<Camera> CreateCamera(
    std::string entityName, 
    glm::vec3 positionVector, glm::vec3 startUpDirection, float startYaw, float startPitch
  );
  // Shortcut for create Entity, add components: camera, controller, texture
  std::shared_ptr<Quad> CreateQuad(
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    dfloat width, dfloat height
  );
  std::shared_ptr<Block> CreateBlock(
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    dfloat width, dfloat height, dfloat length,
    bool bIsStatic = true
  );

  std::shared_ptr<WorldObject> CreateStaticModelFromFile(
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    std::string filePath
  );
  
  std::shared_ptr<DirectionalLight> CreateDirectionalLight
  (
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour, glm::vec3 lightIntensities, 
    glm::vec3 shadowMapSize,
    glm::vec3 lightDirection
  );

  std::shared_ptr<PointLight> CreatePointLight(
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour,
    glm::vec3 lightIntensities,
    glm::vec3 shadowMapSize,
    glm::vec2 planeDimensions,
    glm::vec3 coefficients
  );

  std::shared_ptr<SpotLight> CreateSpotLight(
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour,
    glm::vec3 lightIntensities,
    glm::vec3 shadowMapSize,
    glm::vec2 planeDimensions,
    glm::vec3 coefficients,
    glm::vec3 lightDirection,
    dfloat coneAngle
  );

  const std::unordered_map<size_t, std::shared_ptr<Entity>> &GetActiveModelsRefConst() const;
  const std::unordered_map<size_t, std::shared_ptr<Collider>> &GetActiveColliders() const;
  const std::unordered_map<size_t, std::shared_ptr<Entity>> &GetDirectionalLightsMapRefConst() const;
  const std::unordered_map<size_t, std::shared_ptr<Entity>> &GetPointLightsMapRefConst() const;
  const std::unordered_map<size_t, std::shared_ptr<Entity>> &GetSpotLightsMapRefConst() const;

private:
  SceneContext _sceneContext;
  // EntityManager instance dedicated for this Scene instance.
  std::shared_ptr<EntityManager> _pEntityManager;
  // Pointer to default Engine Editor camera instance.
  std::shared_ptr<Camera> _pEditorCamera;
 
  // Map of all entities in this Scene.
  std::unordered_map<size_t, std::shared_ptr<Entity>> _entities;
  // Map of all Entities that have something to render out.
  std::unordered_map<size_t, std::shared_ptr<Entity>> _activeModels;
  // Map of all active DirectionalLights.
  std::unordered_map<size_t, std::shared_ptr<Entity>> _activeDirectionalLights;
  // Map of all active SpotLights.
  std::unordered_map<size_t, std::shared_ptr<Entity>> _activePointLights;
  // Map of all active SpotLights.
  std::unordered_map<size_t, std::shared_ptr<Entity>> _activeSpotLights;
  std::unordered_map<size_t, std::shared_ptr<Collider>> _activeColliders;
  // Map of all Entities that have RigidBodies.
  std::unordered_map<size_t, std::shared_ptr<Entity>> _activeWithRigidBodies;

  // Global Entity inserter.
  std::shared_ptr<Entity> InsertEntity(std::shared_ptr<Entity> entityToInsert);
  std::shared_ptr<Entity> DeleteEntity(std::shared_ptr<Entity> entityToDelete);
  
  std::shared_ptr<Entity> InsertActiveColliders(std::shared_ptr<Entity> entityToDelete);
  std::shared_ptr<Entity> DeleteActiveColliders(std::shared_ptr<Entity> entityToDelete);
  
  // Models to be rendered inserter.
  std::shared_ptr<Entity> InsertActiveModel(std::shared_ptr<Entity> entityToInsert);
  // Light insertors.
  std::shared_ptr<Entity> InsertDirectionalLight(std::shared_ptr<Entity> entityToInsert);
  std::shared_ptr<Entity> InsertPointLight(std::shared_ptr<Entity> entityToInsert);
  std::shared_ptr<Entity> InsertSpotLight(std::shared_ptr<Entity> entityToInsert);
};

} // namespace SYE