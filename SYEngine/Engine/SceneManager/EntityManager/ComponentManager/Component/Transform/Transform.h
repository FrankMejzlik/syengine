#pragma once

#include "CommonValues.h"
#include "Component.h"


namespace SYE {

class Transform:
  public Component
{
public:
  Transform() = delete;
  Transform(Entity* pOwnerEntity) noexcept;
  ~Transform() noexcept;


private:
  
};

}