#pragma once
#include "Component.h"

namespace SYE {

class Logic :
  public Component
{
public:
  Logic() = delete;

  Logic(std::shared_ptr<Entity> pEntity);
  virtual ~Logic();
};

}