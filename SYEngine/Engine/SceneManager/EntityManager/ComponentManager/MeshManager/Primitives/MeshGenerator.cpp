#include "MeshGenerator.h"

using namespace SYE;

MeshGenerator::MeshGenerator(BaseModule& parentModule) noexcept:
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_MESH_GENERATOR, std::make_unique<MeshGenerator>(*this)));

  DLog(eLogType::Success, "\t\t\t MeshGenerator instance created.");
}

MeshGenerator::~MeshGenerator() noexcept
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t\t\t MeshGenerator instance destroyed.");
}

bool MeshGenerator::Initialize()
{
  // Initialize submodules.
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization

  SetModuleState(eModuleState::OK);
  DLog(eLogType::Success, "\t\t\t MeshGenerator instance initialized.");
  return true;
}

bool MeshGenerator::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t\t\t MeshGenerator instance terminated.");
  return true;
}

std::pair< std::vector<dfloat>, std::vector<unsigned int> > MeshGenerator::GenerateBlockVerticesIndices(
  dfloat width, dfloat height, dfloat length
)
{
  dfloat halfWidth = width / 2;
  dfloat halfHeight = height / 2;
  dfloat halfLength = length / 2;

  // Generate vertices vector.
  std::vector<dfloat> blockVertices = 
  {
    /*
    Data format:
    x            y             z             u    v      nx     ny   nz
    */
    // Top.
    -halfWidth, halfHeight, -halfLength,		  0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
    halfWidth, halfHeight, -halfLength,		  1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
    halfWidth, halfHeight, halfLength,		  1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
    -halfWidth, halfHeight, halfLength,		  0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

    // Bottom.
    -halfWidth, -halfHeight, halfLength,		  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
    -halfWidth, -halfHeight, -halfLength,		  1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
    halfWidth, -halfHeight, -halfLength,		  1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    halfWidth, -halfHeight, halfLength,		  0.0f, 1.0f,		0.0f, 1.0f, 0.0f,

    // Front.
    -halfWidth, halfHeight, halfLength,		  0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
    halfWidth, halfHeight, halfLength,		  1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
    halfWidth, -halfHeight, halfLength,		  1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
    -halfWidth, -halfHeight, halfLength,		  0.0f, 1.0f,		0.0f, 0.0f, -1.0f,

    // Back.
    -halfWidth, halfHeight, -halfLength,		  0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    -halfWidth, -halfHeight, -halfLength,		  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, -halfHeight, -halfLength,		  1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, halfHeight, -halfLength,		  0.0f, 1.0f,		0.0f, 0.0f, 1.0f,

    // Left. 
    halfWidth, halfHeight, -halfLength,		  0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
    halfWidth, halfHeight, halfLength,		  1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
    halfWidth, -halfHeight, halfLength,		  1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
    halfWidth, -halfHeight, -halfLength,		  0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,

    // Right.
    -halfWidth, halfHeight, -halfLength,		  0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
    -halfWidth, -halfHeight, -halfLength,		  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
    -halfWidth, -halfHeight, halfLength,		  1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -halfWidth, halfHeight, halfLength,		  0.0f, 1.0f,		1.0f, 0.0f, 0.0f,

  };

  // Create indices vector.
  std::vector<unsigned int>  blockIndices = 
  {
    // Top.
    2, 1, 0,
    0, 3, 2,
    // Bottom.
    6, 5, 4, 
    4, 7, 6, 
    // Front.
    10, 9, 8,
    8, 11, 10,
    // Back.
    14, 13, 12, 
    12, 15, 14,
    // Left.
    16, 17, 18,
    18, 19, 16,
    // Right.
    20, 21, 22, 
    22, 23, 20
  };


  return std::make_pair(blockVertices, blockIndices);
}


std::pair< std::vector<dfloat>, std::vector<unsigned int> > MeshGenerator::GenerateQuadVerticesIndices(dfloat width, dfloat height)
{
  dfloat halfWidth = width / 2;
  dfloat halfHeight = height / 2;

  // Generate vertices vector.
  std::vector<dfloat> vertexArray = 
  {
    // x            y         z           u    v       nx     ny   nz
    -halfWidth, -halfHeight, 0.0f, 		  0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    -halfWidth, halfHeight, 0.0f,	      0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, halfHeight, 0.0f,		      1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, -halfHeight, 0.0f,		    1.0f, 0.0f,		0.0f, 0.0f, 1.0f
  };

  // Create indices vector.
  std::vector<unsigned int>  indexArray = 
  {
    0, 1, 2,
    2, 3, 0
  };

  return std::make_pair(vertexArray, indexArray);
}

#if !NEW_SSSEC_IMPLEMENTED

std::unique_ptr<Mesh> MeshGenerator::GenerateMeshBlock(
  dfloat width, dfloat height, dfloat length,
  bool bAverageNormals
)
{

  dfloat halfWidth = width / 2;
  dfloat halfHeight = height / 2;
  dfloat halfLength = length / 2;

  // Generate vertices vector.
  std::vector<float> blockVertices = 
  {
    /*
      Data format:
      x            y             z             u    v      nx     ny   nz
    */
    // Top.
    -halfWidth, halfHeight, -halfLength,		  0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
    halfWidth, halfHeight, -halfLength,		  1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
    halfWidth, halfHeight, halfLength,		  1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
    -halfWidth, halfHeight, halfLength,		  0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

    // Bottom.
    -halfWidth, -halfHeight, halfLength,		  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
    -halfWidth, -halfHeight, -halfLength,		  1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
    halfWidth, -halfHeight, -halfLength,		  1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    halfWidth, -halfHeight, halfLength,		  0.0f, 1.0f,		0.0f, 1.0f, 0.0f,

    // Front.
    -halfWidth, halfHeight, halfLength,		  0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
    halfWidth, halfHeight, halfLength,		  1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
    halfWidth, -halfHeight, halfLength,		  1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
    -halfWidth, -halfHeight, halfLength,		  0.0f, 1.0f,		0.0f, 0.0f, -1.0f,

    // Back.
    -halfWidth, halfHeight, -halfLength,		  0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    -halfWidth, -halfHeight, -halfLength,		  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, -halfHeight, -halfLength,		  1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, halfHeight, -halfLength,		  0.0f, 1.0f,		0.0f, 0.0f, 1.0f,

    // Left. 
    halfWidth, halfHeight, -halfLength,		  0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
    halfWidth, halfHeight, halfLength,		  1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
    halfWidth, -halfHeight, halfLength,		  1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
    halfWidth, -halfHeight, -halfLength,		  0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,

    // Right.
    -halfWidth, halfHeight, -halfLength,		  0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
    -halfWidth, -halfHeight, -halfLength,		  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
    -halfWidth, -halfHeight, halfLength,		  1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -halfWidth, halfHeight, halfLength,		  0.0f, 1.0f,		1.0f, 0.0f, 0.0f,

  };

  // Create indices vector.
  std::vector<unsigned int>  blockIndices = 
  {
    // Top.
    2, 1, 0,
    0, 3, 2,
    // Bottom.
    6, 5, 4, 
    4, 7, 6, 
    // Front.
    10, 9, 8,
    8, 11, 10,
    // Back.
    14, 13, 12, 
    12, 15, 14,
    // Left.
    16, 17, 18,
    18, 19, 16,
    // Right.
    20, 21, 22, 
    22, 23, 20
  };

  // Mesh
  std::unique_ptr<Mesh> pBlockMesh = std::make_unique<Mesh>(nullptr, _subModules, _fake);
  pBlockMesh->CreateMesh(blockVertices, blockIndices, bAverageNormals);

  return pBlockMesh;
}


std::unique_ptr<Mesh>  MeshGenerator::GenerateMeshQuad(
  dfloat width, dfloat height,
  bool bAverageNormals
)
{
  dfloat halfWidth = width / 2;
  dfloat halfHeight = height / 2;

  // Generate vertices vector.
  std::vector<float> vertexArray = 
  {
    // x            y         z           u    v       nx     ny   nz
    -halfWidth, -halfHeight, 0.0f, 		  0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    -halfWidth, halfHeight, 0.0f,	      0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, halfHeight, 0.0f,		      1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, -halfHeight, 0.0f,		    1.0f, 0.0f,		0.0f, 0.0f, 1.0f
  };

  // Create indices vector.
  std::vector<unsigned int>  indexArray = 
  {
    0, 1, 2,
    2, 3, 0
  };

  // Instantiate Mesh instance.
  std::unique_ptr<Mesh> pBlockMesh = std::make_unique<Mesh>(nullptr, _subModules, _fake);
  pBlockMesh->CreateMesh(vertexArray, indexArray, bAverageNormals);

  return pBlockMesh;
}

#endif