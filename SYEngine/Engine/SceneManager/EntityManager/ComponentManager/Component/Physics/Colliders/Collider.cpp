#include "Collider.h"

using namespace SYE;

Collider::Collider(Entity* pEntity):
  Component(pEntity)
{
}

Collider::Collider(
  Entity* pEntity, 
  std::unique_ptr<Mesh>&& mesh,
  glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, bool bIsStatic, bool bIsSolid): 
    Component(pEntity),
  _pMesh(std::move(mesh)),
  _position(position), _rotation(rotation), _scale(scale),
  _bIsStatic(bIsStatic),
  _bIsSolid(bIsSolid),
  _absolutePosition(pEntity->GetPositionVectorRefConst() + position),   
  _absoluteRotation(pEntity->GetRotationVectorRefConst() + rotation),
  _absoluteScale(pEntity->GetScaleVectorRefConst() * scale)
{
}


Collider::~Collider()
{}
