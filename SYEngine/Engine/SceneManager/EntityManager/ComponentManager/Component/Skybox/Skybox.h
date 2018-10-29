#pragma once

#include <vector>
#include <string>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "CommonValues.h"
#include "Mesh.h"
#include "Shader.h"

#include "Component.h"

using namespace WeSp;

namespace WeSp 
{

class Skybox:
  public Component
{
public:
  Skybox() = delete;

  Skybox(std::shared_ptr<Entity> pEntity, std::vector<std::string> faceLocation);
  ~Skybox();

  void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
  Mesh* skyMesh;
  Shader* skyShader;

  GLuint textureId;
  GLuint uniformProjection, uniformView;

};

}