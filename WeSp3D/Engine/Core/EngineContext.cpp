#include "EngineContext.h"

using namespace WeSp;

bool EngineContext::gTorchOn = false;

EngineContext::EngineContext():
  _bShouldRun(true)
{}

bool EngineContext::GetBShouldRun()
{
  return _bShouldRun;
}

bool EngineContext::SetBShouldRun(bool newValue)
{
  _bShouldRun = newValue;
}

