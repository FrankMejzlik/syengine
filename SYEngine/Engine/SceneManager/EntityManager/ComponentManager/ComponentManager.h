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
#include "Collider/BlockCollider.h"

// Components.
#include "Mesh.h"
#include "Model.h"

namespace SYE 
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

  TextureManager* GetTextureManager() const { return _pTextureManager;  }
  
  std::unique_ptr<Mesh> GenerateMeshQuad(dfloat width, dfloat height);
  std::unique_ptr<Mesh> GenerateMeshBlock(dfloat width, dfloat height, dfloat length);

  Component* CreateBoxCollider(
    Entity* pEntity,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,
    dfloat width,
    dfloat heigt,
    dfloat length,
    bool bIsStatic
  );

  Component* CreateModel(
    Entity* pEntity,
    std::unique_ptr<Mesh>&& pQuadMesh,
    std::unique_ptr<Texture>&& pTexture = nullptr,
    std::unique_ptr<Shininess>&& pShininess = nullptr
  );

  Component* CreateModelFromFile(
    Entity* pEntity,
    std::string filePath
  );

private:
  Component* InsertComponent(std::unique_ptr<Component>&& pNewComponent);


private:



  TextureManager* _pTextureManager;

  std::map<size_t, std::unique_ptr<Component>> _components;

};

} // namespace SYE