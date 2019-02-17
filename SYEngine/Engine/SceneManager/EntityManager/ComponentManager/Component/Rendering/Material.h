#pragma once


#include <vector>

#include "common.h"
#include "Component.h"
#include "Texture.h"

#include <GL/glew.h>

namespace SYE 
{

/**
 * Describes how light is reflected from surfaces.
 *
 * Used in: 
 * @see   class Material
 */
class _Shininess:
  public Component
{
public:
  _Shininess() = delete;

  /**
   * Default constructor.
   * shiny: 1.0f, 512
   * dull: 0.3f  4
   */
  _Shininess(
    Entity* pEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef,
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
    ):
    Component(pEntity, subModulesConstRef, primaryComponentSlots, false),
    _specularIntensity(0.3f), _shininessIntensity(4)
  {}

  // Parametrized constructor.
  _Shininess(
    Entity* pEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef,
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    dfloat specularIntensity, dfloat shininessIntensity
  ):
    Component(pEntity, subModulesConstRef, primaryComponentSlots, false),
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
class _Material:
  public Component
{
public:
  _Material() = delete;

  /**
   * Adds default Texture and Shininess.
   */
  _Material(Entity* pEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots);
  ~_Material();

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
  std::vector<_Shininess> _shininesses;
  // TODO: Implement shader per material
  //std::vector<Shader*> _shaders;

 };

}