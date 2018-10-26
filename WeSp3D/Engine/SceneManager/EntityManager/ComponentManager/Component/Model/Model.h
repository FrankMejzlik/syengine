#pragma once

#include <vector>
#include <string>
#include <memory>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Logger.h"
#include "Component.h"
#include "Mesh.h"
#include "Texture.h"


using namespace WeSp;

namespace WeSp 
{

class Model:
  public Component
{
public:
  Model();
  virtual ~Model();

  virtual void LoadModelFromFile(const std::string& fileName);
  virtual void RenderModel();
  virtual void ClearModel();


  size_t AddMesh(std::shared_ptr<Mesh> pNewMesh);
  size_t AddTexture(std::shared_ptr<Texture> pNewTexture);
  void SetMeshIndexToTexture(size_t meshIndex, size_t textureIndex);

protected: 
  std::vector<std::shared_ptr<Mesh>> _meshList;
  std::vector<std::shared_ptr<Texture>> _textureList;
  std::vector<std::shared_ptr<Shininess>> _shininesList;
  std::vector<size_t> _meshToTexture;
  std::vector<size_t> _meshToShininess;
  
  virtual void LoadNode(aiNode* node, const aiScene* scene);
  virtual void LoadMesh(aiMesh* mesh, const aiScene* scene);
  virtual void LoadMaterials(const aiScene* scene);



};

}