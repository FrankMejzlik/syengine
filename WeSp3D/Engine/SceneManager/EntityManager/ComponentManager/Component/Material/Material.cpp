#include "Material.h"

using namespace WeSp;

Material::Material()
{
  // Add default Texture and Shininess.
  _textures.push_back(Texture());
  _shininesses.push_back(Shininess());
}

Material::~Material()
{}

size_t Material::AddTexture(std::string filePathToTexture)
{
  Texture newTexture(filePathToTexture.c_str());
  newTexture.LoadTexture();
  _textures.push_back(newTexture);

  return _textures.size() - 1;
}

size_t Material::AddShininess(dfloat specularIntensity, dfloat shininessIntensity)
{
  _shininesses.push_back(Shininess(specularIntensity, shininessIntensity));
  
  return _shininesses.size() - 1;
}

void Material::UseMaterial(
  GLuint ul_specularIntensityLocation, GLuint ul_shininessIntensitLocation,
  unsigned int textureIndex, unsigned int shininessIndex
)
{
  // Apply texture.
  _textures[textureIndex].UseTexture();

  // Appply Shininess.
  glUniform1f(ul_specularIntensityLocation, _shininesses[shininessIndex].GetSpecularIntensity());
  glUniform1f(ul_shininessIntensitLocation, _shininesses[shininessIndex].GetShininessIntensity());

}
