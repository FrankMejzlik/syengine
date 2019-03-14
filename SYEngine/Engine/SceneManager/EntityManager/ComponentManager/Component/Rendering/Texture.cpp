

#include "Texture.h"

#include "stb_image.h"
#include <GLFW/glfw3.h>

using namespace SYE;

Texture::Texture(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Component(pOwnerEntity, pOwnerComponent, false, true, slotIndex, type)
{}


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

  // If no Alpha chanel
  if (bitDepth == 3)
  {
    // Fill texture data into the GPU memory
    glTexImage2D(
      GL_TEXTURE_2D,
      0,          // Mipmaps 
      GL_RGB,    // Data fomrat in GPU memory
      width,
      height,
      0,          // Legacy border
      GL_RGB,    // Type on input
      GL_UNSIGNED_BYTE,
      textureData
    );
  }
  // Else alpha chanell present
  else
  {
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
  }

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


bool Texture::LoadTexture(Vector3f colour)
{
  // Fill in texture data
  // R G B A
  unsigned char textureData[] = { 
    static_cast<unsigned char>(colour.GetX()),
    static_cast<unsigned char>(colour.GetY()),
    static_cast<unsigned char>(colour.GetZ()),
    static_cast<unsigned char>(1.0f * 255)
  };

  // Let OpenGL create new texture ID
  glGenTextures(1, &textureID);

  // Bind to this texture
  glBindTexture(GL_TEXTURE_2D, textureID);

  // Fill texture data into the GPU memory
  glTexImage2D(
    GL_TEXTURE_2D,
    0,          // Mipmaps 
    GL_RGBA,    // Data fomrat in GPU memory
    1,
    1,
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
