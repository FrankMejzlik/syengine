#include "Material.h"

using namespace SYE;

_Material::_Material(Entity* pEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef):
  Component(pEntity, subModulesConstRef, false)
{
  // Add default Texture and Shininess.
  // TODO: Allocate those properly.
  _textures.push_back(Texture(pEntity, subModulesConstRef));
  _shininesses.push_back(_Shininess(pEntity, subModulesConstRef));

  _type = eType::MATERIAL;
}

_Material::~_Material()
{}

size_t _Material::AddTexture(std::string filePathToTexture)
{
  Texture newTexture(_pOwnerEntity, _subModules, filePathToTexture.c_str());
  newTexture.LoadTexture();
  _textures.push_back(newTexture);

  return _textures.size() - 1;
}

size_t _Material::AddShininess(dfloat specularIntensity, dfloat shininessIntensity)
{
  _shininesses.push_back(_Shininess(_pOwnerEntity, _subModules, specularIntensity, shininessIntensity));
  
  return _shininesses.size() - 1;
}

void _Material::UseMaterial(
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
