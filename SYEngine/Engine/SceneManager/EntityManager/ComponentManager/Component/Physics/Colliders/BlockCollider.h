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

  BlockCollider(
    Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef
  );
  BlockCollider(
    Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
    float a, float b, float c,
    bool bIsStatic, bool isSolid
  );

  virtual ~BlockCollider();
};

} // namespace SYE