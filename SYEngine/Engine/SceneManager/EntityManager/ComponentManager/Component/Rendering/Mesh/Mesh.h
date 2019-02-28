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
class _Material;

class Mesh:
  public Component
{
public:
  Mesh() = delete;
  Mesh(
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::MESH
  );
  virtual ~Mesh() noexcept;


  virtual void CreateMesh_(
    std::vector<dfloat> vertices, std::vector<unsigned int> indices, 
    bool calculateAverageNormals = false
  );

  virtual void RenderMesh();
  virtual void ClearMesh();

  void MakeBlock(dfloat width, dfloat height, dfloat length);
  void MakeQuad(dfloat width, dfloat height);
  void MakeSphere(dfloat radius, size_t numSlices, size_t numStacks);
  void MakeTriangle(dfloat a, dfloat b, dfloat c);

  bool CalculateAverageNormals(std::vector<dfloat>& vertices, std::vector<unsigned int>& indices);

  const std::vector<unsigned int>& GetIndices() const { return _indices; }

  const std::vector<dfloat>& GetVertices() const { return _vertices; }

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