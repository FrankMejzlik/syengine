#include "WorldObject.h"



WorldObject::WorldObject(
  glm::vec3 positionVector, 
  glm::vec3 rotationVector, 
  glm::vec3 scaleVector,
  bool bIsStatic
):
  WorldEntity(positionVector, rotationVector, scaleVector),
  _bIsStatic(bIsStatic)
{}


WorldObject::~WorldObject()
{}
