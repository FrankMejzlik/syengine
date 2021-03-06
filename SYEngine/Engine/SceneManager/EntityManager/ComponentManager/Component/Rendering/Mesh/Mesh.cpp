#include "Mesh.h"

#include "MeshManager.h"
#include "MeshGenerator.h"
#include "MeshRenderer.h"
#include "Shader.h"

using namespace SYE;

Mesh::Mesh(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Component(pOwnerEntity, pOwnerComponent, false, true, slotIndex, type)
{}

Mesh::~Mesh()
{
  ClearMesh();
}

void Mesh::DefineMesh(
  std::vector<dfloat> vertices, std::vector<unsigned int> indices, 
  bool calculateAverageNormals  
)
{
  _vertices = vertices;
  _indices = indices;

  _indexCount = (GLsizei)indices.size();
  _vertexCount = (GLsizei)vertices.size();


  // If requred, compute average normals for every vertex
  if (calculateAverageNormals)
  {
    CalculateAverageNormals(vertices, indices);
  }

  // Create VAO
  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);

  glGenBuffers(1, &_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * _vertexCount, &(vertices[0]), GL_STATIC_DRAW);

  // x, y, z
  glVertexAttribPointer(
    0,                          // Pointer ID 
    3,                          // Number of data send in - x,y,z = 3
    GL_FLOAT,                     // Type of data
    GL_FALSE,                     // Want normalize?
    sizeof(vertices[0]) * 8,    // Number to skip if we had e.g x,y,z,a,b structure
    0                           // Offset, where data starts
  );
  glEnableVertexAttribArray(0);

  // u, v
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(vertices[0]) * 8,
    (void*)(sizeof(vertices[0]) * 3)
  );
  glEnableVertexAttribArray(1); 

  // nx, ny, nz
  glVertexAttribPointer(
    2,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(vertices[0]) * 8,
    (void*)(sizeof(vertices[0]) * 5)
  );
  glEnableVertexAttribArray(2);

  glGenBuffers(1, &_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * _indexCount, &(indices[0]), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  return;
}


bool Mesh::LoadShaderUniforms(Camera* pCamera, NewShader* pShader) const
{
  // Make sure owner component is set
  if (_pOwnerComponent == nullptr)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::AttemptedToFillShaderUniformsWithoutParentComponent,
      std::string("Attempted to load Shader uniforms without pointer to owner Component set while rendering Mesh with ID " + std::to_string(GetGuid())),
      ""
    );
    SetState(eState::cError);

    return false;
  }

  // Check if parent is MeshRenderer
  MeshRenderer* pMeshRenderer = dynamic_cast<MeshRenderer*>(_pOwnerComponent);
  if (pMeshRenderer == nullptr)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::RenderingMeshWithoutParentMeshRenderer,
      std::string("Rendering Mesh without parent MeshRenderer with Mesh ID " + std::to_string(GetGuid())),
      "Transformations will be identities."
    );
    SetState(eState::cWarning);
  }

  // Load shader uniforms for this MeshRenderer and Camera
  if (!pShader->LoadSelfWithUniformsFrom(pCamera, pMeshRenderer))
  {
    return false;
  }

  return true;
}

void Mesh::RenderMesh(Camera* pCamera, NewShader* pShader) const
{
  // Fill shader uniforms with correct data
  bool result = LoadShaderUniforms(pCamera, pShader);
  if (!result)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::FailedToRenderMesh,
      std::string("Failed to render Mesh with ID " + std::to_string(GetGuid())),
      std::string("")
    );
    SetState(eState::cError);
  }

  // Bind this Mesh's VAO to OpenGL
  glBindVertexArray(_VAO);

  // Bind this Mesh's only IBO it has
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

  // Draw it
  glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);

  // Unbind this Mesh's only IBO it has
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  // Unbind this Mesh's VAO to OpenGL
  glBindVertexArray(0);
}

void Mesh::dc_RenderMesh()
{

  glBindVertexArray(_VAO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
  glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

}

void Mesh::ClearMesh()
{
  if (_IBO != 0)
  {
    // Remove Mesh from GPU memory
    glDeleteBuffers(1, &_IBO);
    _IBO = 0;
  }

  if (_VBO != 0)
  {
    // Remove Mesh from GPU memory
    glDeleteBuffers(1, &_VBO);
    _VBO = 0;
  }

  if (_VAO != 0)
  {
    // Remove Mesh from GPU memory
    glDeleteVertexArrays(1, &_VAO);
    _VAO = 0;
  }

  _indexCount = 0;
  return;
}

void Mesh::MakeBlock(dfloat width, dfloat height, dfloat length)
{
  auto data = GetMeshManagerPtr()->GenerateBlockVerticesIndices(width, height, length);
  
  DefineMesh(data.first, data.second, false);
}

void Mesh::MakePrism(
  const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& p4,
  const Vector3f& p5, const Vector3f& p6, const Vector3f& p7, const Vector3f& p8
)
{
  auto data = GetMeshManagerPtr()->GeneratePrismVerticesIndices(p1, p2, p3, p4, p5, p6, p7, p8);

  DefineMesh(data.first, data.second, false);
}

void Mesh::MakeQuad(dfloat width, dfloat height)
{
  auto data = GetMeshManagerPtr()->GenerateQuadVerticesIndices(width, height);

  DefineMesh(data.first, data.second, false);
}

void Mesh::MakeSphere(dfloat radius, size_t numSlices, size_t numStacks)
{
  auto data = GetMeshManagerPtr()->GenerateSphereVerticesIndices(radius, numSlices, numStacks);

  DefineMesh(data.first, data.second, false);
}

bool Mesh::CalculateAverageNormals(std::vector<dfloat>& vertices, std::vector<unsigned int>& indices)
{
  for (size_t i = 0; i < _indexCount; i += 3)
  {
    size_t in0 = indices[i] * vLength;
    size_t in1 = indices[i + 1] * vLength;
    size_t in2 = indices[i + 2] * vLength;

    glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
    glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
    glm::vec3 normal = glm::cross(v1, v2);
    normal = glm::normalize(normal);


    // Offset us to nx values we're gonna update
    in0 += normalOffset;
    in1 += normalOffset;
    in2 += normalOffset;

    vertices[in0] += normal.x;
    vertices[in0 + 1] += normal.y;
    vertices[in0 + 2] += normal.z;

    vertices[in1] += normal.x;
    vertices[in1 + 1] += normal.y;
    vertices[in1 + 2] += normal.z;

    vertices[in2] += normal.x;
    vertices[in2 + 1] += normal.y;
    vertices[in2 + 2] += normal.z;
  }
  for (size_t i = 0; i < _vertexCount / vLength; ++i)
  {
    size_t nOffset = i * vLength + normalOffset;
    glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
    vec = glm::normalize(vec);

    vertices[nOffset] = -vec.x;
    vertices[nOffset + 1] = -vec.y;
    vertices[nOffset + 2] = -vec.z;
  }
  return true;
}
