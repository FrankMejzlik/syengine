#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>

#pragma warning(push, 1)
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "stb_image.h"
#pragma warning(pop)

#include "Mesh.h"
#include "Shader.h"

#include "Component.h"

using namespace SYE;

// TODO: Reimplementation needed

namespace SYE 
{

class Skybox:
  public Component
{
public:
  Skybox() = delete;

  Skybox(Entity* pOwnerEntity, Component* pOwnerComponent, std::vector<std::string> faceLocation);
  ~Skybox();

  void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
  Mesh* skyMesh;
  Shader* skyShader;

  GLuint textureId;
  GLuint uniformProjection, uniformView;

};

}