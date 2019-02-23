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
  Softbody(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept;
  ~Softbody() noexcept;


  BlockCollider* AddBlockCollider(dfloat width, dfloat height, dfloat length);
  BlockCollider* AddSphereCollider(dfloat radius);


private:
  
};

}