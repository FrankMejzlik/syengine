#pragma once

#include "Component.h"

namespace SYE {

class MeshRenderer:
  public Component
{
public:
  MeshRenderer() = delete;
  MeshRenderer(Entity* pEntity);
  ~MeshRenderer();
};

}