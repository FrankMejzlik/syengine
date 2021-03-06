#pragma once

#include "common.h"
#include "BaseModule.h"
#include "Texture.h"

using namespace SYE;

namespace SYE 
{

class TextureManager :
  public BaseModule
{
public:
  TextureManager() = delete;

  TextureManager(BaseModule &parentModule, EngineContext* pEngineContext);
  ~TextureManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  std::unique_ptr<Texture> CreateDefaultTexture();

private:

  
};

}