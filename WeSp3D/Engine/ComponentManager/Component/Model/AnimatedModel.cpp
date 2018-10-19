//
using namespace WeSp;

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

//// Helper functions
//glm::mat3 aiMatrix3x3ToGlm(const aiMatrix3x3 &from)
//{
//  glm::mat3 to;
//  //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
//  to[0][0] = from.a1; to[1][0] = from.a2;	to[2][0] = from.a3; 
//  to[0][1] = from.b1; to[1][1] = from.b2;	to[2][1] = from.b3; 
//  to[0][2] = from.c1; to[1][2] = from.c2;	to[2][2] = from.c3; 
//
//  return to;
//}
//
//glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4 &from)
//{
//  glm::mat4 to;
//  //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
//  to[0][0] = from.a1; to[1][0] = from.a2;	to[2][0] = from.a3; to[3][0] = from.a4;
//  to[0][1] = from.b1; to[1][1] = from.b2;	to[2][1] = from.b3; to[3][1] = from.b4;
//  to[0][2] = from.c1; to[1][2] = from.c2;	to[2][2] = from.c3; to[3][2] = from.c4;
//  to[0][3] = from.d1; to[1][3] = from.d2;	to[2][3] = from.d3; to[3][3] = from.d4;
//  return to;
//}
//



AnimatedModel::AnimatedModel()
{

  m_VAO = 0;
  for (unsigned int i = 0; i < NUM_VBs; ++i)
  {
    m_Buffers[i] = 0;
  }
  _numBones = 0;
  _pScene = NULL;
}


AnimatedModel::~AnimatedModel()
{}

bool AnimatedModel::LoadModel(const std::string& fileName)
{
  /* Deletes the previous loaded mesh(if it exists) */
  Clear();

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  /* Create VBOs for vertices attributes */
  glGenBuffers(NUM_VBs, m_Buffers);

  /* Return value */
  bool ret = false;

  Assimp::Importer importer;
  _pScene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

  if (_pScene)
  {
    /* Get transformation matrix for nodes(vertices relative to boes) */
    aiMatrix4x4 tp1 = _pScene->mRootNode->mTransformation;
    _globalInverseTransform = aiMatrix4x4ToGlm(tp1);
    _globalInverseTransform =  glm::inverse(_globalInverseTransform);

    ret = InitFromScene(_pScene, fileName);
  }
  else
  {
    DLog(eLogType::Error, "Error parsing: %s : %s\n", fileName.c_str(), _importer.GetErrorString());
  }

  /* Make sure the VAO is not changed from the outside */
  glBindVertexArray(0);

  return ret;
}


bool AnimatedModel::InitFromScene(const aiScene* pScene, const std::string& fileName)
{
  /* Resize the mesh & texture vectors */
  _entries.resize(pScene->mNumMeshes);
  _textures.resize(pScene->mNumMaterials);

  std::vector<glm::vec3> Positions;
  std::vector<glm::vec3> Normals;
  std::vector<glm::vec2> TexCoords;
  std::vector<VertexBoneData> Bones;
  std::vector<unsigned int> Indices;

  unsigned int NumVertices = 0;
  unsigned int NumIndices = 0;

  /* Count the number of vertices and indices */
  for (unsigned int i = 0; i < _entries.size(); ++i)
  {
    _entries[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
    _entries[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
    _entries[i].BaseVertex = NumVertices;
    _entries[i].BaseIndex = NumIndices;

    NumVertices += pScene->mMeshes[i]->mNumVertices;
    NumIndices += _entries[i].NumIndices;
  }

  // Reserve space in the vectors for the vertex attributes and indices
  Positions.reserve(NumVertices);
  Normals.reserve(NumVertices);
  TexCoords.reserve(NumVertices);
  Bones.resize(NumVertices);
  Indices.reserve(NumIndices);

  /* Initialize the meshes in the scene one by one */
  for (unsigned int i = 0; i < _entries.size(); ++i)
  {
    /* get mesh */
    const aiMesh* paiMesh = pScene->mMeshes[i];
    /* init the mesh */
    InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
  }
  if (!InitMaterials(pScene, fileName))
    return false;

  /* Generate and populate the buffers with vertex attributes and indices */
  glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(POSITION_LOCATION);
  glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(TEX_COORD_LOCATION);
  glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(NORMAL_LOCATION);
  glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BONE_VB]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(BONE_ID_LOCATION);
  glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
  glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
  glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  if (glGetError() == GL_NO_ERROR)
    return true;
  else
    return false;

}


void VertexBoneData::AddBoneData(unsigned int BoneID, float Weight)
{
  for (unsigned int i = 0; i < NUM_BONES_PER_VERTEX; ++i)
    if (Weights[i] == 0.0)
    {
      IDs[i] = BoneID;
      Weights[i] = Weight;
      return;
    }
}


void AnimatedModel::InitMesh(
  unsigned int MeshIndex,
  const aiMesh* paiMesh,
  std::vector<glm::vec3>& Positions,
  std::vector<glm::vec3>& Normals,
  std::vector<glm::vec2>& TexCoords,
  std::vector<VertexBoneData>& Bones,
  std::vector<unsigned int>& Indices
)
{
  const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

  DLog(eLogType::Error, "Num vertices = %d \n", paiMesh->mNumVertices);

  /* Populize the vertex attribute vectors */
  for (unsigned int i = 0; i < paiMesh->mNumVertices; ++i)
  {
    /* Get pos normal texCoord */

    const aiVector3D* pPos = &(paiMesh->mVertices[i]);

    const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

    /* store pos normal texCoord */
    Positions.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));

    if (paiMesh->HasNormals())
    {
      const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
      Normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
    }
    TexCoords.push_back(glm::vec2(pTexCoord->x, pTexCoord->y));
  }

  /* Load bones */
  LoadBones(MeshIndex, paiMesh, Bones);

  /* Populate the index buffer */
  for (unsigned int i = 0; i < paiMesh->mNumFaces; ++i)
  {
    const aiFace& Face = paiMesh->mFaces[i];
    /* if mNumIndices != 3 then worning */
    assert(Face.mNumIndices == 3);
    Indices.push_back(Face.mIndices[0]);
    Indices.push_back(Face.mIndices[1]);
    Indices.push_back(Face.mIndices[2]);
  }
}

void AnimatedModel::LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones)
{
  /* Load bones one by one */

  for (unsigned int i = 0; i < pMesh->mNumBones; ++i)
  {
    unsigned int BoneIndex = 0;
    std::string BoneName(pMesh->mBones[i]->mName.data);

    if (_boneMapping.find(BoneName) == _boneMapping.end())
    {
      /* allocate an index for the new bone */
      BoneIndex = _numBones;
      _numBones++;
      BoneInfo bi;
      _boneInfo.push_back(bi);

      aiMatrix4x4 tp1 = pMesh->mBones[i]->mOffsetMatrix;
      _boneInfo[BoneIndex].BoneOffset = aiMatrix4x4ToGlm(tp1);
      _boneMapping[BoneName] = BoneIndex;
    }
    else
    {
      BoneIndex = _boneMapping[BoneName];
    }

    for (unsigned int j = 0; j < pMesh->mBones[i]->mNumWeights; ++j)
    {
      //std::cout << pMesh->mBones[i]->mWeights. << std::endl;
      unsigned int VertexID = _entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
      float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
      Bones[VertexID].AddBoneData(BoneIndex, Weight);
    }
  }
}

bool AnimatedModel::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
  // Extract the directory part from the file name
  std::string::size_type SlashIndex = Filename.find_last_of("/");
  std::string Dir;

  if (SlashIndex == std::string::npos) {
    Dir = ".";
  }
  else if (SlashIndex == 0) {
    Dir = "/";
  }
  else {
    Dir = Filename.substr(0, SlashIndex);
  }

  bool ret = true;

  /* Initialize the materials */
  for (unsigned int i = 0; i < pScene->mNumMaterials; ++i)
  {
    textureList.resize(pScene->mNumMaterials);
    /* Get the material */
    const aiMaterial* pMaterial = pScene->mMaterials[i];

    _textures[i] = 0;

    if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
      aiString Path;

      if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
      {
        std::string p(Path.data);

        if (p.substr(0, 2) == ".\\")
        {
          p = p.substr(2, p.size() - 2);
        }

        std::string FullPath = Dir + "/" + p;


        textureList[i] = new Texture("Resource/textures/plain.png");
        textureList[i]->LoadTextureA();
        /* Here load the textures */
      }
    }
  }
  return ret;
}


void AnimatedModel::Clear()
{
  /* Deletes VBOs */
  if (m_Buffers[0] != 0)
    glDeleteBuffers(NUM_VBs, m_Buffers);
  /* Deletes VAO */
  if (m_VAO != 0)
  {
    glDeleteVertexArrays(1, &m_VAO);
    m_VAO = 0;
  }
}


void AnimatedModel::Render(const GLuint& shaderProgram)
{
  glBindVertexArray(m_VAO);

  for (unsigned int i = 0; i < _entries.size(); i++) {

    glDrawElementsBaseVertex(GL_TRIANGLES,
      _entries[i].NumIndices,
      GL_UNSIGNED_INT,
      (void*)(sizeof(unsigned int) * _entries[i].BaseIndex),
      _entries[i].BaseVertex);
  }

  glBindVertexArray(0);
}


unsigned int AnimatedModel::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
  for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) 
  {

    if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
      return i;
    }
  }

  assert(0);
  return 0;
}

unsigned int AnimatedModel::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
  assert(pNodeAnim->mNumRotationKeys > 0);

  for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
    if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
      return i;
    }
  }

  assert(0);
  return 0;
}

unsigned int AnimatedModel::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
  assert(pNodeAnim->mNumScalingKeys > 0);

  for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
    if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
      return i;
    }
  }

  assert(0);
  return 0;
}

void AnimatedModel::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
  if (pNodeAnim->mNumPositionKeys == 1) {
    Out = pNodeAnim->mPositionKeys[0].mValue;
    return;
  }

  unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
  unsigned int NextPositionIndex = (PositionIndex + 1);
  assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
  float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
  float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
  assert(Factor >= 0.0f && Factor <= 1.0f);
  const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
  const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
  aiVector3D Delta = End - Start;
  Out = Start + Factor * Delta;
}

void AnimatedModel::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
  // we need at least two values to interpolate...
  if (pNodeAnim->mNumRotationKeys == 1) {
    Out = pNodeAnim->mRotationKeys[0].mValue;
    return;
  }

  unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
  unsigned int NextRotationIndex = (RotationIndex + 1);
  assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
  float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
  float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
  assert(Factor >= 0.0f && Factor <= 1.0f);
  const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
  const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
  aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
  Out = Out.Normalize();
}

void AnimatedModel::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
  if (pNodeAnim->mNumScalingKeys == 1) {
    Out = pNodeAnim->mScalingKeys[0].mValue;
    return;
  }

  unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
  unsigned int NextScalingIndex = (ScalingIndex + 1);
  assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
  float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
  float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
  assert(Factor >= 0.0f && Factor <= 1.0f);
  const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
  const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
  aiVector3D Delta = End - Start;
  Out = Start + Factor * Delta;
}

void AnimatedModel::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform)
{
  std::string NodeName(pNode->mName.data);

  const aiAnimation* pAnimation = _pScene->mAnimations[0];

  aiMatrix4x4 tp1 = pNode->mTransformation;
  glm::mat4 NodeTransformation = aiMatrix4x4ToGlm(tp1);
  const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

  if (pNodeAnim) {
    // Interpolate scaling and generate scaling transformation matrix
    aiVector3D Scaling;
    CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
    glm::mat4 ScalingM;

    ScalingM = glm::scale(ScalingM, glm::vec3(Scaling.x, Scaling.y, Scaling.z));

    // Interpolate rotation and generate rotation transformation matrix
    aiQuaternion RotationQ;
    CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
    aiMatrix3x3 tp = RotationQ.GetMatrix();
    glm::mat4 RotationM = aiMatrix3x3ToGlm(tp);

    // Interpolate translation and generate translation transformation matrix
    aiVector3D Translation;

    CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
    glm::mat4 TranslationM;
    TranslationM = glm::translate(TranslationM, glm::vec3(Translation.x, Translation.y, Translation.z));

    // Combine the above transformations
    NodeTransformation = TranslationM * RotationM *ScalingM;
  }

  glm::mat4 GlobalTransformation = ParentTransform * NodeTransformation;

  if (_boneMapping.find(NodeName) != _boneMapping.end()) {
    unsigned int BoneIndex = _boneMapping[NodeName];
    _boneInfo[BoneIndex].FinalTransformation = _globalInverseTransform * GlobalTransformation * _boneInfo[BoneIndex].BoneOffset;
  }

  for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
    ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
  }
}

void AnimatedModel::BoneTransform(float timeInSeconds, std::vector<glm::mat4>& Transforms)
{
  glm::mat4 Identity = glm::mat4();

  ///* The original code with the buggy animation duration */
  ////animDuration = (float)m_pScene->mAnimations[0]->mDuration;

  ///* Calc animation duration from last frame */
  //unsigned int numPosKeys = _pScene->mAnimations[0]->mChannels[0]->mNumPositionKeys;
  //animDuration = _pScene->mAnimations[0]->mChannels[0]->mPositionKeys[numPosKeys - 1].mTime;

  //float TicksPerSecond = (float)(_pScene->mAnimations[0]->mTicksPerSecond != 0 ? _pScene->mAnimations[0]->mTicksPerSecond : 25.0f);

  //float TimeInTicks = timeInSeconds * TicksPerSecond;
  //float AnimationTime = fmod(TimeInTicks, animDuration);

  //ReadNodeHeirarchy(AnimationTime, _pScene->mRootNode, Identity);

  //Transforms.resize(_numBones);

  //for (unsigned int  i = 0; i < _numBones; i++) {
  //  Transforms[i] = _boneInfo[i].FinalTransformation;
  //}

  float TicksPerSecond = _pScene->mAnimations[0]->mTicksPerSecond != 0 ? 
    _pScene->mAnimations[0]->mTicksPerSecond : 25.0f;
  float TimeInTicks = timeInSeconds * TicksPerSecond;
  float AnimationTime = fmod(TimeInTicks, _pScene->mAnimations[0]->mDuration);

  ReadNodeHeirarchy(AnimationTime, _pScene->mRootNode, Identity);

  Transforms.resize(_numBones);

  for (unsigned int i = 0 ; i < _numBones ; i++) {
    Transforms[i] = _boneInfo[i].FinalTransformation;
  }
}

const aiNodeAnim* AnimatedModel::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
{
  for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
    const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

    if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
      return pNodeAnim;
    }
  }

  return NULL;
}
