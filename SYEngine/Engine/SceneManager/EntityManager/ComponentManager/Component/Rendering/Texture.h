#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>


#include "common.h"
#include "Component.h"

namespace SYE 
{

class Texture:
  public Component
{
  // Methods
public:
  Texture() = delete;
  Texture(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::TEXTURE
  );
  ~Texture() noexcept;
  
  bool LoadTexture(std::string_view texturePathFile);
  bool LoadTexture(Vector3f colour);
  bool LoadTextures(const std::vector<std::string>& textureFilepaths);

  //bool LoadTextures(const std::vector< std::vector<std::byte> >& data, const std::vector<GLenum>& attachments);
  bool InitTextresAsRenderTarget(std::vector<std::byte>, GLenum attachments, size_t width, size_t height);

  
  bool LoadDepthTexture(size_t width, size_t height);
  

  void UseTexture(size_t textureUnit = 0ULL, size_t index = 0ULL);
  void ClearTexture();

  /*!
   * Sets this texture as render target for OpenGL
   */
  void SetAsRenderTarget(Scene* pScene) const;

  size_t GetTextureId() const;
  std::vector<size_t> GetTextureIds() const;


private:
  void InitRenderTargets(const std::vector<GLenum>& attachments);
  void InitDepthTextue();


  // Attributes
private:
  //! List of texture ID handlers recieved from OpenGL
  std::vector<GLuint> _textureIds;

  //! Width of our textures
  size_t _width;

  //! Height of our textures
  size_t _height;

  //! Number of color channgels used in texture data
  size_t _numColorChanels;

  // What kind of texture we are
  GLenum _textureTarget;

  // Framebuffer attached to our textures
  GLuint _framebuffer;

  // Renderbuffer if need depth text when rendering to texture without depth attachment
  GLuint _renderBuffer;

};

}