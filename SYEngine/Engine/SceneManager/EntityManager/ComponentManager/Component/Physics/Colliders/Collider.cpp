#include "Collider.h"

using namespace SYE;

Collider::Collider(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots):
  Component(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
    true, true,
    PHYSICS_COLLIDER
  )
{
  _type = eType::COLLIDER;
}

Collider::Collider(
  Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots, 
  std::unique_ptr<Mesh>&& mesh,
  glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
  bool bIsStatic, bool bIsSolid
): 
  Component(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
    true, true,
    PHYSICS_COLLIDER
  ),
  _pMesh(std::move(mesh)),
  _position(position), _rotation(rotation), _scale(scale),
  _bIsStatic(bIsStatic),
  _bIsSolid(bIsSolid),
  _absolutePosition(pOwnerEntity->GetPositionVectorRefConst() + position),   
  _absoluteRotation(pOwnerEntity->GetRotationVectorRefConst() + rotation),
  _absoluteScale(pOwnerEntity->GetScaleVectorRefConst() * scale)
{
  _type = eType::COLLIDER;
}


Collider::~Collider()
{}
