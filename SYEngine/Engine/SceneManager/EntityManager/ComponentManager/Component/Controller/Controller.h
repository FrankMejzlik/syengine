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

  Controller(std::shared_ptr<Entity> pEntity);
  ~Controller();
};

} // namespace SYE
