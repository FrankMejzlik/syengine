#pragma once

#include "BaseModule.h"

using namespace WeSp;

namespace WeSp {

class ModelManager :
  public BaseModule
{
public:
  ModelManager() = delete;

  ModelManager(BaseModule &parentModule);
  ~ModelManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}