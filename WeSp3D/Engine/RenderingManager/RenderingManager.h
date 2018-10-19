#pragma once

#include "IMainEngineModule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

// Include submodules
#include "AnimationManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "ShadowManager.h"
#include "SkyboxManager.h"
#include "TextureManager.h"
#include "WindowManager.h"

using namespace WeSp;

namespace WeSp {

class RenderingManager :
  public IMainEngineModule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  RenderingManager() = delete;

  RenderingManager(Engine* pParentInstance);
  ~RenderingManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules) override;
  virtual bool Terminate() override;

private:
  std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> _subModules;
};

}
