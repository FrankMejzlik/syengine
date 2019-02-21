#include "Material_.h"

#include "ComponentManager.h"

using namespace SYE;

Material::Material(Entity* _pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots):
  Component(_pOwnerEntity, subModulesConstRef, primaryComponentSlots, false)
{
  _type = eType::MATERIAL;
}

Material::~Material()
{}

size_t Material::AddShininess()
{
  // Add default Shininess
  Shininess* pShininess = _pComponentManager->CreateComponent<Shininess>(_pOwnerEntity);

  _shininesses.push_back(pShininess);

  return (_shininesses.size() - 1ULL);
}

size_t Material::AddShininess(dfloat specularIntensity, dfloat shininessIntensity)
{
  // Create new Shininess Component
  Shininess* pShininess = _pComponentManager->CreateComponent<Shininess>(_pOwnerEntity);
  
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
  Texture* pTexture = _pComponentManager->CreateComponent<Texture>(_pOwnerEntity);

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
  Texture* pTexture = _pComponentManager->CreateComponent<Texture>(_pOwnerEntity);
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
  DLog(eLogType::Warning, "%s", "NOT IMPMLEMENTED!");
  return 0ULL;
}

size_t Material::AddShader(std::string_view filePath)
{
  UNREFERENCED_PARAMETER(filePath);

  DLog(eLogType::Warning, "%s", "NOT IMPMLEMENTED!");
  return 0ULL;
}

size_t Material::AddShader(Shader* pShader)
{
  UNREFERENCED_PARAMETER(pShader);

  DLog(eLogType::Warning, "%s", "NOT IMPMLEMENTED!");
  return 0ULL;
}

void Material::AddTextureToShaderIndex(size_t textureIndex, size_t shaderIndex)
{
  UNREFERENCED_PARAMETER(textureIndex);
  UNREFERENCED_PARAMETER(shaderIndex);

  DLog(eLogType::Warning, "%s", "NOT IMPMLEMENTED!");
}
