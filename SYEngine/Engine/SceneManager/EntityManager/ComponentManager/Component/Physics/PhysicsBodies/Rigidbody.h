#pragma once

#include "common.h"
#include "PhysicsBody.h"


namespace SYE 
{

// Forward declarations
class BlockCollider;
class SphereCollider;
class ConvexHullCollider;

class Rigidbody:
  public PhysicsBody
{
public:
  Rigidbody() = delete;
  Rigidbody(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = PHYSICS_BODY, Component::eType type = eType::RIGID_BODY
  );
  ~Rigidbody() noexcept;

  virtual void SaveComponent() override;

  BlockCollider* AddBlockCollider(dfloat width, dfloat height, dfloat length);
  SphereCollider* AddSphereCollider(dfloat radius, size_t numSlices, size_t numStacks);
  ConvexHullCollider* AddConvexHullCollider(
    const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& p4,
    const Vector3f& p5, const Vector3f& p6, const Vector3f& p7, const Vector3f& p8
  );

private:
  
};

}