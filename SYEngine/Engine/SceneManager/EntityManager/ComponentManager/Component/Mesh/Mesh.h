#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <memory>

#include "Component.h"
#include "MaterialManager.h"
#include "TextureManager.h"

namespace WeSp 
{

class Texture;
class Material;

class Mesh:
  public Component
{
public:
  Mesh() = delete;

  Mesh(std::shared_ptr<Entity> pEntity);

  Mesh(
    std::shared_ptr<Entity> pEntity,
    std::vector<GLfloat> vertices, 
    std::vector<unsigned int> indices, 
    bool calculateAverageNormals = false
  );
  ~Mesh();

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