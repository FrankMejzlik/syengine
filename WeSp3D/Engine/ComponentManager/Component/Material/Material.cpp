#include "Material.h"

using namespace WeSp;

extern void GetGLErrors(const  char* file, unsigned int lineNum);

Material::Material():
  _specularIntensity(0), _shininess(0)
{}

Material::Material(GLfloat specularIntensity, GLfloat shininess) :
  _specularIntensity(specularIntensity), _shininess(shininess)
{
  
}


Material::~Material()
{}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
  glUniform1f(specularIntensityLocation, _specularIntensity);
  glUniform1f(shininessLocation, _shininess);

}
