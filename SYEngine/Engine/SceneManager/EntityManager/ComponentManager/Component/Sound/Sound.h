#pragma once

#include "Component.h"

namespace SYE {

class Sound:
  public Component
{
public:
  Sound() = delete;
  Sound(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef);
  ~Sound();
};

}