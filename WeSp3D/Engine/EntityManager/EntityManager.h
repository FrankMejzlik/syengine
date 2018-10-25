#pragma once

#include "BaseModule.h"

using namespace WeSp;

namespace WeSp {

class EntityManager :
  public BaseModule
{
public:
  EntityManager() = delete;

  EntityManager(BaseModule &parentModule);
  ~EntityManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}