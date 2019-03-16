#pragma once

#include <vector>
#include <memory>

#include <GL/glew.h>
#pragma warning(push, 1)
#include <GLM/glm.hpp>
#pragma warning(pop)

#include "Component.h"
#include "MaterialManager.h"
#include "TextureManager.h"

namespace SYE 
{

class Texture;
class Shader;
class NewShader;

class Mesh:
  public Component
{
public:
  Mesh() = delete;
  Mesh(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::MESH
  );
  virtual ~Mesh() noexcept;

  /**
   * Resets and populates this Mesh instance with provided vertices and indices data
   *
   * This creates generates VAO with VBO and IBO and sends data as STATIC to GPU.
   *
   * Vertices MUST be in format:
   *    x, y, z,    u, v,     nx, ny, nz
   */
  virtual void DefineMesh(
    std::vector<dfloat> vertices, std::vector<unsigned int> indices, 
    bool calculateAverageNormals = false
  );

  virtual void RenderMesh(Camera* pCamera, NewShader* pShader) const;

  virtual void dc_RenderMesh();
  virtual void ClearMesh();

  void MakeBlock(dfloat width, dfloat height, dfloat length);
  void MakePrism(
    const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& p4,
    const Vector3f& p5, const Vector3f& p6, const Vector3f& p7, const Vector3f& p8
  );
  void MakeQuad(dfloat width, dfloat height);
  void MakeSphere(dfloat radius, size_t numSlices, size_t numStacks);
  void MakeTriangle(dfloat a, dfloat b, dfloat c);

  bool CalculateAverageNormals(std::vector<dfloat>& vertices, std::vector<unsigned int>& indices);

  const std::vector<unsigned int>& GetIndices() const { return _indices; }

  const std::vector<dfloat>& GetVertices() const { return _vertices; }

private:
  bool LoadShaderUniforms(Camera* pCamera, NewShader* pShader) const;


  // Attributes
protected:
  std::vector<dfloat> _vertices;
  std::vector<unsigned int> _indices;
  
  GLuint _VAO, _VBO, _IBO;
  GLsizei _indexCount;
  GLsizei _vertexCount;

  /** Number of values representing one vertex */
  unsigned int vLength = 8;
  /** Offset to first normal vector value */
  unsigned int normalOffset = 5;

 
};

}