#pragma once

#include <vector>
#include <string>
#include <memory>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#pragma warning(push, 1)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)



#include "Logger.h"
#include "Component.h"
#include "Mesh.h"
#include "Texture.h"
#include "Entity.h"


using namespace SYE;

namespace SYE 
{

class Model:
  public Component
{
public:
  Model() = delete;
  Model(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef);
  virtual ~Model() = default;

  virtual void LoadModelFromFile(std::string_view fileName);
  virtual void RenderModel(GLuint ul_modelToWorldMatrix, Entity* pOwner);
  virtual void ClearModel();


  size_t AddMesh(std::shared_ptr<Mesh> pNewMesh);
  size_t AddTexture(std::shared_ptr<Texture> pNewTexture);
  size_t AddShininess(std::shared_ptr<_Shininess> pNewShininess);

  void SetMeshIndexToTexture(size_t meshIndex, size_t textureIndex);
  void SetMeshIndexToShininess(size_t meshIndex, size_t shininessIndex);

protected: 
  std::vector<std::shared_ptr<Mesh>> _meshList;
  std::vector<std::shared_ptr<Texture>> _textureList;
  std::vector<std::shared_ptr<_Shininess>> _shininesList;
  std::vector<size_t> _meshToTexture;
  // TODO!: Shininess not applied to render.
  std::vector<size_t> _meshToShininess;
  
  virtual void LoadNode(aiNode* node, const aiScene* scene);
  virtual void LoadMesh(aiMesh* mesh, const aiScene* scene);
  virtual void LoadMaterials(const aiScene* scene);



};

}