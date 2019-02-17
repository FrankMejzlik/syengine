

#include "Texture.h"

#include "stb_image.h"
#include <GLFW/glfw3.h>


#if !NEW_SSSEC_IMPLEMENTED
  #include <cstring>
#endif

using namespace SYE;

Texture::Texture(
  Entity* pEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef
) noexcept:
  Component(pEntity,subModulesConstRef, false) 
{
  _type = eType::TEXTURE;
}


bool Texture::LoadTexture(std::string_view texturePathFile)
{
  // Load texture data
  unsigned char* textureData = stbi_load(texturePathFile.data(), &width, &height, &bitDepth, 0);

  // If loading failed
  if (!textureData)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::UnableToLoadTextureFromFile,
      "Failed to load texture from " + static_cast<std::string>(texturePathFile), 
      ""
    );

    return false;
  }

  // Let OpenGL create new texture ID
  glGenTextures(1, &textureID);

  // Bind to this texture
  glBindTexture(GL_TEXTURE_2D, textureID);

  // Fill texture data into the GPU memory
  glTexImage2D(
    GL_TEXTURE_2D,
    0,          // Mipmaps 
    GL_RGBA,    // Data fomrat in GPU memory
    width,
    height,
    0,          // Legacy border
    GL_RGBA,    // Type on input
    GL_UNSIGNED_BYTE,
    textureData
  );

  // Generate mipmaps automaticaly
  glGenerateMipmap(GL_TEXTURE_2D);

  // Setup texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  // Unbind from this texture
  glBindTexture(GL_TEXTURE_2D, 0);

  // Dealocate loader memory
  stbi_image_free(textureData);
  return true;
}

void Texture::UseTexture()
{
  // TODO: Use all units
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


#if !NEW_SSSEC_IMPLEMENTED

Texture::Texture(
  Entity* pEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef,
  const char* const fileLocation
):
  Component(pEntity, subModulesConstRef, false),
  textureID(0), width(0), height(0), bitDepth(0)
{
  strcpy_s(this->fileLocation, 1024, fileLocation);
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

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  glBindTexture(GL_TEXTURE_2D, 0);

  // Dealocate CPU mem 
  stbi_image_free(texData);
  return true;
}


#endif