#pragma once

#include "WorldEntity.h"
#include "ComponentManager.h"

class WorldObject:
  public WorldEntity
{
public:
  WorldObject(
    ComponentManager* pComponentManager,
    glm::vec3 positionVector, 
    glm::vec3 rotationVector, 
    glm::vec3 scaleVector,
    bool bIsStatic
  );
  // Model from file contructor.
  WorldObject(
    ComponentManager* pComponentManager,
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector,
    bool bIsStatic,
    std::string filePath
  );

  ~WorldObject();

private:
  // If this WorldObject does not move at all.
  bool _bIsStatic;
  
};

