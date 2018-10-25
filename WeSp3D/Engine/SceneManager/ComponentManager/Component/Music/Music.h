#pragma once

#include "Component.h"

namespace WeSp {

class Music :
  public Component,
  public IComponentState
{
public:
  Music();
  ~Music();
};

}