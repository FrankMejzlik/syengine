#include "OmniShadowMap.h"

using namespace SYE;


OmniShadowMap::OmniShadowMap() :
  ShadowMap()
{}


OmniShadowMap::~OmniShadowMap()
{
  if (FBO)
  {
    //glDeleteFramebuffers(1, &FBO);
  }

  if (shadowMap)
  {
    glDeleteTextures(1, &shadowMap);
  }
}

bool OmniShadowMap::Init(unsigned int width, unsigned int height)
{
  shadowWidth = width;
  shadowHeight = height;

  glGenFramebuffers(1, &FBO);
  glGenTextures(1, &shadowMap);

  // Attach cube map to shadow map ID
  glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);

  // Loop through all 6 textures
  for (size_t i = 0; i < 6; ++i)
  {
    glTexImage2D(
      GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
      GL_DEPTH_COMPONENT, shadowWidth, shadowHeight,
      0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr
    );
  }

  glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // Also add Z axis of texture handling
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);

  // We do not want to read and write any data
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);

  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE)
  {
    printf("Framebuffer error: %d\n", (int)status);
    return false;
  }
  return true;
  
}

void OmniShadowMap::Write()
{
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
}

void OmniShadowMap::Read(GLenum textureUnit)
{
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);
}
