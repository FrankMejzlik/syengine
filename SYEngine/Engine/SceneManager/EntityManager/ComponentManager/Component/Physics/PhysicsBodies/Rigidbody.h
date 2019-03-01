#pragma once

#include "common.h"
#include "PhysicsBody.h"


namespace SYE 
{

class BlockCollider;

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
  BlockCollider* AddSphereCollider(dfloat radius);


private:
  
};

}