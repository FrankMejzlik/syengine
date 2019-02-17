#include "BlockCollider.h"

using namespace SYE;

BlockCollider::BlockCollider(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) :
  Collider(pOwnerEntity, subModulesConstRef, primaryComponentSlots)
{
  _type = eType::BLOCK_COLLIDER;
}

BlockCollider::BlockCollider(
  Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots, 
  glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
  float a, float b, float c,
  bool bIsStatic, bool bIsSolid
): 
  Collider(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
    std::move(pOwnerEntity->GetComponentManagerPtr()->GenerateMeshBlock(a, b, c)),
    position, rotation, scale, bIsStatic, bIsSolid
  )
{
  _type = eType::BLOCK_COLLIDER;
}


BlockCollider::~BlockCollider()
{}
