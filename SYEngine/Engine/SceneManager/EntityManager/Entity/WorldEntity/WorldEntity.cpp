
#include "WorldEntity.h"

using namespace SYE;


WorldEntity::WorldEntity(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 positionVector, 
  glm::vec3 rotationVector, 
  glm::vec3 scaleVector
) :
  Entity(pComponentManager, positionVector, rotationVector, scaleVector)
{}

WorldEntity::~WorldEntity() {}