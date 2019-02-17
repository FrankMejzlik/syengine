#pragma once
#include "Component.h"

namespace SYE {

class Logic :
  public Component
{
public:
  Logic() = delete;

  Logic(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots);
  virtual ~Logic();
};

}