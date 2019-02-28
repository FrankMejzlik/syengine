#pragma once


#include "BaseModule.h"
#include "Scene.h"


using namespace SYE;

namespace SYE {

class NetworkManager :
  public BaseModule
{
public:
  NetworkManager() = delete;

  NetworkManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~NetworkManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  bool InitializeScene(Scene* pScene);
  void ProcessScene(dfloat deltaTime, Scene* pScene);

};

}
