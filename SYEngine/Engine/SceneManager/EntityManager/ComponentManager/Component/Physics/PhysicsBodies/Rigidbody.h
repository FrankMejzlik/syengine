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
  Rigidbody(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept;
  ~Rigidbody() noexcept;

  virtual void SaveComponent() override;

  BlockCollider* AddBlockCollider(dfloat width, dfloat height, dfloat length);
  BlockCollider* AddSphereCollider(dfloat radius);


private:
  
};

}