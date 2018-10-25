
#include "Scene.h"

using namespace WeSp;

Scene::Scene(std::string sceneName) :
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
  float moveSpeed = 5.0;
  float turnSpeed = 1.0;

  // Create new Camera instance.
  std::shared_ptr<Camera> pNewCamera = std::make_shared<Camera>(positionVector, startUpDirection, startYaw, startPitch, moveSpeed, turnSpeed);
  // Insert in map of Entities.
  _entities.insert(std::make_pair(cameraName, pNewCamera));

  return pNewCamera;
}

std::shared_ptr<Quad> Scene::CreateQuad(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  float width, float height
)
{
  return nullptr;
}