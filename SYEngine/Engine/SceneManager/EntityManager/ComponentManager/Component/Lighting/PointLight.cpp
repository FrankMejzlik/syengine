#include "PointLight.h"

#include "Component.h"
#include "Entity.h"
#include "Transform.h"

using namespace SYE;


PointLight::PointLight(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Light(pOwnerEntity, pOwnerComponent, slotIndex, type)
{
  dc_pShadowMap = std::make_unique<OmniShadowMap>();
}

PointLight::~PointLight() noexcept
{}


void PointLight::SetShadowDimensions(glm::ivec3 shadowDimensions, dfloat nearPlane, dfloat farPlane)
{
  _shadowDimensions = shadowDimensions;
  _nearPlane = nearPlane;
  _farPlane = farPlane;


  float aspect = (float)_shadowDimensions.x / (float)_shadowDimensions.y;
  _lightProjectionMatrix = glm::perspective(glm::radians(90.0f), aspect, _nearPlane, _farPlane);

  dc_pShadowMap->Init(_shadowDimensions.x, _shadowDimensions.y);

  _nearPlane = nearPlane;
  _farPlane = farPlane;
}


void PointLight::SetCoeficients(Vector3f coefficients)
{
  _constant = coefficients.GetX();
  _linear = coefficients.GetY();
  _exponent = coefficients.GetZ();
}

void PointLight::UseLight(
  GLuint ambientIntensityLocation, 
  GLuint ambientColourLocation, 
  GLuint diffuseIntensityLocation, 
  GLuint positionLocation, 
  GLuint constantLocation, 
  GLuint linearLocation, 
  GLuint exponentLocation
)
{
  Vector3f pos = GetTransformPtr()->GetPosition();

  glUniform3f(ambientColourLocation, _colourVector.x, _colourVector.y, _colourVector.z);

  glUniform3f(positionLocation, pos.GetX(), pos.GetY(), pos.GetZ());
  
  glUniform1f(ambientIntensityLocation, _lightIntensities.x);
  glUniform1f(diffuseIntensityLocation, _lightIntensities.y);
  
  glUniform1f(constantLocation, _constant);
  glUniform1f(linearLocation, _linear);
  glUniform1f(exponentLocation, _exponent);
}

std::vector<glm::mat4> PointLight::GetOmniLightModelToWorldMatrices()
{
  std::vector<glm::mat4> lightMatrices;

  glm::vec3 pos = GetTransformPtr()->GetPosition().GetData();

  // +x, -x
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(pos, pos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(pos, pos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    
  // +y, -y
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(pos, pos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(pos, pos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));

  // +z, -z
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
  
  return lightMatrices;
}


GLfloat PointLight::GetFarPlane()
{
  return _farPlane;
}
