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

  std::shared_ptr<Model> CreateModel(std::shared_ptr<Entity> pEntity, std::shared_ptr<Mesh> pQuadMesh, std::shared_ptr<Texture> pTexture, std::shared_ptr<Shininess> pShininess);
  std::shared_ptr<Model> CreateModelFromFile(std::shared_ptr<Entity> pEntity, std::string filePath);


private:
  std::unordered_map<std::string, std::shared_ptr<Model>> _loadedModels;

};

}