#include "Model.h"

using namespace SYE;


Model::Model(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef):
  Component(pOwnerEntity, subModulesConstRef)
{
  _type = eType::MODEL;
}

void Model::LoadModelFromFile(std::string_view fileName)
{
  Assimp::Importer importer;
  const aiScene* pScene = importer.ReadFile(fileName.data(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
  if (!pScene)
  {
    printf("Model (%s) failed to load: %s\n", fileName.data(), importer.GetErrorString());
    return;
  }

  LoadNode(pScene->mRootNode, pScene);
  LoadMaterials(pScene);
}

void Model::RenderModel(GLuint ul_modelToWorldMatrix, Entity* pOwner)
{

  glm::mat4 modelToWorldMatrix;
  modelToWorldMatrix = std::move(glm::mat4(1.0f));
  modelToWorldMatrix = glm::translate(modelToWorldMatrix, pOwner->GetPositionVectorRefConst());
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, pOwner->GetRotationVectorRefConst().z, glm::vec3(0.0f, 0.0f, 1.0f));
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, pOwner->GetRotationVectorRefConst().y, glm::vec3(0.0f, 1.0f, 0.0f));
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, pOwner->GetRotationVectorRefConst().x, glm::vec3(1.0f, 0.0f, 0.0f));
  modelToWorldMatrix = glm::scale(modelToWorldMatrix, pOwner->GetScaleVectorRefConst());

  glUniformMatrix4fv(ul_modelToWorldMatrix, 1, GL_FALSE, glm::value_ptr(modelToWorldMatrix));

  for (size_t i = 0; i < _meshList.size(); ++i)
  {
    size_t materialIndex = _meshToTexture[i];

    if (materialIndex < _textureList.size() && _textureList[materialIndex])
    {
      _textureList[materialIndex]->UseTexture();
    }

    _meshList[i]->RenderMesh();
  }
}

void Model::ClearModel()
{
  for (size_t i = 0; i < _meshList.size(); ++i)
  {
    if (_meshList[i])
    {
      //delete _meshList[i];
      _meshList[i] = nullptr;
    }
  }

  for (size_t i = 0; i < _textureList.size(); ++i)
  {
    if (_textureList[i])
    {
      //delete _textureList[i];
      _textureList[i] = nullptr;
    }
  }
}

size_t Model::AddMesh(std::shared_ptr<Mesh> pNewMesh)
{
  _meshList.push_back(pNewMesh);
  
  _meshToTexture.push_back(0);
  _meshToShininess.push_back(0);
  
  return _meshList.size() - 1;
}

size_t Model::AddTexture(std::shared_ptr<Texture> pNewTexture)
{
  _textureList.push_back(pNewTexture);

  return _textureList.size() - 1;
}

size_t Model::AddShininess(std::shared_ptr<_Shininess> pNewShininess)
{
  _shininesList.push_back(pNewShininess);

  return _shininesList.size() - 1;
}

void Model::SetMeshIndexToTexture(size_t meshIndex, size_t textureIndex)
{
  _meshToTexture[meshIndex] = textureIndex;
  return;
}

void Model::SetMeshIndexToShininess(size_t meshIndex, size_t shininessIndex)
{
  _meshToShininess[meshIndex] = shininessIndex;
  return;
}

void Model::LoadNode(aiNode * node, const aiScene * scene)
{
  for (size_t i = 0; i < node->mNumMeshes; ++i)
  {
    LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
  }

  for (size_t i = 0; i < node->mNumChildren; ++i)
  {
    LoadNode(node->mChildren[i], scene);
  }
}

void Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
  UNREFERENCED_PARAMETER(scene);

  std::vector<GLfloat> vertices;
  std::vector<unsigned int> indices;

  for (size_t i = 0; i < mesh->mNumVertices; ++i)
  {
    vertices.insert(
      vertices.end(),
      { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z }
    );

    if (mesh->mTextureCoords[0])
    {
      vertices.insert(
        vertices.end(),
        { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y }
      );
    }
    else
    {
      vertices.insert( vertices.end(), { 0.0f, 0.0f });
    }
    vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
  }

  for (size_t i = 0; i < mesh->mNumFaces; ++i)
  {
    aiFace face = mesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; ++j)
    {
      indices.push_back(face.mIndices[j]);
    }
  }

  std::shared_ptr<Mesh> pNewMesh = std::make_shared<Mesh>(_pOwnerEntity, _subModules);
  pNewMesh->CreateMesh(vertices, indices, true);
  _meshList.push_back(pNewMesh);

  _meshToTexture.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene * scene)
{
  _textureList.resize(scene->mNumMaterials);

  for (size_t i = 0; i < scene->mNumMaterials; ++i)
  {
    aiMaterial* material = scene->mMaterials[i];
    _textureList[i] = nullptr;

    // TODO: Support more types of textures.
    if (material->GetTextureCount(aiTextureType_DIFFUSE))
    {
      aiString path;
      if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
      {
        // If models were exported with absolute values, get just last \ part
        size_t idx = std::string(path.data).rfind("\\");
        std::string filename = std::string(path.data).substr(idx + 1);

        std::string texPath = std::string(CONCATENATE_LITERALS(PATH_TEXTURES, "/")) + filename;

        //_textureList[i] = new Texture(texPath.c_str());
        _textureList[i] = std::make_shared<Texture>(_pOwnerEntity, _subModules, texPath.c_str());

        if (!_textureList[i]->LoadTexture())
        {
          printf("Failed to load texture at: %s\n", texPath.c_str()); 
          //delete _textureList[i];
          _textureList[i] = nullptr;

        }

      }
    }
    // If no texture loaded.
    else
    {
      // Load default texture.
      //_textureList[i] = new Texture(CONCATENATE_DEFINES(PATH_TEXTURES, FILENAME_DEFAULT_TEXTURE));
      _textureList[i] = std::make_shared<Texture>(_pOwnerEntity, _subModules, CONCATENATE_DEFINES(PATH_TEXTURES, FILENAME_DEFAULT_TEXTURE));
      _textureList[i]->LoadTexture();
    }
  }
}
