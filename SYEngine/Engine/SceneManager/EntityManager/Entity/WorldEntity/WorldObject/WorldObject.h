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
    bool isStatic
  );
  // Model from file contructor.
  WorldObject(
    ComponentManager* pComponentManager,
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector,
    bool isStatic,
    std::string_view filePath
  );

  ~WorldObject();

private:
  // If this WorldObject does not move at all.
  bool _isStatic;
  
};

