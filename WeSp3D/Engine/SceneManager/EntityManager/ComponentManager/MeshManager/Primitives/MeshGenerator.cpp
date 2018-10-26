#include "MeshGenerator.h"

using namespace WeSp;

MeshGenerator::MeshGenerator(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_MESH_GENERATOR, std::make_shared<MeshGenerator>(*this)));

  DLog(eLogType::Success, "\t\t\t MeshGenerator instance created.");
}

MeshGenerator::~MeshGenerator()
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
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
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

std::shared_ptr<Mesh> MeshGenerator::GenerateMeshBlock(
  dfloat width, dfloat height, dfloat length,
  bool bAverageNormals
)
{
  // Generate vertices vector.
  std::vector<float> blockVertices = 
  {
    // x      y         z           u    v       nx     ny   nz
    -width, height, -length,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    -width, -height, -length,	    0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    width, height, -length,		      0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    width, -height, -length,		    0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

    -width, height, length,		    0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    width, height, length,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    -width, -height, length,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    width, -height, length,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f
  };

  // Create indices vector.
  std::vector<unsigned int>  blockIndices = 
  {
    // front
    0, 1, 2,
    2, 1, 3,
    // right
    2, 3, 5,
    5, 3, 7,
    // back
    5, 7, 4,
    4, 7, 6,
    // left
    4, 6, 0,
    0, 6, 1,
    // top
    4, 0, 5,
    5, 0, 2,
    // bottom
    1, 6, 3,
    3, 6, 7
  };

  // Mesh
  std::shared_ptr<Mesh> pBlockMesh = std::make_shared<Mesh>();    
  pBlockMesh->CreateMesh(blockVertices, blockIndices, bAverageNormals);

  return pBlockMesh;
}


std::shared_ptr<Mesh>  MeshGenerator::GenerateMeshQuad(
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
    -halfWidth, halfHeight, 0.0f,	      0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, halfHeight, 0.0f,		      0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, -halfHeight, 0.0f,		    0.0f, 0.0f,		0.0f, 0.0f, 1.0f
  };

  // Create indices vector.
  std::vector<unsigned int>  indexArray = 
  {
    0, 1, 2,
    2, 3, 0
  };

  // Instantiate Mesh instance.
  std::shared_ptr<Mesh> pBlockMesh = std::make_shared<Mesh>();    
  pBlockMesh->CreateMesh(vertexArray, indexArray, bAverageNormals);

  return pBlockMesh;
}