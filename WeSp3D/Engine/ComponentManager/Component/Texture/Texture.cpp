
// Treat header file like implementation file
#define STB_IMAGE_IMPLEMENTATION

#include <cstring>
#include <string>

#pragma warning (push, 3)
#include "Texture.h"
#pragma warning(pop)

using namespace WeSp;

Texture::Texture() :
  textureID(0), width(0), height(0), bitDepth(0), fileLocation()
{}

Texture::Texture(const char* const fileLocation):
  textureID(0), width(0), height(0), bitDepth(0)
{
  strcpy_s(this->fileLocation, 1024, fileLocation);
}

bool Texture::LoadTextureA()
{
  unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
  if (!texData)
  {
    printf("Failed to find %s\n", fileLocation);
    return false;
  }

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(
    GL_TEXTURE_2D,
    0, // Mipmaps 
    GL_RGBA, // Data fomrat in GPU memory
    width,
    height,
    0,  // Legacy border
    GL_RGBA, // Type on input
    GL_UNSIGNED_BYTE,
    texData
  );

  // Generate mipmaps automaticaly
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);

  // Dealocate CPU mem 
  stbi_image_free(texData);
  return true;
}
bool Texture::LoadTexture()
{
  unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
  if (!texData)
  {
    printf("Failed to find %s\n", fileLocation);
    return false;
  }

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(
    GL_TEXTURE_2D,
    0, // Mipmaps 
    GL_RGB, // Data fomrat in GPU memory
    width,
    height,
    0,  // Legacy border
    GL_RGB, // Type on input
    GL_UNSIGNED_BYTE,
    texData
  );

  // Generate mipmaps automaticaly
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);

  // Dealocate CPU mem 
  stbi_image_free(texData);
  return true;
}
void Texture::UseTexture()
{
  glActiveTexture(GL_TEXTURE1); // Minimum of 16 texture unit available
  glBindTexture(GL_TEXTURE_2D, textureID);
}
void Texture::ClearTexture()
{
  // Delete texture from GPU
  glDeleteTextures(1, &textureID);
  textureID = 0;
  width = 0;
  height = 0;
  bitDepth = 0;
}

Texture::~Texture()
{}
