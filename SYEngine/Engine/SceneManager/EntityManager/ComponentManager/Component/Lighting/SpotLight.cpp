#include "SpotLight.h"

#include "Component.h"
#include "Entity.h"
#include "Transform.h"

using namespace SYE;


SpotLight::SpotLight(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  PointLight(pOwnerEntity, pOwnerComponent, slotIndex, type)
{}

SpotLight::~SpotLight() noexcept
{}



void SpotLight::SetConeAngle(dfloat angle)
{
  _coneAngle = angle;
  _processedConeAngle = cosf(glm::radians(_coneAngle));
}

void SpotLight::SetLightDirection(Vector3f direction)
{
  _lightDirection = glm::normalize(direction.GetData());
}


void SpotLight::UseLight(
  GLuint ambientIntensityLocation, 
  GLuint ambientColourLocation, 
  GLuint diffuseIntensityLocation, 
  GLuint positionLocation, 
  GLuint directionLocation, 
  GLuint constantLocation, 
  GLuint linearLocation, 
  GLuint exponentLocation, 
  GLuint edgeLocation
)
{
  Vector3f pos = GetTransformPtr()->GetPosition();

  glUniform3f(ambientColourLocation, _colourVector.x, _colourVector.y, _colourVector.z);
  glUniform1f(ambientIntensityLocation, _lightIntensities.x);
  glUniform1f(diffuseIntensityLocation, _lightIntensities.y);


  glUniform3f(positionLocation, pos.GetX(), pos.GetY(), pos.GetZ());

  glUniform1f(constantLocation, _constant);
  glUniform1f(linearLocation, _linear);
  glUniform1f(exponentLocation, _exponent);

  glUniform3f(directionLocation, _lightDirection.x, _lightDirection.y, _lightDirection.z);
  glUniform1f(edgeLocation, _processedConeAngle);
}


