#pragma once

#include "Component.h"

#include <GL/glew.h>

namespace WeSp 
{

class Material:
  public Component
{
public:
  Material();
  Material(GLfloat specularIntensity, GLfloat shininess);
  ~Material();

  void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

private:
  GLfloat _specularIntensity;
  GLfloat _shininess;


};

}