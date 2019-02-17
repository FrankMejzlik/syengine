#pragma once
#include "Component.h"

namespace SYE {

class PhysicsMaterial :
  public Component
{
public:
  PhysicsMaterial() = delete;

  PhysicsMaterial(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots);
  virtual ~PhysicsMaterial();
};

}