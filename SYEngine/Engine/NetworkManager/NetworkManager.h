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

  NetworkManager(BaseModule &parentModule);
  ~NetworkManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void ProcessScene(dfloat deltaTime, Scene* pScene);

};

}
