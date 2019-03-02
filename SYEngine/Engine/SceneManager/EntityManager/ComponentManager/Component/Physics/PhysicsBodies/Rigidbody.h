#pragma once

#include "common.h"
#include "PhysicsBody.h"


namespace SYE 
{

// Forward declarations
class BlockCollider;
class SphereCollider;

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


private:
  
};

}