#pragma once

#include "CommonValues.h"
#include "Component.h"


namespace SYE {

class Rigidbody:
  public Component
{
public:
  Rigidbody() = delete;
  Rigidbody(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept;
  ~Rigidbody() noexcept;


private:
  
};

}