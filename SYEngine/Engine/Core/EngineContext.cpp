#include "EngineContext.h"

using namespace SYE;

bool EngineContext::gTorchOn = false;

EngineContext::EngineContext():
  _bShouldRun(true)
{}

bool EngineContext::GetBShouldRun() const
{
  return _bShouldRun;
}

void EngineContext::SetBShouldRun(bool newValue)
{
  _bShouldRun = newValue;
}

