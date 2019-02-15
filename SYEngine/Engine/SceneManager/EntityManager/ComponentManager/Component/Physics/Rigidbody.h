#pragma once

#include "CommonValues.h"
#include "Component.h"


namespace SYE {

class Rigidbody:
  public Component
{
public:
  Rigidbody() = delete;
  Rigidbody(Entity* pOwnerEntity) noexcept;
  ~Rigidbody() noexcept;


private:
  
};

}