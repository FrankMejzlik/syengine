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

void EngineContext::SetModule(size_t indexKey, BaseModule* pModule)
{
  _pModules.insert(std::make_pair(indexKey, pModule));
}

BaseModule* EngineContext::GetModule(size_t indexKey) const
{
  return _pModules.at(indexKey);
}