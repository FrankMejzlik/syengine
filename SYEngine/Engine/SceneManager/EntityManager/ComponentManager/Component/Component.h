#pragma once

#include <memory>
#include <vector>

#include "IComponentState.h"
#include "IGuidCounted.h"


namespace WeSp
{
class Entity;

class Component:
  public IComponentState, public IGuidCounted
{
public:
  Component() = delete;

  Component(std::shared_ptr<Entity> pEntity);
  ~Component();

protected:
  // Pointer to Entity that owns this Component.
  std::shared_ptr<Entity> _pEntity;
  // Connected Components.
  std::vector<std::shared_ptr<Component>> _connectedComponents;

};

}