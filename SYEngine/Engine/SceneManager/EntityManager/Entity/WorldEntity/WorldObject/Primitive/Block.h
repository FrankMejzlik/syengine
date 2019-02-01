#pragma once

#include "common.h"
#include "WorldObject.h"
#include "ComponentManager.h"
#include "Model.h"

class Block :
  public WorldObject
{
public:
  Block(
    ComponentManager* pComponentManager,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    bool bIsStatic,
    dfloat width, dfloat height, dfloat length
  );
  ~Block();



private:
  
};

