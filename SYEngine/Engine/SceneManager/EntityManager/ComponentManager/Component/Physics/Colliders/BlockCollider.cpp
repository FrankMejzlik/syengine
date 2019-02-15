#include "BlockCollider.h"

using namespace SYE;

BlockCollider::BlockCollider(Entity* pEntity) :
  Collider(pEntity)
{
}

BlockCollider::BlockCollider(
  Entity* pEntity, 
  glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
  float a, float b, float c,
  bool bIsStatic, bool bIsSolid
): 
    Collider(pEntity, 
      std::move(pEntity->GetComponentManagerPtr()->GenerateMeshBlock(a, b, c)),
      position, rotation, scale, bIsStatic, bIsSolid)

{
}


BlockCollider::~BlockCollider()
{}
