#pragma once

/** 
* @file
* @breif Class @ref SYE::_SceneBuilder implementation
*/

#include "Script.h"
#include "Scene.h"
#include "Entity.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "PointLight.h"

#include "generic_script_includes.h"

namespace SYE
{

/**
 * @brief   Class responsible for building initial Scene instance before launch
 */
class _SceneBuilderBase
{
public:
  /**
   * Builds initial scene.
   *
   * This is special script that is executed exactly once before game itself starts.
   *
   * @param   Scene*  Pointer to Scene instance we are building
   * @return  void
   */
  virtual void SetupScene(Scene* pScene) = 0;
};


}