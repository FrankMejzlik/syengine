#pragma once

#include "Entity.h"

using namespace WeSp;

namespace WeSp 
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
    std::shared_ptr<ComponentManager> pComponentManager,
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector
  );
  virtual ~WorldEntity();

protected:

};

}