#include "EngineContext.h"

using namespace SYE;

EngineContext::EngineContext():
  _shouldRun(true)
{}

bool EngineContext::ShouldRun() const
{
  return _shouldRun;
}

void EngineContext::SetShouldRun(bool newValue)
{
  _shouldRun = newValue;
}

