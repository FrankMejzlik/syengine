#pragma once

#include <map>

#include "common.h"
#include "BaseModule.h"
#include "ControllerManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "ModelManager.h"
#include "SkyboxManager.h"
#include "TextureManager.h"

namespace WeSp {

class ComponentManager:
    public BaseModule
{
public:
  ComponentManager() = delete;
  ComponentManager(BaseModule &parentModule);
  ~ComponentManager();
  bool Initialize();
  bool Terminate();

};

}