#include "BlockCollider.h"

using namespace SYE;

BlockCollider::BlockCollider(std::shared_ptr<Entity> pEntity) :
  Collider(pEntity)
{
}

BlockCollider::BlockCollider(
  std::shared_ptr<Entity> pEntity, 
  glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
  float a, float b, float c,
  bool isSolid
): 
    Collider(pEntity, 
      pEntity->GetComponentManager()->GenerateMeshBlock(a, b, c),
      position, rotation, scale, isSolid)

{
}


BlockCollider::~BlockCollider()
{}
