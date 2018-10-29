#pragma once

#include "common.h"
#include "Component.h"

namespace WeSp
{

class Collider :
  public Component
{
public:
  Collider() = delete;
  
  Collider(std::shared_ptr<Entity> pEntity);
  virtual ~Collider();
};

} // namespace WeSp