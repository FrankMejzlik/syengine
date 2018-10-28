#include "WorldObject.h"



WorldObject::WorldObject(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 positionVector, 
  glm::vec3 rotationVector, 
  glm::vec3 scaleVector,
  bool bIsStatic
):
  WorldEntity(pComponentManager, positionVector, rotationVector, scaleVector),
  _bIsStatic(bIsStatic)
{}


WorldObject::WorldObject(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 positionVector, 
  glm::vec3 rotationVector, 
  glm::vec3 scaleVector,
  bool bIsStatic,
  std::string filePath
):
  WorldEntity(pComponentManager, positionVector, rotationVector, scaleVector),
  _bIsStatic(bIsStatic)
{

  std::shared_ptr<Entity> pThis = std::make_shared<WorldObject>(*this);
_pModel = pComponentManager->CreateModelFromFile(pThis, filePath);
}


WorldObject::~WorldObject()
{}
