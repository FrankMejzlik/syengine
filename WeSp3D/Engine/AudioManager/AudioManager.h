#pragma once

#include "IMainEngineModule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

using namespace WeSp;

namespace WeSp {

class AudioManager :
  public IMainEngineModule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  AudioManager() = delete;

  AudioManager(Engine* pParentInstance);
  ~AudioManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules) override;
  virtual bool Terminate() override;
};

}