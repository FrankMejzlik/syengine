#include "EngineContext.h"

using namespace WeSp;

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

