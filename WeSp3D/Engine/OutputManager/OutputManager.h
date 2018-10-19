#pragma once

#include "IMainEngineModule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

using namespace WeSp;

namespace WeSp {

class OutputManager :
  public IMainEngineModule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  OutputManager() = delete;

  OutputManager(Engine* pParentInstance);
  ~OutputManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules) override;
  virtual bool Terminate() override;
};

}