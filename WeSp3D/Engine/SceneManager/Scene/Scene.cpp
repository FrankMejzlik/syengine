
#include "Scene.h"

using namespace WeSp;

Scene::Scene(std::shared_ptr<EntityManager> pEntityManager, std::string sceneName) :
  _pEntityManager(pEntityManager),
  _sceneContext(sceneName),
  _pEditorCamera(nullptr)
{

  DLog(eLogType::Success, "Scene with name %s instantiated.", _sceneContext.m_sceneName.c_str());
}

Scene::~Scene()
{
  DLog(eLogType::Success, "Scene with name %s destroyed.", _sceneContext.m_sceneName.c_str());
}

std::shared_ptr<Camera> Scene::GetEditorCamera() const
{
  return _pEditorCamera;
}


std::string Scene::GetSceneName() const
{
  return _sceneContext.m_sceneName;
}

size_t Scene::GetSceneNumberOfEntities() const
{
  return _entities.size();
}

std::shared_ptr<Entity> Scene::InsertEntity(std::shared_ptr<Entity> entityToInsert)
{
  _entities.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

std::shared_ptr<Entity> Scene::InsertDirectionalLight(std::shared_ptr<Entity> entityToInsert)
{
  // TODO: Increase light limit.
  if (_activePointLights.size() >= MAX_DIRECTIONAL_LIGHTS)
  {
    return nullptr;
  }

  _activeDirectionalLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

std::shared_ptr<Entity> Scene::InsertActiveModel(std::shared_ptr<Entity> entityToInsert)
{
  _activeModels.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

std::shared_ptr<Entity> Scene::InsertPointLight(std::shared_ptr<Entity> entityToInsert)
{
  // TODO: Increase light limit.
  if (_activePointLights.size() >= MAX_POINT_LIGHTS)
  {
    return nullptr;
  }

  _activePointLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

std::shared_ptr<Entity> Scene::InsertSpotLight(std::shared_ptr<Entity> entityToInsert)
{
  // TODO: Increase light limit.
  if (_activePointLights.size() >= MAX_SPOT_LIGHTS)
  {
    return nullptr;
  }
  _activeSpotLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

const std::unordered_map<size_t, std::shared_ptr<Entity>> &Scene::GetActiveModelsRefConst() const
{
  return _activeModels;
}
const std::unordered_map<size_t, std::shared_ptr<Entity>> &Scene::GetDirectionalLightsMapRefConst() const
{
  return _activeDirectionalLights;
}
const std::unordered_map<size_t, std::shared_ptr<Entity>> &Scene::GetPointLightsMapRefConst() const
{
  return _activePointLights;
}

const std::unordered_map<size_t, std::shared_ptr<Entity>> &Scene::GetSpotLightsMapRefConst() const
{
  return _activeSpotLights;
}


std::shared_ptr<Camera> Scene::CreateCamera(std::string cameraName, glm::vec3 positionVector, glm::vec3 startUpDirection, float startYaw, float startPitch)
{
  // TEMP
  // Camera has also input methods
  // It needs total restructure.
  //
  float moveSpeed = 5.0f;
  float turnSpeed = 1.0f;

  // Create new Camera instance.
  std::shared_ptr<Camera> pNewCamera = std::make_shared<Camera>(nullptr, positionVector, startUpDirection, startYaw, startPitch, moveSpeed, turnSpeed);

  pNewCamera->SetEntityName(cameraName);

  InsertEntity(pNewCamera);
  // TODO: Implement properly.
  _pEditorCamera = pNewCamera;

  return pNewCamera;
}

std::shared_ptr<Quad> Scene::CreateQuad(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height
)
{
  // Call EntityManager to create new Quad Entity.
  std::shared_ptr<Quad> pNewQuad = _pEntityManager->CreateQuad(
    entityName,
    positionVector,
    rotationVector,
    scaleVector,
    width, height
  );

  InsertEntity(pNewQuad);

  // TODO: Make dynamic
  (*pNewQuad).SetBIsToRender(true);

  if ((*pNewQuad).GetBIsToRender())
  {
    InsertActiveModel(pNewQuad);
  }

  return pNewQuad;
}


std::shared_ptr<Block> Scene::CreateBlock(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height, dfloat length
)
{
  // Call EntityManager to create new Quad Entity.
  std::shared_ptr<Block> pNewBlock = _pEntityManager->CreateBlock(
    entityName,
    positionVector,
    rotationVector,
    scaleVector,
    width, height, length
  );

  InsertEntity(pNewBlock);

  // TODO: Make dynamic
  (*pNewBlock).SetBIsToRender(true);

  if ((*pNewBlock).GetBIsToRender())
  {
    InsertActiveModel(pNewBlock);
  }

  return pNewBlock;
}


std::shared_ptr<WorldObject> Scene::CreateStaticModelFromFile(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  std::string filePath
)
{
  // Call EntityManager to create new WorldObject Entity.
  std::shared_ptr<WorldObject> pNewEntity = _pEntityManager->CreateStaticModelFromFile(
    entityName,
    positionVector,
    rotationVector,
    scaleVector,
    filePath
  );

  InsertEntity(pNewEntity);

  // TODO: Make dynamic
  (*pNewEntity).SetBIsToRender(true);

  if ((*pNewEntity).GetBIsToRender())
  {
    InsertActiveModel(pNewEntity);
  }

  return pNewEntity;
}

std::shared_ptr<DirectionalLight> Scene::CreateDirectionalLight
(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 lightColour, glm::vec3 lightIntensities, 
  glm::vec3 shadowMapSize,
  glm::vec3 lightDirection
)
{

  std::shared_ptr<DirectionalLight> pMainLight = std::make_shared<DirectionalLight>(
    nullptr,
    positionVector,          // Position vector
    rotationVector,          // rotation vector
    scaleVector,          // scale vector
    lightColour,          // Colour vector
    lightIntensities,          // Intensities
    shadowMapSize,    // Shadow dimensions
    lightDirection      // Light direction vector
  );

  pMainLight->SetEntityName(entityName);

  InsertEntity(pMainLight);
  InsertDirectionalLight(pMainLight);

  return pMainLight;
  
}

std::shared_ptr<PointLight> Scene::CreatePointLight(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector, 
  glm::vec3 lightColour, glm::vec3 lightIntensities, glm::vec3 shadowMapSize, 
  glm::vec2 planeDimensions, glm::vec3 coefficients
)
{
  std::shared_ptr<PointLight> pMainLight = std::make_shared<PointLight>(
    nullptr,
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

  InsertEntity(pMainLight);
  InsertPointLight(pMainLight);

  return pMainLight;
}

std::shared_ptr<SpotLight> Scene::CreateSpotLight(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector, 
  glm::vec3 lightColour, glm::vec3 lightIntensities, glm::vec3 shadowMapSize, 
  glm::vec2 planeDimensions, glm::vec3 coefficients, glm::vec3 lightDirection, 
  dfloat coneAngle
)
{
  std::shared_ptr<SpotLight> pMainLight = std::make_shared<SpotLight>(
    nullptr,
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

  InsertEntity(pMainLight);
  InsertSpotLight(pMainLight);

  return pMainLight;
}

