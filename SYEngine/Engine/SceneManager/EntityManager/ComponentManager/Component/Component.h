#pragma once

#include "IComponentState.h"
#include "IGuidCounted.h"
#include <memory>

namespace WeSp
{
class Entity;

class Component:
  public IComponentState, public IGuidCounted
{
public:
  Component();
  Component(std::shared_ptr<Entity> pEntity);
  ~Component();

protected:
  std::shared_ptr<Entity> _pEntity;
};

}