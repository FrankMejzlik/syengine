#pragma once


#include <vector>

#include "common.h"
#include "Component.h"
#include "Texture.h"

#include <GL/glew.h>

namespace WeSp 
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
  Shininess(std::shared_ptr<Entity> pEntity):
    Component(pEntity),
    _specularIntensity(0.3f), _shininessIntensity(4)
  {}

  // Parametrized constructor.
  Shininess(std::shared_ptr<Entity> pEntity, dfloat specularIntensity, dfloat shininessIntensity):
    Component(pEntity),
    _specularIntensity(specularIntensity), _shininessIntensity(shininessIntensity)
  {}


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

  /**
   * Adds default Texture and Shininess.
   */
  Material(std::shared_ptr<Entity> pEntity);
  ~Material();

  /**
   * Adds Texture to this Material component and returns index of it.
   */
  size_t AddTexture(std::string filePathToTexture);

  /**
   * Adds Shininess to this Material component and returns index of it.
   */
  size_t AddShininess(dfloat specularIntensity, dfloat shininessIntensity);

  // TODO!: Abstract this out 
  void UseMaterial(
    GLuint ul_specularIntensityLocation, GLuint ul_shininessIntensitLocation,
    unsigned int textureIndex, unsigned int shininessIndex
  );

protected:
  // List of textures of this material
  std::vector<Texture> _textures;
  std::vector<Shininess> _shininesses;

 };

}