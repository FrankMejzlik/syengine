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
class Material;

class Mesh:
  public Component
{
public:
  Mesh() = delete;

  Mesh(Entity* pEntity);

  Mesh(
    Entity* pEntity,
    std::vector<GLfloat> vertices, 
    std::vector<unsigned int> indices, 
    bool calculateAverageNormals = false
  );
  ~Mesh();

  const std::vector<unsigned int>& GetIndices()
  {
    return _indices;
  }

  const std::vector<GLfloat>& GetVertices()
  {
    return _vertices;
  }

  virtual void CreateMesh(
    std::vector<GLfloat> vertices, std::vector<unsigned int> indices, 
    bool calculateAverageNormals = false
  );
  virtual void CreateMesh(
    std::vector<GLfloat> vertices, std::vector<unsigned int> indices, 
    std::shared_ptr<Texture> pTexture, std::shared_ptr<Material> pMaterial, 
    bool calculateAverageNormals = false
  );
  virtual void RenderMesh();
  virtual void ClearMesh();

protected:
  std::vector<GLfloat> _vertices;
  std::vector<unsigned int> _indices;
  std::shared_ptr<Texture> _pTexture;
  std::shared_ptr<Material> _pMaterial;
  
  GLuint _VAO, _VBO, _IBO;
  GLsizei _indexCount;
  GLsizei _vertexCount;

  // Number of values representing one vertex
  unsigned int vLength = 8;
  // Offset to first normal value
  unsigned int normalOffset = 5;

  bool CalculateAverageNormals(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices);

};

}