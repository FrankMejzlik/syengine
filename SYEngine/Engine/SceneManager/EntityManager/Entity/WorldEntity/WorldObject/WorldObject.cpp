#include "WorldObject.h"



WorldObject::WorldObject(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector, 
  glm::vec3 rotationVector, 
  glm::vec3 scaleVector,
  bool isStatic
):
  WorldEntity(pComponentManager, positionVector, rotationVector, scaleVector),
  _isStatic(isStatic)
{}


WorldObject::WorldObject(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector, 
  glm::vec3 rotationVector, 
  glm::vec3 scaleVector,
  bool bIsStatic,
  std::string_view filePath
):
  WorldEntity(pComponentManager, positionVector, rotationVector, scaleVector),
  _isStatic(bIsStatic)
{
  _pModel = pComponentManager->CreateModelFromFile(this, filePath);
}


WorldObject::~WorldObject()
{}
