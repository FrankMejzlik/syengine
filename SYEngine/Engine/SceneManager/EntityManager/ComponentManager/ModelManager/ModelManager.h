#pragma once

#include "common.h"
#include "BaseModule.h"
#include "Model.h"

using namespace SYE;

namespace SYE 
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

  std::unique_ptr<Model> CreateModel(Entity* pEntity, std::unique_ptr<Mesh>&& pQuadMesh, std::unique_ptr<Texture>&& pTexture, std::unique_ptr<Shininess>&& pShininess);
  std::unique_ptr<Model> CreateModelFromFile(Entity* pEntity, std::string filePath);


private:

};

}