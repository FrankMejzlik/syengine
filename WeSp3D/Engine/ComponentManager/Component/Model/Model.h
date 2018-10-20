#pragma once

#include <vector>
#include <string>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

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

  virtual void LoadModel(const std::string& fileName);
  virtual void RenderModel();
  virtual void ClearModel();

protected: 
  std::vector<Mesh*> _meshList;
  std::vector<Texture*> _textureList;
  std::vector<unsigned int> _meshToTexture;
  
  virtual void LoadNode(aiNode* node, const aiScene* scene);
  virtual void LoadMesh(aiMesh* mesh, const aiScene* scene);
  virtual void LoadMaterials(const aiScene* scene);
};

}