#include "BlockCollider.h"

using namespace SYE;

BlockCollider::BlockCollider(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) :
  Collider(pOwnerEntity, subModulesConstRef)
{
  _type = eType::BLOCK_COLLIDER;
}

BlockCollider::BlockCollider(
  Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
  float a, float b, float c,
  bool bIsStatic, bool bIsSolid
): 
  Collider(
    pOwnerEntity, subModulesConstRef,
    std::move(pOwnerEntity->GetComponentManagerPtr()->GenerateMeshBlock(a, b, c)),
    position, rotation, scale, bIsStatic, bIsSolid
  )
{
  _type = eType::BLOCK_COLLIDER;
}


BlockCollider::~BlockCollider()
{}
