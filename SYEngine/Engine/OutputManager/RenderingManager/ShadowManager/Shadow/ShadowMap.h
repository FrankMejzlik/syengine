#pragma once

#include <stdio.h>

#include <GL/glew.h>

#include "Shadow.h"

namespace SYE 
{

class ShadowMap:
  public Shadow
{
public:
  ShadowMap();
  virtual ~ShadowMap();
  virtual bool Init(unsigned int width, unsigned int height);
  virtual void Write();
  virtual void Read(GLenum textureUnit);
  GLuint GetShadowWidth() { return shadowWidth; }
  GLuint GetShadowHeight() { return shadowHeight; }

protected:
  GLuint FBO, shadowMap;
  GLuint shadowWidth, shadowHeight;
};

}
