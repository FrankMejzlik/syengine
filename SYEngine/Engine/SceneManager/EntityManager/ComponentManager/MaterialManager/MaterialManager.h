#pragma once


#include <map>

#include "BaseModule.h"


using namespace SYE;

namespace SYE 
{

class MaterialManager :
  public BaseModule
{
public:
  MaterialManager() = delete;

  MaterialManager(BaseModule &parentModule);
  ~MaterialManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

private:

};

}