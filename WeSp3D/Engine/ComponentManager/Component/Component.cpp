#include "Component.h"

using namespace WeSp;

// Initialize static attributes
size_t Component::_componentCounter = 0;
size_t Component::_nextGUID = 0;


Component::Component():
  _GUID(_nextGUID)
{
  ++_nextGUID;
  ++_componentCounter;
}

Component::~Component()
{
  --_componentCounter;
}


size_t Component::GetComponentCount() const
{
  return _componentCounter;
}

size_t Component::GetGUID() const
{
  return _GUID;
}