

#include "Texture.h"

#include "stb_image.h"
#include <GLFW/glfw3.h>

#include "Entity.h"
#include "Scene.h"

#include "Camera.h"
using namespace SYE;

Texture::Texture(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Component(pOwnerEntity, pOwnerComponent, false, true, slotIndex, type),
  _textureTarget(GL_TEXTURE_2D),
  _framebuffer(0),
  _renderBuffer(0)
{
}

Texture::~Texture() noexcept
{
  // Delete all textures on GPU
  ClearTexture();
}

bool Texture::LoadTexture(std::string_view texturePathFile)
{
  int resultWidth;
  int resultHeight;
  int resultNumColorChannels;

  // Load texture data
  unsigned char* textureData = stbi_load(texturePathFile.data(), &resultWidth, &resultHeight, &resultNumColorChannels, 0);

  _width = static_cast<size_t>(resultWidth);
  _height = static_cast<size_t>(resultHeight);
  _numColorChanels = static_cast<size_t>(resultNumColorChannels);

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

  // Push empty value to vector
  _textureIds.push_back(0ULL);

  // Let OpenGL create new texture ID
  glGenTextures(1, &_textureIds.back());

  // Bind to this texture so we can write data to it
  glBindTexture(GL_TEXTURE_2D, _textureIds.back());

  // If no Alpha chanel
  if (_numColorChanels == 3)
  {
    // Fill texture data into the GPU memory
    glTexImage2D(
      GL_TEXTURE_2D,
      0,          // Mipmaps 
      GL_RGB,    // Data fomrat in GPU memory
      static_cast<GLsizei>(_width),
        static_cast<GLsizei>(_height),
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
      static_cast<GLsizei>(_width),
      static_cast<GLsizei>(_height),
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

bool Texture::LoadTextures(const std::vector< std::vector<std::byte> >& data, const std::vector<GLenum>& attachments)
{
  // Create Texture for rendering into
  UNREFERENCED_PARAMETER(data);
  UNREFERENCED_PARAMETER(attachments);


  InitRenderTargets(attachments);

  return true;
}


void Texture::InitRenderTargets(const std::vector<GLenum>& attachments)
{
  // If no attachments wanted
  if (attachments.empty())
  {
    return;
  }

  // Initialize vector with enough space
  std::vector<GLenum> drawBuffers(_textureIds.size(), GL_NONE);
  bool hasDepthAttachment = false;

  for (size_t i = 0; i < _textureIds.size(); ++i)
  {
    // TODO: Befare of stencil bufferin future
    // If has depth attachment
    if (attachments[i] == GL_DEPTH_ATTACHMENT)
    {
      drawBuffers[i] = GL_NONE;
      hasDepthAttachment = true;
    }
    else
    {
      drawBuffers[i] = attachments[i];
    }

    // Set draw buffers to corresponding attachments
    drawBuffers[i] = attachments[i];

    // If no attachments
    if (attachments[i] == GL_NONE)
    {
      // Just continue
      continue;
    }

    // If frame buffert not set yet
    if (_framebuffer == 0)
    {
      // Generate framebuffer for our textures
      glGenFramebuffers(1, &_framebuffer);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
    }

    

    // Bind this texture to specific attachment
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachments[i], _textureTarget, _textureIds[i], 0);
  }

  // If no framebuffer
  if (_framebuffer == 0)
  {
    // Just return
    return;
  }

  // If this texture doesn't have depth attachment
  if (!hasDepthAttachment)
  {
    // Use render buffer
    glGenRenderbuffers(1, &_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, static_cast<GLsizei>(_width), static_cast<GLsizei>(_height));

    // Bind renderbuffer to framebuffer as depth buffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer);
  }
  
  // Draw all buffers
  glDrawBuffers(static_cast<GLsizei>(_textureIds.size()), drawBuffers.data());

  // If not complete framebuffer
  auto result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (result != GL_FRAMEBUFFER_COMPLETE)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::IncompleteFrameBufferInRenderingToTextures, 
      "Framebuffer creation failed!", ""
    );
  }

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

  // Push empty value to vector
  _textureIds.push_back(0ULL);

  // Let OpenGL create new texture ID
  glGenTextures(1, &_textureIds.back());
  
  // Bind to this texture
  glBindTexture(GL_TEXTURE_2D, _textureIds.back());

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

size_t Texture::GetTextureId() const
{
  if (_textureIds.empty())
  {
    PUSH_EDITOR_ERROR(
      eEngineError::GettingIdOfEmptyTexture,
      "Getting ID of empty Texture.", 
      ""
    );

    return 0;
  }

  return _textureIds.front();
}

std::vector<size_t> Texture::GetTextureIds() const
{
  if (_textureIds.empty())
  {
    PUSH_EDITOR_ERROR(
      eEngineError::GettingIdOfEmptyTexture,
      "Getting IDs of empty Texture.", 
      ""
    );

    return std::vector<size_t>();
  }

  std::vector<size_t> ids;
  for (auto&& id : _textureIds)
  {
    ids.push_back(id);
  }
  
  return ids;
}

bool Texture::LoadTextures(const std::vector<std::string>& textureFilepaths)
{
  bool result = true;

  for (auto&& textureFilepath : textureFilepaths)
  {
    result = result && LoadTexture(textureFilepath);
  }

  return result;
}

void Texture::SetAsRenderTarget(Scene* pScene) const
{
  // Tell main Camera what is render targer
  pScene->GetEditorCamera()->SetTargetTexture(this);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
  glViewport(0, 0, static_cast<GLsizei>(_width), static_cast<GLsizei>(_height));
}

bool Texture::InitTextresAsRenderTarget(std::vector<std::byte> data, GLenum attachments, size_t width, size_t height)
{
  _width = width;
  _height = height;

  _numColorChanels = 3;

  // Push empty value to vector
  _textureIds.push_back(0ULL);

  // Let OpenGL create new texture ID
  glGenTextures(1, &_textureIds.back());

  // Bind to this texture so we can write data to it
  glBindTexture(_textureTarget, _textureIds.back());
 
  // Fill texture data into the GPU memory
  glTexImage2D(
    _textureTarget,
    0,          // Mipmaps 
    GL_RGBA,    // Data fomrat in GPU memory
    static_cast<GLsizei>(_width),
      static_cast<GLsizei>(_height),
    0,          // Legacy border
    GL_RGBA,    // Type on input
    GL_UNSIGNED_BYTE,
    data.data()
  );


  // Generate mipmaps automaticaly
  //glGenerateMipmap(_textureTarget);

  // Setup texture parameters
  glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  /*glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
  glTexParameterfv(_textureTarget, GL_TEXTURE_BORDER_COLOR, borderColor);*/


  glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  std::vector<GLenum> attachmentsVector;
  attachmentsVector.push_back(attachments);
  InitRenderTargets(attachmentsVector);

  // Unbind from this texture
  glBindTexture(_textureTarget, 0);

  return true;
}

void Texture::UseTexture(size_t textureUnit, size_t index)
{
  // Check if not out of bounds
  if (index >= _textureIds.size())
  {
    PUSH_EDITOR_ERROR(
      eEngineError::TryingToUseNonExistingTextureOnMaterial,
      "Trying to use Texture that does not exist", ""
    );
  }

  // TODO: Use all units
  glActiveTexture(GL_TEXTURE1 + static_cast<GLenum>(textureUnit)); // Minimum of 16 texture unit available
  glBindTexture(_textureTarget, _textureIds[index]);
}

void Texture::ClearTexture()
{
  // Delete texture from GPU
  glDeleteTextures(static_cast<GLsizei>(_textureIds.size()), _textureIds.data());

  // Delete any attached framebuffer
  if (_framebuffer != 0)
  {
    // Tell OpenGL to delete this 
    glDeleteFramebuffers(1, &_framebuffer);
  }

  // If render buffer present
  if (_renderBuffer != 0)
  {
    // Tell OpenGL to delete it
    glDeleteFramebuffers(1, &_framebuffer);
  }

  // Reset attributes
  _textureIds.clear();
  _width = 0;
  _height = 0;
  _numColorChanels = 0;
}
