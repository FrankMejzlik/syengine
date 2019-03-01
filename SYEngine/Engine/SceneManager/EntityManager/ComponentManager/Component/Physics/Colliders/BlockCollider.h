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
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = PHYSICS_COLLIDER, Component::eType type = eType::BLOCK_COLLIDER
  );
  virtual ~BlockCollider() noexcept = default;

  void SetDimensions(dfloat width, dfloat height, dfloat length);
  Vector3f GetDimensions() const { return Vector3f(_width, _height, _length); }

  // Attributes
protected:
  dfloat _width;
  dfloat _height;
  dfloat _length;

};

} // namespace SYE