#pragma once

#include "WorldEntity.h"

class WorldObject:
  public WorldEntity
{
public:
  WorldObject(
    glm::vec3 positionVector, 
    glm::vec3 rotationVector, 
    glm::vec3 scaleVector,
    bool bIsStatic
  );
  ~WorldObject();

private:
  // If this WorldObject does not move at all.
  bool _bIsStatic;
  
};

