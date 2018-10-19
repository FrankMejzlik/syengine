#pragma once

#include <GL/glew.h>

#include "CommonValues.h"
#include "Component.h"

namespace WeSp 
{

class Texture:
  public Component
{
public:
  Texture();
  Texture(const char* const fileLocation);

  bool LoadTexture();
  bool LoadTextureA();
  void UseTexture();
  void ClearTexture();

  ~Texture();

private:
  GLuint textureID;
  int width, height, bitDepth;

  char fileLocation[1024];

};

}