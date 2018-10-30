#pragma once

#include "Component.h"

namespace SYE {

class Sound:
  public IComponentState
{
public:
  Sound() = delete;
  Sound(std::shared_ptr<Entity> pEntity);
  ~Sound();
};

}