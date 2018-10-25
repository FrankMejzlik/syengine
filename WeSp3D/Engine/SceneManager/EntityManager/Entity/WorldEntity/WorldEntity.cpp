
#include "WorldEntity.h"

using namespace WeSp;

WorldEntity::WorldEntity() :
  Entity() 
{}
WorldEntity::WorldEntity(
  glm::vec3 positionVector, 
  glm::vec3 rotationVector, 
  glm::vec3 scaleVector
) :
  Entity(positionVector, rotationVector, scaleVector)
{}

WorldEntity::~WorldEntity() {}