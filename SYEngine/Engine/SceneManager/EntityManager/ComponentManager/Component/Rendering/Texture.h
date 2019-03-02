#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>


#include "common.h"
#include "Component.h"

namespace SYE 
{

class Texture:
  public Component
{
public:
  Texture() = delete;
  Texture(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::TEXTURE
  );
  
  bool LoadTexture(std::string_view texturePathFile);
  bool LoadTexture(Vector3f colour);
  void UseTexture();
  void ClearTexture();


private:
  GLuint textureID;
  int width, height, bitDepth;


};

}