#include "Mesh.h"

using namespace WeSp;

Mesh::Mesh() :
  Component(),
  _vertices(), _indices(),
  _VAO(0), _VBO(0), _IBO(0), 
  _indexCount(0), _vertexCount(0),
  _pTexture(nullptr), _pMaterial(nullptr)
{}

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, bool calculateAverageNormals):
  Component(),
  _vertices(vertices), _indices(indices),
  _vertexCount(vertices.size()), _indexCount(indices.size()),
  _pTexture(nullptr), _pMaterial(nullptr)
{
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

  // Define how one vertex data look like for 
  glVertexAttribPointer(
    0,                          // Pointer ID 
    3,                          // Number of data send in - x,y,z = 3
    GL_FLOAT,                     // Type of data
    GL_FALSE,                     // Want normalize?
    sizeof(vertices[0]) * 8,    // Number to skip if we had e.g x,y,z,a,b structure
    0                           // Offset, where data starts
  );
  glEnableVertexAttribArray(0);

  // Define attrib pointer for two additional data on each vertex
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(vertices[0]) * 8,
    (void*)(sizeof(vertices[0]) * 3)
  );
  glEnableVertexAttribArray(1); 

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

  // Mesh is ready to be used
  SetComponentState(eComponentState::Ready);

  return;
}

Mesh::~Mesh()
{
  SetComponentState(eComponentState::Null);
  ClearMesh();

}

void Mesh::CreateMesh(
  std::vector<GLfloat> vertices, std::vector<unsigned int> indices, 
  bool calculateAverageNormals  
)
{
  _indexCount = indices.size();
  _vertexCount = vertices.size();

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

  // Define how one vertex data look like for 
  glVertexAttribPointer(
    0,                          // Pointer ID 
    3,                          // Number of data send in - x,y,z = 3
    GL_FLOAT,                     // Type of data
    GL_FALSE,                     // Want normalize?
    sizeof(vertices[0]) * 8,    // Number to skip if we had e.g x,y,z,a,b structure
    0                           // Offset, where data starts
  );
  glEnableVertexAttribArray(0);

  // Define attrib pointer for two additional data on each vertex
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(vertices[0]) * 8,
    (void*)(sizeof(vertices[0]) * 3)
  );
  glEnableVertexAttribArray(1); 

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

  // Mesh is ready to be used
  SetComponentState(eComponentState::Ready);

  return;
}

void Mesh::CreateMesh(
  std::vector<GLfloat> vertices, std::vector<unsigned int> indices, 
  std::shared_ptr<Texture> pTexture, std::shared_ptr<Material> pMaterial,
  bool calculateAverageNormals
)
{
  // Setup correct texture and material.
  _pTexture = pTexture;
  _pMaterial = pMaterial;

  _indexCount = indices.size();
  _vertexCount = vertices.size();

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

  // Define how one vertex data look like for 
  glVertexAttribPointer(
    0,                          // Pointer ID 
    3,                          // Number of data send in - x,y,z = 3
    GL_FLOAT,                     // Type of data
    GL_FALSE,                     // Want normalize?
    sizeof(vertices[0]) * 8,    // Number to skip if we had e.g x,y,z,a,b structure
    0                           // Offset, where data starts
  );
  glEnableVertexAttribArray(0);

  // Define attrib pointer for two additional data on each vertex
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(vertices[0]) * 8,
    (void*)(sizeof(vertices[0]) * 3)
  );
  glEnableVertexAttribArray(1); 

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

  // Mesh is ready to be used
  SetComponentState(eComponentState::Ready);

  return;
}

void Mesh::RenderMesh()
{

  glBindVertexArray(_VAO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
  glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  return;
}
 
void Mesh::RenderMesh(GLuint ul_specularIntensity, GLuint ul_shininess)
{

  _pTexture->UseTexture();
  _pMaterial->UseMaterial(ul_specularIntensity, ul_shininess);

  glBindVertexArray(_VAO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
  glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  return;
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

bool Mesh::CalculateAverageNormals(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices)
{
  for (size_t i = 0; i < _indexCount; i += 3)
  {
    unsigned int in0 = indices[i] * vLength;
    unsigned int in1 = indices[i + 1] * vLength;
    unsigned int in2 = indices[i + 2] * vLength;

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

    vertices[nOffset] = vec.x;
    vertices[nOffset + 1] = vec.y;
    vertices[nOffset + 2] = vec.z;
  }
  return true;
}
