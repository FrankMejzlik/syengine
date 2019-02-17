#include "SpotLight_.h"

#include "Component.h"
#include "Entity.h"
#include "Transform.h"

using namespace SYE;


SpotLight::SpotLight(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept :
  PointLight(pOwnerEntity, subModulesConstRef)
{}

SpotLight::~SpotLight() noexcept
{}


void SpotLight::SetConeAngle(dfloat angle)
{
  _coneAngle = angle;
  _processedConeAngle = cosf(glm::radians(_coneAngle));
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
  Vector3f pos = _pOwnerEntity->GetTransform()->GetPosition();

  glUniform3f(ambientColourLocation, _colourVector.x, _colourVector.y, _colourVector.z);
  glUniform1f(ambientIntensityLocation, _lightIntensities.x);
  glUniform1f(diffuseIntensityLocation, _lightIntensities.y);


  glUniform3f(positionLocation, pos.GetX(), pos.GetY(), pos.GetZ());

  glUniform1f(constantLocation, _constant);
  glUniform1f(linearLocation, _linear);
  glUniform1f(exponentLocation, _exponent);

  glUniform3f(directionLocation, pos.GetX(), pos.GetY(), pos.GetZ());
  glUniform1f(edgeLocation, _processedConeAngle);
}

