#pragma once

#include "Component.h"

namespace SYE {

class Sound:
  public Component
{
public:
  Sound() = delete;
  Sound(Entity* pEntity);
  ~Sound();
};

}