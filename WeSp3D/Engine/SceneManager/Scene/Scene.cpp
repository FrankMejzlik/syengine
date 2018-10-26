
#include "Scene.h"

using namespace WeSp;

Scene::Scene(std::shared_ptr<EntityManager> pEntityManager, std::string sceneName) :
  _pEntityManager(pEntityManager),
  _sceneContext(sceneName)
{

  DLog(eLogType::Success, "Scene with name %s instantiated.", _sceneContext.m_sceneName.c_str());
}

Scene::~Scene()
{
  DLog(eLogType::Success, "Scene with name %s destroyed.", _sceneContext.m_sceneName.c_str());
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
  _activeDirectionalLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

std::shared_ptr<Entity> Scene::InsertOmniDirectionalLight(std::shared_ptr<Entity> entityToInsert)
{
  _activeOmniDirectionallLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

std::shared_ptr<Camera> Scene::CreateCamera(std::string cameraName, glm::vec3 positionVector, glm::vec3 startUpDirection, float startYaw, float startPitch)
{
  // TEMP
  // Camera has also input methods
  // It needs total restructure.
  //
  float moveSpeed = 5.0;
  float turnSpeed = 1.0;

  // Create new Camera instance.
  std::shared_ptr<Camera> pNewCamera = std::make_shared<Camera>(nullptr, positionVector, startUpDirection, startYaw, startPitch, moveSpeed, turnSpeed);

  pNewCamera->SetEntityName(cameraName);

  InsertEntity(pNewCamera);

  return pNewCamera;
}

std::shared_ptr<Quad> Scene::CreateQuad(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  float width, float height
)
{
  // Call EntityManager to create new Quad Entity.
  std::shared_ptr<Quad> pNewQuad = _pEntityManager->CreateQuad(
    entityName,
    glm::vec3(0.0f, 0.0f, 5.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    5.0f, 10.0f
  );

  InsertEntity(pNewQuad);

  return pNewQuad;
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