#pragma once

#define INVALID_MATERIAL 0xFFFFFFFF

#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* ASSIMP headers */
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Logger.h"
#include "Model.h"

namespace WeSp
{

enum VB_TYPES 
{
  INDEX_BUFFER,
  POS_VB,
  NORMAL_VB,
  TEXCOORD_VB,
  BONE_VB,
  NUM_VBs
};


#define NUM_BONES_PER_VERTEX 4

struct BoneInfo
{
  glm::mat4 BoneOffset;
  glm::mat4 FinalTransformation;

  BoneInfo()
  {
    BoneOffset = glm::mat4(0.0f);
    FinalTransformation = glm::mat4(0.0f);
  }
};

struct VertexBoneData
{
  unsigned int IDs[NUM_BONES_PER_VERTEX];
  float Weights[NUM_BONES_PER_VERTEX];

  VertexBoneData()
  {
    Reset();
  }

  void Reset()
  {
    for (unsigned int i = 0; i < NUM_BONES_PER_VERTEX; ++i)
    {
      IDs[i] = 0;
      Weights[i] = 0;
    }
  }

  void AddBoneData(unsigned int BoneID, float Weight);
};

struct MeshEntry {
  MeshEntry()
  {
    NumIndices = 0;
    BaseVertex = 0;
    BaseIndex = 0;
    MaterialIndex = INVALID_MATERIAL;
  }

  unsigned int NumIndices;
  unsigned int BaseVertex;
  unsigned int BaseIndex;
  unsigned int MaterialIndex;
};

class AnimatedModel :
  public Model
{
public:
  AnimatedModel();
  ~AnimatedModel();
  bool LoadModel(const std::string& fileName);
  bool InitFromScene(const aiScene* pScene, const std::string& fileName);
  void InitMesh(
    unsigned int MeshIndex,
    const aiMesh* paiMesh,
    std::vector<glm::vec3>& Positions,
    std::vector<glm::vec3>& Normals,
    std::vector<glm::vec2>& TexCoords,
    std::vector<VertexBoneData>& Bones,
    std::vector<unsigned int>& Indices
  );
  void RenderModel();
  void ClearModel();
  void Clear();

  

  void Render(const GLuint& shaderProgram);


  const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);
  void BoneTransform(float timeInSeconds, std::vector<glm::mat4>& Transforms);
  void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform);
  void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
  void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
  void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
  unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
  unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
  unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);


private:

  std::vector<Texture*> _textureList;
  std::vector<unsigned int> _meshToTex;

  GLuint m_VAO;
  GLuint m_Buffers[NUM_VBs];
  GLuint m_ColorBuffer;
  std::vector<glm::vec3> Colors;

  const aiScene* _pScene;
  Assimp::Importer _importer;
  double animDuration;
   

  std::vector<MeshEntry> _entries;
  std::vector<GLuint> _textures;

  std::map<std::string, unsigned int> _boneMapping; // maps a bone name to its index
  unsigned int _numBones;
  std::vector<BoneInfo> _boneInfo;
  glm::mat4 _globalInverseTransform;

  bool InitMaterials(const aiScene* pScene, const std::string& Filename);
  void LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones);

};

}
