#include "MeshGenerator.h"

using namespace SYE;

MeshGenerator::MeshGenerator(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  DLog(eLogType::cSuccess, "\t\t\t MeshGenerator instance created.");
}

MeshGenerator::~MeshGenerator() noexcept
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "\t\t\t MeshGenerator instance destroyed.");
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
  DLog(eLogType::cSuccess, "\t\t\t MeshGenerator instance initialized.");
  return true;
}

bool MeshGenerator::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "\t\t\t MeshGenerator instance terminated.");
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
    4, 5, 6,
    6, 7, 4,
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

std::pair< std::vector<dfloat>, std::vector<unsigned int> > MeshGenerator::GeneratePrismVerticesIndices(
  const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& p4,
  const Vector3f& p5, const Vector3f& p6, const Vector3f& p7, const Vector3f& p8
)
{
  // Compute normals
  Vector3f normTop = Cross((p3 - p4), (p8 - p4));
  Vector3f normBottom = Cross((p5- p1), (p2 - p1));

  Vector3f normFront = Cross((p2 - p1), (p4 - p1));
  Vector3f normBack = Cross((p7 - p8), (p5 - p8));

  Vector3f normLeft = Cross((p8 - p4), (p1 - p4));
  Vector3f normRight = Cross((p2 - p3), (p7 - p3));

  // Generate vertices vector.
  std::vector<dfloat> vertices =
  {
    /*
    Data format:
    x            y             z             u    v      nx     ny   nz
    */
    // Top 8734
    p8.GetX(), p8.GetY(), p8.GetZ(),      0.0f, 0.0f,		normTop.GetX(), normTop.GetY(), normTop.GetZ(),
    p7.GetX(), p7.GetY(), p7.GetZ(),		  1.0f, 0.0f,		normTop.GetX(), normTop.GetY(), normTop.GetZ(),
    p3.GetX(), p3.GetY(), p3.GetZ(),		  1.0f, 1.0f,		normTop.GetX(), normTop.GetY(), normTop.GetZ(),
    p4.GetX(), p4.GetY(), p4.GetZ(),		  0.0f, 1.0f,		normTop.GetX(), normTop.GetY(), normTop.GetZ(),

    // Bottom 5621
    p5.GetX(), p5.GetY(), p5.GetZ(),		  0.0f, 0.0f,		normBottom.GetX(), normBottom.GetY(), normBottom.GetZ(),
    p6.GetX(), p6.GetY(), p6.GetZ(),		  1.0f, 0.0f,		normBottom.GetX(), normBottom.GetY(), normBottom.GetZ(),
    p2.GetX(), p2.GetY(), p2.GetZ(),		  1.0f, 1.0f,		normBottom.GetX(), normBottom.GetY(), normBottom.GetZ(),
    p1.GetX(), p1.GetY(), p1.GetZ(),		  0.0f, 1.0f,		normBottom.GetX(), normBottom.GetY(), normBottom.GetZ(),

    // Front 4321
    p4.GetX(), p4.GetY(), p4.GetZ(),		  0.0f, 0.0f,		normFront.GetX(), normFront.GetY(), normFront.GetZ(),
    p3.GetX(), p3.GetY(), p3.GetZ(),		  1.0f, 0.0f,		normFront.GetX(), normFront.GetY(), normFront.GetZ(),
    p2.GetX(), p2.GetY(), p2.GetZ(),		  1.0f, 1.0f,		normFront.GetX(), normFront.GetY(), normFront.GetZ(),
    p1.GetX(), p1.GetY(), p1.GetZ(),		  0.0f, 1.0f,		normFront.GetX(), normFront.GetY(), normFront.GetZ(),

    // Back 8567
    p8.GetX(), p8.GetY(), p8.GetZ(),		  0.0f, 0.0f,		normBack.GetX(), normBack.GetY(), normBack.GetZ(),
    p5.GetX(), p5.GetY(), p5.GetZ(),		  1.0f, 0.0f,		normBack.GetX(), normBack.GetY(), normBack.GetZ(),
    p6.GetX(), p6.GetY(), p6.GetZ(),		  1.0f, 1.0f,		normBack.GetX(), normBack.GetY(), normBack.GetZ(),
    p7.GetX(), p7.GetY(), p7.GetZ(),		  0.0f, 1.0f,		normBack.GetX(), normBack.GetY(), normBack.GetZ(),

    // Left 8415
    p8.GetX(), p8.GetY(), p8.GetZ(),		  0.0f, 0.0f,		normLeft.GetX(), normLeft.GetY(), normLeft.GetZ(),
    p4.GetX(), p4.GetY(), p4.GetZ(),		  1.0f, 0.0f,		normLeft.GetX(), normLeft.GetY(), normLeft.GetZ(),
    p1.GetX(), p1.GetY(), p1.GetZ(),		  1.0f, 1.0f,		normLeft.GetX(), normLeft.GetY(), normLeft.GetZ(),
    p5.GetX(), p5.GetY(), p5.GetZ(),		  0.0f, 1.0f,		normLeft.GetX(), normLeft.GetY(), normLeft.GetZ(),

    // Right 7623
    p7.GetX(), p7.GetY(), p7.GetZ(),		  0.0f, 0.0f,		normRight.GetX(), normRight.GetY(), normRight.GetZ(),
    p6.GetX(), p6.GetY(), p6.GetZ(),		  1.0f, 0.0f,		normRight.GetX(), normRight.GetY(), normRight.GetZ(),
    p2.GetX(), p2.GetY(), p2.GetZ(),		  1.0f, 1.0f,		normRight.GetX(), normRight.GetY(), normRight.GetZ(),
    p3.GetX(), p3.GetY(), p3.GetZ(),		  0.0f, 1.0f,		normRight.GetX(), normRight.GetY(), normRight.GetZ(),

  };

  // Create indices vector.
  std::vector<unsigned int>  indices =
  {
    // Top
    0, 1, 2,
    2, 3, 0,
    // Bottom
    6, 5, 4, 
    4, 7, 6,
    // Front
    8, 9, 10,
    10, 11, 8,
    // Back
    12, 13, 14,
    14, 15, 12,
    // Left
    16, 17, 18,
    18, 19, 16,
    // Right
    20, 21, 22,
    22, 23, 20
  };


  return std::make_pair(vertices, indices);
}


std::pair< std::vector<dfloat>, std::vector<unsigned int> > MeshGenerator::GenerateQuadVerticesIndices(dfloat width, dfloat height)
{
  dfloat halfWidth = width / 2;
  dfloat halfHeight = height / 2;

  // Generate vertices vector.
  std::vector<dfloat> vertexArray = 
  {
    // x            y         z           u    v       nx     ny   nz
    -halfWidth, -halfHeight, 0.0f, 		  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    -halfWidth, halfHeight, 0.0f,	      1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, halfHeight, 0.0f,		      0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
    halfWidth, -halfHeight, 0.0f,		    0.0f, 0.0f,		0.0f, 0.0f, 1.0f
  };

  // Create indices vector.
  std::vector<unsigned int>  indexArray = 
  {
    0, 1, 2,
    2, 3, 0
  };

  return std::make_pair(vertexArray, indexArray);
}

std::pair< std::vector<dfloat>, std::vector<unsigned int> > MeshGenerator::GenerateSphereVerticesIndices(dfloat radius, size_t numSlices, size_t numStacks)
{
  // Generate vertices vector
  std::vector<dfloat> vertices;

  // Create indices vector
  std::vector<unsigned int>  indices;

  /**
    * Data format:
    * x   y   z |  u    v   |  nx   ny   nz
    */


  dfloat x, y, z, xy;                              // vertex position
  dfloat nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
  dfloat u, v;                                     // vertex texCoord

  dfloat sectorStep = static_cast<dfloat>(2 * M_PI / numSlices);
  dfloat stackStep = static_cast<dfloat>(M_PI / numStacks);
  dfloat sectorAngle, stackAngle;

  // Generate vertices for sphere
  for (int i = 0; i <= numStacks; ++i)
  {
    stackAngle = static_cast<dfloat>(M_PI / 2 - i * stackStep);        // starting from pi/2 to -pi/2
    xy = radius * cosf(stackAngle);             // r * cos(u)
    z = radius * sinf(stackAngle);              // r * sin(u)

    // add (sectorCount+1) vertices per stack
    // the first and last vertices have same position and normal, but different tex coords
    for (int j = 0; j <= numSlices; ++j)
    {
      sectorAngle = j * sectorStep;           // starting from 0 to 2pi

      // vertex position (x, y, z)
      x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
      y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
      vertices.push_back(x);
      vertices.push_back(y);
      vertices.push_back(z);

      // vertex tex coord (s, t) range between [0, 1]
      u = (dfloat)j / numSlices;
      v = (dfloat)i / numStacks;
      vertices.push_back(u);
      vertices.push_back(v);

      // normalized vertex normal (nx, ny, nz)
      nx = x * lengthInv;
      ny = y * lengthInv;
      nz = z * lengthInv;
      vertices.push_back(-nx);
      vertices.push_back(-ny);
      vertices.push_back(-nz);
    }
  }

  // Generate indices for sphere
  unsigned int k1, k2;
  for (int i = 0; i < numStacks; ++i)
  {
    k1 = static_cast<unsigned int>(i * (numSlices + 1));     // beginning of current stack
    k2 = static_cast<unsigned int>(k1 + numSlices + 1);      // beginning of next stack

    for (int j = 0; j < numSlices; ++j, ++k1, ++k2)
    {
      // 2 triangles per sector excluding first and last stacks
      // k1 => k2 => k1+1
      if (i != 0)
      {
        indices.push_back(k1);
        indices.push_back(k2);
        indices.push_back(k1 + 1);
      }

      // k1+1 => k2 => k2+1
      if (i != (numStacks - 1))
      {
        indices.push_back(k1 + 1);
        indices.push_back(k2);
        indices.push_back(k2 + 1);
      }
    }
  }


  return std::make_pair(vertices, indices);
}

