//#pragma once
//
//#define POSITION_LOCATION    0
//#define TEX_COORD_LOCATION   1
//#define NORMAL_LOCATION      2
//#define BONE_ID_LOCATION     3
//#define BONE_WEIGHT_LOCATION 4
//
//#define INVALID_MATERIAL 0xFFFFFFFF
//
//#define NUM_BONES_PER_VERTEX 4
//
//#include <map>
//#include <iostream>
//
//#pragma warning(push, 1)
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#pragma warning(pop)
//
//
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//#include "Model.h"
//
//using namespace SYE;
//
//namespace SYE
//{
//
//enum eVertexBufferType
//{
//  INDEX_BUFFER,
//  POS_VB,
//  NORMAL_VB,
//  TEXCOORD_VB,
//  BONE_VB,
//  NUM_VBs
//};
//
//struct MeshEntry
//{
//  MeshEntry()
//  {
//    m_numIndices = 0;
//    m_baseVertex = 0;
//    m_baseIndex = 0;
//    m_materialIndex = INVALID_MATERIAL;
//  }
//
//  unsigned int m_numIndices;
//  unsigned int m_baseVertex;
//  unsigned int m_baseIndex;
//  unsigned int m_materialIndex;
//};
//
//struct BoneInfo
//{
//  glm::mat4 BoneOffset;
//  glm::mat4 FinalTransformation;
//
//  BoneInfo();
//};
//
//struct VertexBoneData
//{
//  /* de pastrat numarul de elemente al IDs & Weights */
//  unsigned int IDs[NUM_BONES_PER_VERTEX];
//  float Weights[NUM_BONES_PER_VERTEX];
//
//  VertexBoneData();
//
//  void Reset();
//
//  void AddBoneData(unsigned int BoneID, float Weight);
//};
//
//
//class SkeletalModel :
//  public Model
//{
//public:
//  SkeletalModel() = delete;
//
//  SkeletalModel(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots);
//  ~SkeletalModel();
//
//  /**
//   * Loads skeleton model from specified file.
//   */
//  virtual void LoadModelFromFile(std::string_view fileName) override;
//
//  void render(GLuint shaderId);
//
//  unsigned int GetNumBones() const
//  {
//    return m_NumBones;
//  }
//
//  void boneTransform(float timeInSeconds, std::vector<glm::mat4>& Transforms);
//
//protected:
//  std::vector<MeshEntry> m_Entries;
//  std::vector<GLuint> m_Textures;
//
//  std::map<std::string, unsigned int> m_BoneMapping; // maps a bone name to its index
//  unsigned int m_NumBones;
//  std::vector<BoneInfo> m_BoneInfo;
//  glm::mat4 m_GlobalInverseTransform;
//
//  /* duration of the animation, can be changed if frames are not present in all interval */
//  double animDuration;
//
//  const aiScene* m_pScene;
//  ::Assimp::Importer* m_Importer;
//
//  
//
//  void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//  void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//  void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//  unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
//  unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
//  unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
//  const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);
//  void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform);
//  bool InitFromScene(const aiScene* pScene, const std::string& Filename);
//  void InitMesh(unsigned int MeshIndex,
//    const aiMesh* paiMesh,
//    std::vector<glm::vec3>& Positions,
//    std::vector<glm::vec3>& Normals,
//    std::vector<glm::vec2>& TexCoords,
//    std::vector<VertexBoneData>& Bones,
//    std::vector<unsigned int>& Indices);
//  void LoadBones(unsigned int MeshIndex, const aiMesh* paiMesh, std::vector<VertexBoneData>& Bones);
//  bool InitMaterials(const aiScene* pScene, const std::string& Filename);
//  void Clear();
//
//  
//
//
//  std::vector<unsigned int> meshToTex;
//
//  std::vector<Texture*> _textures;
//  GLuint m_VAO;
//  GLuint m_Buffers[NUM_VBs];
//  GLuint m_ColorBuffer;
//  std::vector<glm::vec3> Colors;
//
//  
//
//  
//};
//
//}