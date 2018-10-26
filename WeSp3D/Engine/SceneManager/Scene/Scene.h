#pragma once

#include <memory>
#include <string>
#include <map>


#include <glm/glm.hpp>


#include "common.h"
#include "EntityManager.h"
#include "Entity.h"
#include "SceneContext.h"

// Entities.
#include "Camera.h"
#include "Quad.h"

namespace WeSp
{

class Block;
class DirectionalLight;
class PointLight;

/**
 * Every Scene MUST have it's EntityController to call to.
 */
class Scene
{
public:
  Scene() = delete;

  Scene(std::shared_ptr<EntityManager> pEntityManager, std::string sceneName);
  ~Scene();

  std::string GetSceneName();
  // Shortcut for create Entity, add components: camera, controller
  std::shared_ptr<Camera> CreateCamera(
    std::string entityName, 
    glm::vec3 positionVector, glm::vec3 startUpDirection, float startYaw, float startPitch
  );
  // Shortcut for create Entity, add components: camera, controller, texture
  std::shared_ptr<Quad> CreateQuad(
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    float width, float height
  );
  std::shared_ptr<Block> CreateBlock(glm::vec3 leftBottomCoordinate, glm::vec3 rightTopCoordinate);
  std::shared_ptr<DirectionalLight> CreateDirectionalLight(glm::vec3 leftBottomCoordinate, glm::vec3 rightTopCoordinate);
  std::shared_ptr<PointLight> CreatePointLight(glm::vec3 leftBottomCoordinate, glm::vec3 rightTopCoordinate);



private:
  SceneContext _sceneContext;
  std::map<std::string, std::shared_ptr<Entity>> _entityList;
  // EntityManager instance dedicated for this Scene instance.
  std::shared_ptr<EntityManager> _pEntityManager;
};

} // namespace WeSp