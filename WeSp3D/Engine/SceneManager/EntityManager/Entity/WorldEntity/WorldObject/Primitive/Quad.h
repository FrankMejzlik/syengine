#pragma once

#include "common.h"
#include "WorldObject.h"

class Quad :
  public WorldObject
{
public:
  Quad(
    std::shared_ptr<ComponentManager> pComponentManager,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    bool bIsStatic,
    dfloat width, dfloat height
  );
  ~Quad();
};

