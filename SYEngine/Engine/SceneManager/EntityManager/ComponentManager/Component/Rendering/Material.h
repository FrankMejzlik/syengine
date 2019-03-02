#pragma once


#include <vector>

#include <GL/glew.h>

#include "common.h"
#include "Component.h"
#include "Texture.h"
#include "Shader.h"


namespace SYE
{

class Shininess;

/**
 * Component describing how object sufaces look and how they
 * manage light rays.
 *
 * Using:
 * @see   class Texture
 * @see   class Shininess
 */
class Material:
  public Component
{
public:
  Material() = delete;
  Material(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::MATERIAL
  );

  size_t AddTexture();
  size_t AddTexture(Vector3f colour);
  size_t AddTexture(std::string_view filePathToTexture);
  size_t AddTexture(Texture* pTexture);

  size_t AddShininess();
  size_t AddShininess(dfloat specularIntensity, dfloat shininessIntensity);
  size_t AddShininess(Shininess* pShininess);
  void AddTextureToShininessIndex(size_t textureIndex, size_t shininessIndex);

  size_t AddShader();
  size_t AddShader(std::string_view filePath);
  size_t AddShader(Shader* pShader);
  void AddTextureToShaderIndex(size_t textureIndex, size_t shaderIndex);

  void UseMaterial(
    GLuint ul_specularIntensityLocation, GLuint ul_shininessIntensitLocation,
    unsigned int textureIndex
  );

protected:
  // List of textures of this material
  std::vector<Texture*> _textures;

  std::vector<Shininess*> _shininesses;
  std::vector<size_t> _textureToShininesIndex;

  std::vector<Shader*> _shaders;
  std::vector<size_t> _textureToShaderIndex;

 };

}