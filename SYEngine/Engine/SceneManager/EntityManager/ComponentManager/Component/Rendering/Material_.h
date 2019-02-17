#pragma once


#include <vector>

#include <GL/glew.h>

#include "common.h"
#include "Component.h"
#include "Texture.h"
#include "Shader.h"



namespace SYE 
{

/**
 * Describes how light is reflected from surfaces.
 *
 * Used in: 
 * @see   class Material
 */
class Shininess:
  public Component
{
public:
  Shininess() = delete;

  /**
   * Default constructor.
   * shiny: 1.0f, 512
   * dull: 0.3f  4
   */
  Shininess(
    Entity* pEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef
  ):
    Component(pEntity, subModulesConstRef, false),
    _specularIntensity(0.3f), _shininessIntensity(4)
  {}

  void SetSpecularIntensity(dfloat newValue) { _specularIntensity = newValue; }
  void SetShininessIntensity(dfloat newValue) { _shininessIntensity = newValue; }
  dfloat GetSpecularIntensity() const { return _specularIntensity; }
  dfloat GetShininessIntensity() const { return _shininessIntensity; }

private:
  dfloat _specularIntensity;
  dfloat _shininessIntensity;

  
};


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
  Material(Entity* pEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef);
  ~Material();


  size_t AddTexture();
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

#if !NEW_SSSEC_IMPLEMENTED
  // TODO!: Abstract this out 
  void UseMaterial(
    GLuint ul_specularIntensityLocation, GLuint ul_shininessIntensitLocation,
    unsigned int textureIndex, unsigned int shininessIndex
  );
#endif

protected:
  // List of textures of this material
  std::vector<Texture*> _textures;

  std::vector<Shininess*> _shininesses;
  std::vector<size_t> _textureToShininesIndex;

  std::vector<Shader*> _shaders;
  std::vector<size_t> _textureToShaderIndex;

 };

}