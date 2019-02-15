#pragma once

#include <memory>
#include <vector>

#include "IGuidCounted.h"


namespace SYE
{
class Entity;

class Component:
  public IGuidCounted
{
public:
  Component() = delete;
  Component(Entity* pOwnerEntity) noexcept;
  virtual ~Component() noexcept = default;

  Entity* GetOwnerEntityPtr() const;
  Entity* SetOwnerEntityPtr(Entity* newOwnerPtr);

  bool GetIsPrimary() const;
  bool SetIsPrimary(bool newValue);


protected:
  /** Pointer to Entity that owns this Component. */
  Entity* _pOwnerEntity;

  /** If this Component can be directly placed on Entity. */
  bool _isPrimary;
  
};

}