#pragma once

#include <map>
#include <memory>

#include "common.h"
#include "BaseModule.h"

// Component managers.
#include "ControllerManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "ModelManager.h"
#include "SkyboxManager.h"
#include "TextureManager.h"

// Components.
#include "Mesh.h"
#include "Model.h"

namespace WeSp 
{

class ComponentManager:
    public BaseModule
{
public:
  ComponentManager() = delete;

  ComponentManager(BaseModule &parentModule);
  ~ComponentManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


  std::shared_ptr<TextureManager> GetTextureManager() const { return _pTextureManager;  }
  

  std::shared_ptr<Mesh> GenerateMeshQuad(dfloat width, dfloat height);
  std::shared_ptr<Mesh> GenerateMeshBlock(dfloat width, dfloat height, dfloat length);

  std::shared_ptr<Model> CreateModel(
    std::shared_ptr<Entity> pEntity,
    std::shared_ptr<Mesh> pQuadMesh,
    std::shared_ptr<Texture> pTexture = nullptr, 
    std::shared_ptr<Shininess> pShininess = nullptr
  );

  std::shared_ptr<Model> CreateModelFromFile(
    std::shared_ptr<Entity> pEntity,
    std::string filePath
  );

  std::shared_ptr<TextureManager> _pTextureManager;
};

} // namespace WeSp