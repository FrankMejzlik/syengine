#pragma once

#include "IRenderingManagerSubmodule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

using namespace WeSp;

namespace WeSp 
{

class RenderingManager;

class TextureManager :
  public IRenderingManagerSubmodule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  TextureManager() = delete;

  TextureManager(RenderingManager* pParentInstance);
  ~TextureManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> modules) override;
  virtual bool Terminate() override;
};

}