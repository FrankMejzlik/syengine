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
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::TEXTURE
  );
  
  bool LoadTexture(std::string_view texturePathFile);
  void UseTexture();
  void ClearTexture();


private:
  GLuint textureID;
  int width, height, bitDepth;


};

}