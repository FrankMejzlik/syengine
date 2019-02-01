#include "WorldObject.h"



WorldObject::WorldObject(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector, 
  glm::vec3 rotationVector, 
  glm::vec3 scaleVector,
  bool bIsStatic
):
  WorldEntity(pComponentManager, positionVector, rotationVector, scaleVector),
  _bIsStatic(bIsStatic)
{}


WorldObject::WorldObject(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector, 
  glm::vec3 rotationVector, 
  glm::vec3 scaleVector,
  bool bIsStatic,
  std::string filePath
):
  WorldEntity(pComponentManager, positionVector, rotationVector, scaleVector),
  _bIsStatic(bIsStatic)
{
  _pModel = pComponentManager->CreateModelFromFile(this, filePath);
}


WorldObject::~WorldObject()
{}
