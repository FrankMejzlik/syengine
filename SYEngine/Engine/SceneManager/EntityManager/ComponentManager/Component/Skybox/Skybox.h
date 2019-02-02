#pragma once

#include <vector>
#include <string>

#include <GL\glew.h>

#pragma warning(push, 1)
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "stb_image.h"
#pragma warning(pop)

#include "CommonValues.h"
#include "Mesh.h"
#include "Shader.h"

#include "Component.h"

using namespace SYE;

namespace SYE 
{

class Skybox:
  public Component
{
public:
  Skybox() = delete;

  Skybox(Entity* pEntity, std::vector<std::string> faceLocation);
  ~Skybox();

  void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
  Mesh* skyMesh;
  Shader* skyShader;

  GLuint textureId;
  GLuint uniformProjection, uniformView;

};

}