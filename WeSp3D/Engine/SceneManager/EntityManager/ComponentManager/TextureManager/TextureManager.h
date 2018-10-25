#pragma once

#include "common.h"
#include "BaseModule.h"
#include "Texture.h"

using namespace WeSp;

namespace WeSp 
{

class TextureManager :
  public BaseModule
{
public:
  TextureManager() = delete;

  TextureManager(BaseModule &parentModule);
  ~TextureManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  std::shared_ptr<Texture> GetDefaultTexture() const;

private:
  std::shared_ptr<Texture> _defaultTexture;
  
};

}