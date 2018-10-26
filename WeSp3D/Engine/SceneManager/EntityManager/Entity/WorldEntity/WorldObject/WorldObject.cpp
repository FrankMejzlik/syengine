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


WorldObject::~WorldObject()
{}
