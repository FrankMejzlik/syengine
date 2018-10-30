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
  BlockCollider(std::shared_ptr<Entity> pEntity, float a, float b, float c,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, bool isSolid);
  virtual ~BlockCollider();
};

} // namespace SYE