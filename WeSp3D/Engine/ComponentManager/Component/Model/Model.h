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

  void LoadModel(const std::string& fileName);
  void RenderModel();
  void ClearModel();


  ~Model();

protected: 

  void LoadNode(aiNode* node, const aiScene* scene);
  void LoadMesh(aiMesh* mesh, const aiScene* scene);
  void LoadMaterials(const aiScene* scene);


  std::vector<Mesh*> meshList;
  std::vector<Texture*> textureList;
  std::vector<unsigned int> meshToTex;
};


}