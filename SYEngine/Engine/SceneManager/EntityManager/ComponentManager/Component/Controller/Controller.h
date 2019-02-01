#pragma once

#include <memory>

#include "common.h"
#include "Component.h"

namespace SYE
{

class Controller :
  public Component
{
public:
  Controller() = delete;

  Controller(Entity* pEntity);
  ~Controller();
};

} // namespace SYE
