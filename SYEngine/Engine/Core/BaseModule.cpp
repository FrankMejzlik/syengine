#include "BaseModule.h"

using namespace SYE;


BaseModule::BaseModule(int magicNumber) :
  _parentModule(*this),
  _pEngineApi(nullptr),
  _pEngineContext(nullptr)
{
  // Test if magic number matches
  if (magicNumber != MAGIC_BASE_MODULE_NUMBER)
  {
    DLog(eLogType::Error, "Default BaseModule constructor called from non-root module!");
    assert(magicNumber == MAGIC_BASE_MODULE_NUMBER);
  }
}

BaseModule::BaseModule(BaseModule& parentModule, EngineContext* pEngineContext):
  _parentModule(parentModule),
  _pEngineContext(pEngineContext),
  _pEngineApi(nullptr)
{}


void BaseModule::SetEngineApiPointer(const EngineApi* const pEngineApi)
{
  _pEngineApi = pEngineApi;
  return;
}
