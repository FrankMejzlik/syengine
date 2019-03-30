#pragma once

#include <memory>

#include <GL/glew.h>

#pragma warning(push, 1)
#include <GLM/gtc/matrix_transform.hpp>
#pragma warning(pop)

#include "common.h"
#include "MathLibrary.h"
#include "Component.h"
#include "ShadowMap.h"


using namespace SYE;

namespace SYE 
{
class Texture;
class Transform;
class Shader;

class ShadowInfo
{
  // Methods
public:
  ShadowInfo(const Matrix4f& projectionMatrix) :
    _projectionMatrix(projectionMatrix)
  {};

  ShadowInfo(Matrix4f&& projectionMatrix) :
    _projectionMatrix(std::move(projectionMatrix))
  {};

  Matrix4f GetProjection()
  {
    return _projectionMatrix;
  }

  // Attributes
private:
  Matrix4f _projectionMatrix;
};


class Light:
  public Component
{
public:
  Light() = delete;
  Light(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = Component::eType::LIGHT
  );
  virtual ~Light() noexcept;

  glm::vec3 GetColour() const;
  virtual void SetColour(glm::vec3 colourVector);
  glm::vec3 GetIntensities() const;
  virtual void SetInensities(glm::vec3 lightIntensities);
  glm::ivec3 GetShadowDimensions() const;
  virtual void SetShadowDimensions(glm::ivec3 shadowDimensions);

  ShadowMap* dc_GetShadowMap() const;

  Texture* GetShadowMap() const { return _pShadowMap; }
  Shader* GetShader() const { return _pShader; }
  ShadowInfo* GetShadowInfo() const { return _pShadowInfo.get(); }

  void SetShader(Shader* pShader) { _pShader = pShader; }
  void SetShadowInfo(std::unique_ptr<ShadowInfo>&& pShadowInfo) { _pShadowInfo.reset(); _pShadowInfo = std::move(pShadowInfo); }


  const Vector3f& GetPositionConstRef() const;


protected:
#if !NEW_SHADOW_MAPPING_IMPLEMENTED

  // Computed shadow map for this light
  std::unique_ptr<ShadowMap> dc_pShadowMap;

#endif

  std::unique_ptr<ShadowInfo> _pShadowInfo;
  Texture* _pShadowMap;
  Shader* _pShader;

  // TODO: Make static/dynamic
  bool _isStatic;

  // Colour of light
  glm::vec3 _colourVector;
  // Intensities of specific light parts
  // x: ambient, y: diffuse, z: specular
  glm::vec3 _lightIntensities;
  // Dimensions of shadow map
  // x: width y: height z: unused
  glm::ivec3 _shadowDimensions;
  // Projection matrix for computing shadow map
  glm::mat4 _lightProjectionMatrix;
  // Matrix to transform world to window space from POV of light
  glm::mat4 _lightModelToWindowMatrix;


};

}
