#include "Collider.h"

using namespace SYE;

Collider::Collider(std::shared_ptr<Entity> pEntity):
  Component(pEntity)
{
}

Collider::Collider(std::shared_ptr<Entity> pEntity, std::shared_ptr<Mesh> mesh,
  glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, bool isSolid): Component(pEntity),
  _pMesh(mesh), _position(position), _rotation(rotation), _scale(scale), _bIsSolid(isSolid),
  _absolutePosition(pEntity->GetPositionVectorRefConst() + position),   
  _absoluteRotation(pEntity->GetRotationVectorRefConst() + rotation),
  _absoluteScale(pEntity->GetScaleVectorRefConst() * scale)
{
}


Collider::~Collider()
{}
