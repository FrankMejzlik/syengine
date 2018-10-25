#pragma once

#include "BaseModule.h"



namespace WeSp
{

class SimulationManager;

class LogicManager:
  public BaseModule
{
public:
  LogicManager() = delete;

  LogicManager(BaseModule &parentModule);
  ~LogicManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;
};

}