#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

#include "Component.h"

namespace WeSp 
{

class Mesh:
  public Component
{
public:
  Mesh();
  Mesh(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, bool calculateAverageNormals = false);
  ~Mesh();

  virtual void CreateMesh(
    std::vector<GLfloat> vertices, std::vector<unsigned int> indices, 
    bool calculateAverageNormals = false
  );
  virtual void RenderMesh();
  virtual void ClearMesh();

  

protected:
  std::vector<GLfloat> _vertices;
  std::vector<unsigned int> _indices;

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