#pragma once

#include "WorldObject.h"

class Quad :
  public WorldObject
{
public:
  Quad(
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    bool bIsStatic,
    glm::vec3 leftBottomCoordinate, glm::vec3 rightTopCoordinate
  );
  ~Quad();
};

