#pragma once

#include "common.h"
#include "Collider.h"

namespace SYE
{

class SphereCollider :
  public Collider
{
public:
  SphereCollider() = delete;
  SphereCollider(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = PHYSICS_COLLIDER, Component::eType type = eType::SPHERE_COLLIDER
  );
  virtual ~SphereCollider() noexcept = default;

  void SetDimensions(dfloat radius, size_t numSlices, size_t numStacks);
  dfloat GetRadius() const { return _radius; }
  size_t GetSliceCount()const { return _numSlices; }
  size_t GetStackCount()const { return _numStacks; }

  // Attributes
protected:
  dfloat _radius;
  size_t _numSlices;
  size_t _numStacks;

};

} // namespace SYE