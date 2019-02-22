#include "SpotLight.h"

#include "Component.h"
#include "Entity.h"
#include "Transform.h"

using namespace SYE;


SpotLight::SpotLight(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept :
  PointLight(pOwnerEntity, subModulesConstRef, primaryComponentSlots)
{
  _type = eType::SPOT_LIGHT;
}

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
  Vector3f pos = _pTransform->GetPosition();

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


