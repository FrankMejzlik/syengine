#pragma once

#include "IMainEngineModule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

#include "Scene.h"

using namespace WeSp;

namespace WeSp {

class SceneManager :
  public IMainEngineModule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  SceneManager() = delete;

  SceneManager(Engine* pParentInstance);
  ~SceneManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules) override;
  virtual bool Terminate() override;
};

}