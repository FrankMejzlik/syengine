
#include "Scene.h"

using namespace SYE;

Scene::Scene(EntityManager* pEntityManager, std::string_view sceneName) noexcept :
  _pEntityManager(pEntityManager),
  _sceneContext(sceneName),
  _pEditorCamera(nullptr)
{
  DLog(eLogType::Success, "Scene with name %s instantiated.", _sceneContext.m_sceneName.data());
}

Scene::~Scene() noexcept
{
  DLog(eLogType::Success, "Scene with name %s destroyed.", _sceneContext.m_sceneName.data());
}

_Camera* Scene::GetEditorCamera() const
{
  return _pEditorCamera;
}


std::string_view Scene::GetSceneName() const
{
  return _sceneContext.m_sceneName;
}

size_t Scene::GetSceneNumberOfEntities() const
{
  return _entities.size();
}

Entity* Scene::InsertEntity(Entity* pEntityToInsert)
{
  _entities.insert(std::make_pair(pEntityToInsert->GetGuid(), pEntityToInsert));

  // If has Colliders, insert them into map as well.
  if (pEntityToInsert->GetBHasColliders())
  {
    InsertActiveColliders(pEntityToInsert);
  }

  return pEntityToInsert;
}

bool Scene::DeleteEntity(Entity* pEntityToDelete)
{

  // If has Colliders, delete them.
  if (pEntityToDelete->GetBHasColliders())
  {
    DeleteActiveColliders(pEntityToDelete);
  }

  // Delete it from hash map.
  _entities.erase(pEntityToDelete->GetGuid());

  return true;
}

Entity* Scene::InsertActiveColliders(Entity* pEntityToInsert)
{
  auto entityColliders = pEntityToInsert->GetColliders();

  // Iteratre through all Colliders that this Entity has on it.
  for (auto && it : entityColliders)
  {
    _activeColliders.insert(std::make_pair(it.second->GetGuid(), it.second));
  }
  return pEntityToInsert;
}
Entity* Scene::DeleteActiveColliders(Entity* entityToDelete)
{
  auto entityColliders = entityToDelete->GetColliders();

  // Iteratre through all Colliders that this Entity has on it.
  for (auto && it : entityColliders)
  {
    _activeColliders.erase(it.second->GetGuid());
  }
  return entityToDelete;
}


Entity* Scene::InsertDirectionalLight(Entity* entityToInsert)
{
  // TODO: Increase light limit.
  if (_activePointLights.size() >= MAX_DIRECTIONAL_LIGHTS)
  {
    return nullptr;
  }

  _activeDirectionalLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

Entity* Scene::InsertActiveModel(Entity* entityToInsert)
{
  _activeModels.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

Entity* Scene::InsertPointLight(Entity* entityToInsert)
{
  // TODO: Increase light limit.
  if (_activePointLights.size() >= MAX_POINT_LIGHTS)
  {
    return nullptr;
  }

  _activePointLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

Entity* Scene::InsertSpotLight(Entity* entityToInsert)
{
  // TODO: Increase light limit.
  if (_activeSpotLights.size() >= MAX_SPOT_LIGHTS)
  {
    return nullptr;
  }
  _activeSpotLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

const std::unordered_map<size_t, Entity*>& Scene::GetActiveModelsRefConst() const
{
  return _activeModels;
}
const std::unordered_map<size_t, Collider*>& Scene::GetActiveColliders() const
{
  return _activeColliders;
}
const std::unordered_map<size_t, Entity*>& Scene::GetDirectionalLightsMapRefConst() const
{
  return _activeDirectionalLights;
}
const std::unordered_map<size_t, Entity*>& Scene::GetPointLightsMapRefConst() const
{
  return _activePointLights;
}

const std::unordered_map<size_t, Entity*>& Scene::GetSpotLightsMapRefConst() const
{
  return _activeSpotLights;
}


_Camera* Scene::CreateCamera(std::string_view cameraName, glm::vec3 positionVector, glm::vec3 startUpDirection, float startYaw, float startPitch)
{
  // TEMP
  // Camera has also input methods
  // It needs total restructure.
  //
  float moveSpeed = 5.0f;
  float turnSpeed = 1.0f;

  // Create new Camera instance.
  _Camera* pNewCamera = (_Camera*)_pEntityManager->CreateCamera(cameraName, positionVector, startUpDirection, startYaw, startPitch, moveSpeed, turnSpeed);

  pNewCamera->SetEntityName(cameraName);

  // TODO: Implement properly.
  _pEditorCamera = pNewCamera;

  return static_cast<_Camera*>(InsertEntity(pNewCamera));
}

Quad* Scene::CreateQuad(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height
)
{
  // Call EntityManager to create new Quad Entity.
  Quad* pNewQuad = (Quad*)_pEntityManager->CreateQuad(
    entityName,
    positionVector,
    rotationVector,
    scaleVector,
    width, height
  );

 
  // TODO: Make dynamic
  (*pNewQuad).SetBIsToRender(true);

  if ((*pNewQuad).GetBIsToRender())
  {
    InsertActiveModel(pNewQuad);
  }

  return static_cast<Quad*>(InsertEntity(pNewQuad));
}


Block* Scene::CreateBlock(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height, dfloat length,
  bool bIsStatic
)
{
  // Call EntityManager to create new Quad Entity.
  Block* pNewBlock = (Block*)_pEntityManager->CreateBlock(
    entityName,
    positionVector,
    rotationVector,
    scaleVector,
    width, height, length,
    bIsStatic
  );


  // TODO: Make dynamic
  (*pNewBlock).SetBIsToRender(true);

  if ((*pNewBlock).GetBIsToRender())
  {
    InsertActiveModel(pNewBlock);
  }

  return static_cast<Block*>(InsertEntity(pNewBlock));
}


WorldObject* Scene::CreateStaticModelFromFile(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  std::string_view filePath
)
{
  // Call EntityManager to create new WorldObject Entity.
  WorldObject* pNewEntity = (WorldObject*)_pEntityManager->CreateStaticModelFromFile(
    entityName,
    positionVector,
    rotationVector,
    scaleVector,
    filePath
  );


  // TODO: Make dynamic
  (*pNewEntity).SetBIsToRender(true);

  if ((*pNewEntity).GetBIsToRender())
  {
    InsertActiveModel(pNewEntity);
  }

  return static_cast<Block*>(InsertEntity(pNewEntity));
}

DirectionalLight* Scene::CreateDirectionalLight
(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 lightColour, glm::vec3 lightIntensities, 
  glm::vec3 shadowMapSize,
  glm::vec3 lightDirection
)
{

  DirectionalLight* pMainLight = (DirectionalLight*)_pEntityManager->CreateDirectionalLight(
    entityName,
    positionVector,          // Position vector
    rotationVector,          // rotation vector
    scaleVector,          // scale vector
    lightColour,          // Colour vector
    lightIntensities,          // Intensities
    shadowMapSize,    // Shadow dimensions
    lightDirection      // Light direction vector
  );

  pMainLight->SetEntityName(entityName);

  
  InsertDirectionalLight(pMainLight);

  return static_cast<DirectionalLight*>(InsertEntity(pMainLight));
  
}

PointLight* Scene::CreatePointLight(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector, 
  glm::vec3 lightColour, glm::vec3 lightIntensities, glm::vec3 shadowMapSize, 
  glm::vec2 planeDimensions, glm::vec3 coefficients
)
{
  PointLight* pMainLight = (PointLight*)_pEntityManager->CreatePointLight(
    entityName,
    positionVector,          // Position vector
    rotationVector,          // rotation vector
    scaleVector,          // scale vector
    lightColour,          // Colour vector
    lightIntensities,          // Intensities
    shadowMapSize,    // Shadow dimensions
    planeDimensions,      // Light direction vector
    coefficients
  );

  pMainLight->SetEntityName(entityName);
  
  InsertPointLight(pMainLight);

  return static_cast<PointLight*>(InsertEntity(pMainLight));
}

SpotLight* Scene::CreateSpotLight(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector, 
  glm::vec3 lightColour, glm::vec3 lightIntensities, glm::vec3 shadowMapSize, 
  glm::vec2 planeDimensions, glm::vec3 coefficients, glm::vec3 lightDirection, 
  dfloat coneAngle
)
{
  SpotLight* pMainLight = (SpotLight*)_pEntityManager->CreateSpotLight(
    entityName,
    positionVector,          // Position vector
    rotationVector,          // rotation vector
    scaleVector,          // scale vector
    lightColour,          // Colour vector
    lightIntensities,          // Intensities
    shadowMapSize,    // Shadow dimensions
    planeDimensions,      // Light direction vector
    coefficients,
    lightDirection,
    coneAngle
  );

  pMainLight->SetEntityName(entityName);

  InsertSpotLight(pMainLight);

  return static_cast<SpotLight*>(InsertEntity(pMainLight));
}

