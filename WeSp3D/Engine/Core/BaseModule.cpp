#include "BaseModule.h"

using namespace WeSp;


BaseModule::BaseModule(int magicNumber) :
  _parentModule(*this),
  _pEngineApi(nullptr)
{
  // Test if magic number matches
  if (magicNumber != MAGIC_BASE_MODULE_NUMBER)
  {
    DLog(eLogType::Error, "Default BaseModule constructor called from non-root module!");
    assert(magicNumber == MAGIC_BASE_MODULE_NUMBER);
  }
}

BaseModule::BaseModule(BaseModule &parentModule):
  _parentModule(parentModule),
  _pEngineApi(nullptr)
{}


BaseModule::~BaseModule()
{}

void BaseModule::SetEngineApiPointer(const EngineApi* const pEngineApi)
{
  _pEngineApi = pEngineApi;
  return;
}
