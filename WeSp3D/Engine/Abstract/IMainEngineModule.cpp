#include "IMainEngineModule.h"

using namespace WeSp;

IMainEngineModule::IMainEngineModule(Engine* pParentInstance) :
  _pParentInstance(pParentInstance)
{}

IMainEngineModule::~IMainEngineModule() {}

bool IMainEngineModule::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // If no modules send in
  if (modules.size() <= 0)
  {
    DLog(eLogType::Error, "Empty module container send to initialize main module.")
    return false;
  }
  _modules = modules;
  return true;
}

bool IMainEngineModule::Terminate()
{
  // Do all base terminating stuff
  return true;
}
