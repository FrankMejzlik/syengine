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
  Mesh(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept;
  ~Mesh() noexcept;


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

  const std::vector<unsigned int>& GetIndices_() const { return _indices; }

  const std::vector<dfloat>& GetVertices_() const { return _vertices; }

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

  



#if !NEW_SSSEC_IMPLEMENTED

public:

  bool _CalculateAverageNormals(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices);

  const std::vector<unsigned int>& GetIndices()
  {
    return _indices_;
  }

  const std::vector<GLfloat>& GetVertices()
  {
    return _vertices_;
  }

  std::vector<GLfloat> _vertices_;
  std::vector<unsigned int> _indices_;

  virtual void CreateMesh(
    std::vector<GLfloat> vertices, std::vector<unsigned int> indices, 
    bool calculateAverageNormals = false
  );

  Mesh(
    Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    std::vector<GLfloat> vertices, 
    std::vector<unsigned int> indices, 
    bool calculateAverageNormals = false
  );
#endif
};

}