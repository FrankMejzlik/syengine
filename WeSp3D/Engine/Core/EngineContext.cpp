#include "EngineContext.h"

using namespace WeSp;

bool EngineContext::gTorchOn = false;

EngineContext::EngineContext():
  _bShouldRun(true)
{}

bool WeSp::EngineContext::GetBShouldRun()
{
  return _bShouldRun;
}

