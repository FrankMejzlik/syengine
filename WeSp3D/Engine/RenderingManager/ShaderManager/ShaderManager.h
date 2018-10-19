#pragma once

#include "IRenderingManagerSubmodule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

using namespace WeSp;

namespace WeSp 
{

class RenderingManager;

class ShaderManager :
  public IRenderingManagerSubmodule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  ShaderManager() = delete;

  ShaderManager(RenderingManager* pParentInstance);
  ~ShaderManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> modules) override;
  virtual bool Terminate() override;
};

}