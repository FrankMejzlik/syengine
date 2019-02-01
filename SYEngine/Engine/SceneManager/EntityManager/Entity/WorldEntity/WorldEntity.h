#pragma once

#include "Entity.h"

using namespace SYE;

namespace SYE 
{

/**
 * Class representing entities that appear in 3D world.
 */
class WorldEntity :
  public Entity
{
public:
  WorldEntity() = delete;

  WorldEntity(
    ComponentManager* pComponentManager,
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector
  );
  virtual ~WorldEntity();

protected:

};

}