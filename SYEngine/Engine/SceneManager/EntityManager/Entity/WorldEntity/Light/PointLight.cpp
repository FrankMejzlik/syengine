#include "PointLight.h"

using namespace SYE;


PointLight::PointLight(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 colourVector,
  glm::vec3 lightIntensities,
  glm::vec3 shadowDimensions,
  glm::vec2 planeDimensions,
  glm::vec3 coefficients
) :
  Light(
    pComponentManager,
    positionVector, rotationVector, scaleVector,
    colourVector,
    lightIntensities,
    shadowDimensions
  ),
  _constant(coefficients.x), _linear(coefficients.y), _exponent(coefficients.z),
  _nearPlane(planeDimensions.x), _farPlane(planeDimensions.y)
{
  _pShadowMap = std::make_shared<OmniShadowMap>(OmniShadowMap());

  float aspect = (float)_shadowDimensions.x / (float)_shadowDimensions.y;
  _lightProjectionMatrix = glm::perspective(glm::radians(90.0f), aspect, _nearPlane, _farPlane);

  _pShadowMap->Init(_shadowDimensions.x, _shadowDimensions.y);
}

PointLight::~PointLight()
{}

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
  glUniform3f(ambientColourLocation, _colourVector.x, _colourVector.y, _colourVector.z);

  if (pointsAreOn)
  {
    glUniform3f(positionLocation, _positionVector.x, _positionVector.y, _positionVector.z);
  }
  else
  {
    glUniform3f(positionLocation, 1000.0, 1000.0, 1000.0);
  }
  
  glUniform1f(ambientIntensityLocation, _lightIntensities.x);
  glUniform1f(diffuseIntensityLocation, _lightIntensities.y);
  
  glUniform1f(constantLocation, _constant);
  glUniform1f(linearLocation, _linear);
  glUniform1f(exponentLocation, _exponent);
}

std::vector<glm::mat4> PointLight::GetOmniLightModelToWorldMatrices()
{
  std::vector<glm::mat4> lightMatrices;

  // +x, -x
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(_positionVector, _positionVector + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(_positionVector, _positionVector + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    
  // +y, -y
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(_positionVector, _positionVector + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(_positionVector, _positionVector + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));

  // +z, -z
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(_positionVector, _positionVector + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
  lightMatrices.push_back(_lightProjectionMatrix * glm::lookAt(_positionVector, _positionVector + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
  
  return lightMatrices;
}

glm::vec3 PointLight::GetPosition()
{
  return _positionVector;
}

GLfloat PointLight::GetFarPlane()
{
  return _farPlane;
}
