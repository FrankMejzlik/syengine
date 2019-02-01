#pragma once

#include <memory>
#include <vector>

#include "IComponentState.h"
#include "IGuidCounted.h"


namespace SYE
{
class Entity;

class Component:
  public IComponentState, public IGuidCounted
{
public:
  Component() = delete;

  Component(Entity* pEntity);
  ~Component();

  Entity* GetOwner() const
  {
    return _pEntity;
  };

protected:
  // Pointer to Entity that owns this Component.
  Entity* _pEntity;
  // Connected Components.
  std::vector<std::shared_ptr<Component>> _connectedComponents;

};

}