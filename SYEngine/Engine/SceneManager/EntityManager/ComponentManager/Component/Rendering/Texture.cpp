

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
  _framebuffer(0)
{
}

Texture::~Texture() noexcept
{
  // Delete all textures on GPU
  ClearTexture();
}

bool Texture::LoadTexture(std::string_view texturePathFile)
{
  // Load texture data
  unsigned char* textureData = stbi_load(texturePathFile.data(), &_width, &_height, &numColorChanels, 0);

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
  if (numColorChanels == 3)
  {
    // Fill texture data into the GPU memory
    glTexImage2D(
      GL_TEXTURE_2D,
      0,          // Mipmaps 
      GL_RGB,    // Data fomrat in GPU memory
      _width,
      _height,
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
      _width,
      _height,
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

bool Texture::InitTextresForRendering(size_t count, const std::vector<GLenum>& attachments)
{
  UNREFERENCED_PARAMETER(count);
  UNREFERENCED_PARAMETER(attachments);

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

  for (size_t i = 0; i < _textureIds.size(); ++i)
  {
    // Befare of stencil bufferin future
    if (attachments[i] == GL_DEPTH_ATTACHMENT)
    {
      drawBuffers[i] = GL_NONE;
    }
    else
    {
      drawBuffers[i] = attachments[i];
    }

    drawBuffers[i] = attachments[i];

    if (attachments[i] == GL_NONE)
    {
      continue;
    }

    // If frame buffert not set yet
    if (_framebuffer == 0)
    {
      // Generate framebuffer for our textures
      glGenFramebuffers(1, &_framebuffer);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
    }

    // If no framebuffer
    if (_framebuffer == 0)
    {
      // Just return
      return;
    }

    // Bind this texture to specific attachment
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _textureTarget, _textureIds[0], 0);
  }

  // Draw all buffers
  glDrawBuffers(static_cast<GLsizei>(_textureIds.size()), drawBuffers.data());

  // If not complete framebuffer
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::IncompleteFrameBufferInRenderingToTextures, 
      "Framebuffer not complete!", ""
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

void Texture::SetAsRenderTarget() const
{
  auto t = _pOwnerEntity->GetOwnerScenePtr()->_renderTargetTexture;

  _pOwnerEntity->GetOwnerScenePtr()->GetEditorCamera()->SetTargetTexture(t);


  
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
  glViewport(0, 0, _width, _height);
}

bool Texture::InitTextresForRendering(std::vector<std::byte> data, GLenum attachments)
{
  numColorChanels = 4;

  // Push empty value to vector
  _textureIds.push_back(0ULL);

  // Let OpenGL create new texture ID
  glGenTextures(1, &_textureIds.back());

  // Bind to this texture so we can write data to it
  glBindTexture(_textureTarget, _textureIds.back());

  // If no Alpha chanel
  if (numColorChanels == 3)
  {
    // Fill texture data into the GPU memory
    glTexImage2D(
      _textureTarget,
      0,          // Mipmaps 
      GL_RGB,    // Data fomrat in GPU memory
      _width,
      _height,
      0,          // Legacy border
      GL_RGB,    // Type on input
      GL_UNSIGNED_BYTE,
      data.data()
    );
  }
  // Else alpha chanell present
  else
  {
    // Fill texture data into the GPU memory
    glTexImage2D(
      _textureTarget,
      0,          // Mipmaps 
      GL_RGBA,    // Data fomrat in GPU memory
      _width,
      _height,
      0,          // Legacy border
      GL_RGBA,    // Type on input
      GL_UNSIGNED_BYTE,
      data.data()
    );
  }

  // Generate mipmaps automaticaly
  glGenerateMipmap(_textureTarget);

  // Setup texture parameters
  glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
  glTexParameterfv(_textureTarget, GL_TEXTURE_BORDER_COLOR, borderColor);


  glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

  // Reset attributes
  _textureIds.clear();
  _width = 0;
  _height = 0;
  numColorChanels = 0;
}
