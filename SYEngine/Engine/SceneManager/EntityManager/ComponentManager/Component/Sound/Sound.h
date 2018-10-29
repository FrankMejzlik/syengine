#pragma once

#include "Component.h"

namespace WeSp {

class Sound:
  public IComponentState
{
public:
  Sound() = delete;
  Sound(std::shared_ptr<Entity> pEntity);
  ~Sound();
};

}