#pragma once


#include <vector>

#include <GL/glew.h>

#include "common.h"
#include "Component.h"
#include "Shader.h"



namespace SYE
{
class Shader;
class NewShader;
class Texture;
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
  ~Material() noexcept;

  size_t AddTexture();
  size_t AddTexture(Vector3f colour);
  size_t AddTexture(std::string_view filePathToTexture);
  size_t AddTexture(Texture* pTexture);

  size_t AddShininess();
  size_t AddShininess(dfloat specularIntensity, dfloat shininessIntensity);
  size_t AddShininess(Shininess* pShininess);
  void AddTextureToShininessIndex(size_t textureIndex, size_t shininessIndex);

  void AddShader();
  void AddOrthoShadowMapShader();
  void AddPerspectiveShadowMapShader();

  NewShader* AddShader(
    std::vector<NewShader::eUniforms> _requiredUniforms,
    std::vector<NewShader::eUniforms> _optionalUniforms,
    std::string_view vsFilepath, 
    std::string_view fsFilepath,
    std::string_view tsFilepath  = std::string_view(),
    std::string_view gsFilepath  = std::string_view()
  );
  NewShader* AddOrthoShadowMapShader(
    std::vector<NewShader::eUniforms> _requiredUniforms,
    std::vector<NewShader::eUniforms> _optionalUniforms,
    std::string_view vsFilepath, 
    std::string_view fsFilepath,
    std::string_view tsFilepath  = std::string_view(),
    std::string_view gsFilepath  = std::string_view()
  );

  void AddShader(NewShader* pShader);
  void AddOrthoShadowMapShader(NewShader* pShader);
  
  

  void UseMaterial(
    GLuint ul_specularIntensityLocation, GLuint ul_shininessIntensitLocation,
    unsigned int textureIndex
  );

  NewShader* GetShdaer() const { return _shader; }
  NewShader* GetOrthoShadowMapShdaer() const { return _orthoShadowMapShader; }
  NewShader* GetPerspectiveShadowMapShdaer() const { return _perspectiveShadowMapShader; }

  void ClearOrthoShadowMapShader();
  void ClearProjectionShadowMapShader();
  void ClearShader();

protected:
  //! Pointer to owner MeshRenderer
  MeshRenderer* _pMeshRenderer;

  // List of textures of this material
  std::vector<Texture*> _textures;

  std::vector<Shininess*> _shininesses;
  std::vector<size_t> _textureToShininesIndex;

  NewShader* _shader;
  NewShader* _orthoShadowMapShader;
  NewShader* _perspectiveShadowMapShader;
 };

}