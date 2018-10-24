#include "Model.h"

using namespace WeSp;

Model::Model()
{}

void Model::LoadModel(const std::string & fileName)
{
  Assimp::Importer importer;
  const aiScene* pScene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
  if (!pScene)
  {
    printf("Model (%s) failed to load: %s\n", fileName.c_str(), importer.GetErrorString());
    return;
  }

  LoadNode(pScene->mRootNode, pScene);
  LoadMaterials(pScene);
}

void Model::RenderModel()
{
  for (size_t i = 0; i < _meshList.size(); ++i)
  {
    unsigned int materialIndex = _meshToTexture[i];

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
      delete _meshList[i];
      _meshList[i] = nullptr;
    }
  }

  for (size_t i = 0; i < _textureList.size(); ++i)
  {
    if (_textureList[i])
    {
      delete _textureList[i];
      _textureList[i] = nullptr;
    }
  }
}


Model::~Model()
{}

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

void Model::LoadMesh(aiMesh * mesh, const aiScene * scene)
{
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

  Mesh* newMesh = new Mesh();
  newMesh->CreateMesh(vertices, indices);
  _meshList.push_back(newMesh);

  _meshToTexture.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene * scene)
{
  _textureList.resize(scene->mNumMaterials);

  for (size_t i = 0; i < scene->mNumMaterials; ++i)
  {
    aiMaterial* material = scene->mMaterials[i];
    _textureList[i] = nullptr;

    if (material->GetTextureCount(aiTextureType_DIFFUSE))
    {
      aiString path;
      if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
      {
        // If models were exported with absolute values, get just last \ part
        int idx = std::string(path.data).rfind("\\");
        std::string filename = std::string(path.data).substr(idx + 1);

        std::string texPath = std::string("Resource/textures/") + filename;

        _textureList[i] = new Texture(texPath.c_str());

        if (!_textureList[i]->LoadTexture())
        {
          printf("Failed to load texture at: %s\n", texPath); 
          delete _textureList[i];
          _textureList[i] = nullptr;

        }

      }
    }
    else
    {
      _textureList[i] = new Texture("Resource/textures/plain.png");
      _textureList[i]->LoadTextureA();
    }
  }
}
