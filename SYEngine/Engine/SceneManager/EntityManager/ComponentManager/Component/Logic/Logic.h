#pragma once
#include "Component.h"

namespace SYE {

class Logic :
  public Component
{
public:
  Logic() = delete;

  Logic(Entity* pEntity);
  virtual ~Logic();
};

}