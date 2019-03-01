#pragma once

#include "common.h"
#include "PhysicsBody.h"


namespace SYE 
{

class BlockCollider;

class Softbody:
  public PhysicsBody
{
public:
  Softbody() = delete;
  Softbody(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = PHYSICS_BODY, Component::eType type = eType::SOFT_BODY
  );
  ~Softbody() noexcept;


  BlockCollider* AddBlockCollider(dfloat width, dfloat height, dfloat length);
  BlockCollider* AddSphereCollider(dfloat radius);


private:
  
};

}