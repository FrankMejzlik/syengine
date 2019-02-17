#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>


#include "CommonValues.h"
#include "Component.h"

namespace SYE 
{

class Texture:
  public Component
{
public:
  Texture() = delete;
  Texture(Entity* pEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept;

  
  bool LoadTexture(std::string_view texturePathFile);
  void UseTexture();
  void ClearTexture();

  

private:
  GLuint textureID;
  int width, height, bitDepth;


#if !NEW_SSSEC_IMPLEMENTED
public:
  Texture(Entity* pEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, const char* const fileLocation);
  bool LoadTexture();

  char fileLocation[1024];

#endif



};

}