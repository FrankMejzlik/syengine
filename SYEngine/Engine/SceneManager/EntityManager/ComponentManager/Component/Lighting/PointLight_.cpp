#include "PointLight_.h"

#include "Component.h"
#include "Entity.h"
#include "Transform.h"

using namespace SYE;


PointLight::PointLight(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept:
  Light(pOwnerEntity, subModulesConstRef)
{
  _pShadowMap = std::make_unique<OmniShadowMap>();
  _type = eType::POINT_LIGHT;
}

PointLight::~PointLight() noexcept
{}


void PointLight::SetShadowDimensions(glm::ivec3 shadowDimensions, dfloat nearPlane, dfloat farPlane)
{
  _shadowDimensions = shadowDimensions;

  float aspect = (float)_shadowDimensions.x / (float)_shadowDimensions.y;
  _lightProjectionMatrix = glm::perspective(glm::radians(90.0f), aspect, _nearPlane, _farPlane);

  _pShadowMap->Init(_shadowDimensions.x, _shadowDimensions.y);

  _nearPlane = nearPlane;
  _farPlane = farPlane;
}


void PointLight::SetCoeficients(dfloat constant, dfloat linear, dfloat exponent)
{
  _constant = constant;
  _linear = linear;
  _exponent = exponent;
}

Vector3f PointLight::GetPosition() const 
{ 
  return _pOwnerEntity->GetTransform()->GetPosition(); 
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
  Vector3f pos = _pOwnerEntity->GetTransform()->GetPosition();

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

  glm::vec3 pos = _pOwnerEntity->GetTransform()->GetPosition().GetData();

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
