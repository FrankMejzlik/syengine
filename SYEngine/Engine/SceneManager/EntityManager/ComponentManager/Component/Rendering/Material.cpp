#include "Material.h"

#include "ComponentManager.h"

using namespace SYE;

Material::Material(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Component(pOwnerEntity, pOwnerComponent, false, true, slotIndex, type)
{}


size_t Material::AddShininess()
{
  // Add default Shininess
  Shininess* pShininess = GetComponentManagerPtr()->CreateComponent<Shininess>(_pOwnerEntity, this);

  _shininesses.push_back(pShininess);

  return (_shininesses.size() - 1ULL);
}

size_t Material::AddShininess(dfloat specularIntensity, dfloat shininessIntensity)
{
  // Create new Shininess Component
  Shininess* pShininess = GetComponentManagerPtr()->CreateComponent<Shininess>(_pOwnerEntity, this);
  
  // Set correct values
  pShininess->SetSpecularIntensity(specularIntensity);
  pShininess->SetShininessIntensity(shininessIntensity);
  
  _shininesses.push_back(pShininess);

  return _shininesses.size() - 1;
}

size_t Material::AddShininess(Shininess* pShininess)
{
  _shininesses.push_back(pShininess);

  return _shininesses.size() - 1;
}

size_t Material::AddTexture()
{
  // Create new Texture Component
  Texture* pTexture = GetComponentManagerPtr()->CreateComponent<Texture>(_pOwnerEntity, this);

  // Load default texture
  bool result = pTexture->LoadTexture(FILEPATH_DEFAULT_TEXTURE);
  if (result == false)
  {
    return SIZE_T_ERROR_VALUE;
  }

  _textures.push_back(pTexture);

  return _textures.size() - 1;
}

size_t Material::AddTexture(std::string_view filePathToTexture)
{
  // Create new Texture Component
  Texture* pTexture = GetComponentManagerPtr()->CreateComponent<Texture>(_pOwnerEntity, this);
  bool result = pTexture->LoadTexture(filePathToTexture);
  if (result == false)
  {
    return SIZE_T_ERROR_VALUE;
  }

  _textures.push_back(pTexture);

  return _textures.size() - 1;
}

size_t Material::AddTexture(Texture* pTexture)
{
  // Insert new Texture
  _textures.push_back(pTexture);

  return _textures.size() - 1;
}

void Material::AddTextureToShininessIndex(size_t textureIndex, size_t shininessIndex)
{
  // Make sure container is big enough
  _textureToShininesIndex.resize(textureIndex + 1);

  _textureToShininesIndex[textureIndex] = shininessIndex;
}

void Material::UseMaterial(
  GLuint ul_specularIntensityLocation, GLuint ul_shininessIntensitLocation,
  unsigned int textureIndex
)
{
  // Apply texture
  _textures[textureIndex]->UseTexture();

  // Appply Shininess
  glUniform1f(ul_specularIntensityLocation, _shininesses[_textureToShininesIndex[textureIndex]]->GetSpecularIntensity());
  glUniform1f(ul_shininessIntensitLocation, _shininesses[_textureToShininesIndex[textureIndex]]->GetShininessIntensity());

}

size_t Material::AddShader()
{
  LOG_NOT_IMPLEMENTED;
  return 0ULL;
}

size_t Material::AddShader(std::string_view filePath)
{
  UNREFERENCED_PARAMETER(filePath);

  LOG_NOT_IMPLEMENTED;
  return 0ULL;
}

size_t Material::AddShader(Shader* pShader)
{
  UNREFERENCED_PARAMETER(pShader);

  LOG_NOT_IMPLEMENTED;
  return 0ULL;
}

void Material::AddTextureToShaderIndex(size_t textureIndex, size_t shaderIndex)
{
  UNREFERENCED_PARAMETER(textureIndex);
  UNREFERENCED_PARAMETER(shaderIndex);

  LOG_NOT_IMPLEMENTED;
}
