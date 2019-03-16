
#include "Material.h"

#include "ComponentManager.h"

#include "Shininess.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "Texture.h"

using namespace SYE;

Material::Material(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Component(pOwnerEntity, pOwnerComponent, false, true, slotIndex, type),
  _pMeshRenderer(nullptr),
  _shader(GetShaderManagerPtr()->GetStandardShader()),
  _orthoShadowMapShader(GetShaderManagerPtr()->GetStandardOrthoShadowMapShader()),
  _perspectiveShadowMapShader(GetShaderManagerPtr()->GetStandardPerspectiveShadowMapShader())
{
  // Make sure we have valid Shaders
  assert(_shader != nullptr);
  assert(_orthoShadowMapShader != nullptr);
  assert(_perspectiveShadowMapShader != nullptr);
}

Material::~Material() noexcept
{
  // Clear shaders
  ClearShader();
  ClearOrthoShadowMapShader();
}

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

size_t Material::AddTexture(Vector3f colour)
{
  // Create new Texture Component
  Texture* pTexture = GetComponentManagerPtr()->CreateComponent<Texture>(_pOwnerEntity, this);
  bool result = pTexture->LoadTexture(colour);
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

void Material::AddShader()
{
  _shader = GetShaderManagerPtr()->GetStandardShader();
}

void Material::AddOrthoShadowMapShader()
{
  _orthoShadowMapShader = GetShaderManagerPtr()->GetStandardOrthoShadowMapShader();
}

void Material::AddPerspectiveShadowMapShader()
{
  _perspectiveShadowMapShader = GetShaderManagerPtr()->GetStandardPerspectiveShadowMapShader();
}

NewShader*  Material::AddShader(
  std::vector<NewShader::eUniforms> _requiredUniforms,
  std::vector<NewShader::eUniforms> _optionalUniforms,
  std::string_view vsFilepath, 
  std::string_view fsFilepath,
  std::string_view tsFilepath,
  std::string_view gsFilepath
)
{
  // Ask ShaderManager to create new Shader
  _shader = GetShaderManagerPtr()->CreateShader(_requiredUniforms, _optionalUniforms, vsFilepath, fsFilepath, tsFilepath, gsFilepath);

  return 0ULL;
}

NewShader*  Material::AddOrthoShadowMapShader(
  std::vector<NewShader::eUniforms> _requiredUniforms,
  std::vector<NewShader::eUniforms> _optionalUniforms,
  std::string_view vsFilepath,
  std::string_view fsFilepath,
  std::string_view tsFilepath,
  std::string_view gsFilepath
)
{
  // Ask ShaderManager to create new Shader
  _orthoShadowMapShader = GetShaderManagerPtr()->CreateShader(_requiredUniforms, _optionalUniforms, vsFilepath, fsFilepath, tsFilepath, gsFilepath);

  return _orthoShadowMapShader;
}

void Material::AddShader(NewShader* pShader)
{
  _shader = pShader;
}

void Material::AddOrthoShadowMapShader(NewShader* pShader)
{
  _orthoShadowMapShader = pShader;
}

void Material::ClearOrthoShadowMapShader()
{
  _orthoShadowMapShader = nullptr;
}

void Material::ClearProjectionShadowMapShader()
{
  _perspectiveShadowMapShader = nullptr;
}

void Material::ClearShader()
{
  _shader = nullptr;
}