#pragma once

#include <GL/glew.h>

#include "CommonValues.h"
#include "Component.h"

namespace SYE 
{

class Texture:
  public Component
{
public:
  Texture() = delete;

  Texture(std::shared_ptr<Entity> pEntity);
  Texture(std::shared_ptr<Entity> pEntity, const char* const fileLocation);

  bool LoadTexture();
  void UseTexture();
  void ClearTexture();

  ~Texture();

private:
  GLuint textureID;
  int width, height, bitDepth;

  char fileLocation[1024];

};

}