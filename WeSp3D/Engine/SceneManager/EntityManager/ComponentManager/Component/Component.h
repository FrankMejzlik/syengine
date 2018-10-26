#pragma once

#include "IComponentState.h"
#include "IGuidCounted.h"

namespace WeSp
{

class Component:
  public IComponentState, public IGuidCounted
{
public:
  Component();
  ~Component();

protected:

};

}