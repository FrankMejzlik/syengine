#pragma once

#include "common.h"
#include "BaseModule.h"
#include "Model.h"

using namespace WeSp;

namespace WeSp 
{

class ModelManager :
  public BaseModule
{
public:
  ModelManager() = delete;

  ModelManager(BaseModule &parentModule);
  ~ModelManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  std::shared_ptr<Model> CreateModel(std::shared_ptr<Mesh> pQuadMesh, std::shared_ptr<Texture> pTexture, std::shared_ptr<Shininess> pShininess);


private:

};

}