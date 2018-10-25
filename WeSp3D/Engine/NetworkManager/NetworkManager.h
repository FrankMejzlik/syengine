#pragma once


#include "BaseModule.h"


using namespace WeSp;

namespace WeSp {

class NetworkManager :
  public BaseModule
{
public:
  NetworkManager() = delete;

  NetworkManager(BaseModule &parentModule);
  ~NetworkManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

};

}
