
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

std::string Scene::GetSceneName()
{
  return _sceneContext.m_sceneName;
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
  // Insert in map of Entities.
  _entityList.insert(std::make_pair(cameraName, pNewCamera));

  return pNewCamera;
}

std::shared_ptr<Quad> Scene::CreateQuad(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  float width, float height
)
{

  //std::shared_ptr<Quad> newQuad = _pEntityManager->CreateQuad();

  return nullptr;
}