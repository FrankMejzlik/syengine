#pragma once

#include "IComponentState.h"

namespace WeSp
{

class Component:
  public IComponentState
{
public:
  Component();
  ~Component();

  size_t GetComponentCount() const;
  size_t GetGUID() const;

protected:
  static size_t _componentCounter;
  static size_t _nextGUID;

  // Global Unique ID
  size_t _GUID;
};

}