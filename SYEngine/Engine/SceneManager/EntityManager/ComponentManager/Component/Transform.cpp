#include "Transform.h"

#include "Entity.h"

using namespace SYE;

Transform::Transform(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Component(
    pOwnerEntity, pOwnerComponent,
    true, true,
    slotIndex, type
  ),
  _position(Vector3f(0.0f, 0.0f, 0.0f)),
  _rotation(Vector3f(0.0f, 0.0f, 0.0f)),
  _scale(Vector3f(1.0f, 1.0f, 1.0f)),
  _worldUp(0.0f, 1.0f, 0.0f)
{
}

Transform::~Transform() noexcept
{}


void Transform::SetRotation(Vector3f rotation) 
{ 
  // Set rotation angles
  _rotation = rotation; 

  // Recalculate directions
  _zDir.SetX(cos(_rotation.GetX()) * cos(_rotation.GetY()));
  _zDir.SetY(sin(_rotation.GetY()));
  _zDir.SetZ(sin(_rotation.GetX()) * cos(_rotation.GetY()));
  _zDir = Normalize(_zDir);

  _xDir = Normalize(Cross(_worldUp, _zDir));
  _yDir = Normalize(Cross(_zDir, _xDir));
}