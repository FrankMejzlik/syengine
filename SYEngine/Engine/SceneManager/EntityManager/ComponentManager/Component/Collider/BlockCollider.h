#pragma once

#include "common.h"
#include "Collider.h"
#include "Entity.h"
#include "ComponentManager.h"

namespace SYE
{

class BlockCollider :
  public Collider
{
public:
  BlockCollider() = delete;

  BlockCollider(std::shared_ptr<Entity> pEntity);
  BlockCollider(
    std::shared_ptr<Entity> pEntity, 
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
    float a, float b, float c,
    bool bIsStatic, bool isSolid
  );

  virtual ~BlockCollider();
};

} // namespace SYE