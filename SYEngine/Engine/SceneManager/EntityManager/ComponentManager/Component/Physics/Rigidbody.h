#pragma once

#include "CommonValues.h"
#include "Component.h"


namespace SYE {

class Rigidbody:
  public Component
{
public:
  Rigidbody() = delete;
  Rigidbody(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept;
  ~Rigidbody() noexcept;


private:
  
};

}