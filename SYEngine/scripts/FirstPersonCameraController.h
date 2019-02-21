#pragma once

/**
 * First person Camera controller script
 *
 */

#include "common.h"
#include "Script.h"

namespace SYE 
{

class FirstPersonCameraController :
  public Script
{
public:
  FirstPersonCameraController() = delete;
  FirstPersonCameraController(
    Entity* pOwnerEntity,
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef,
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
  ) noexcept :
    Script(pOwnerEntity, subModulesConstRef, primaryComponentSlots)
  {}
  virtual ~FirstPersonCameraController() noexcept {}


  /**
   * Initialize this script
   *
   * Called once when parent Entity is being initialized.
   */
  virtual void OnInitializeScene()
  {

  }

  /**
   * Do all things you need to do in each frame
   *
   * Called once per frame.
   */
  virtual void OnProcessFrame(dfloat deltaTime, Scene* pScene)
  {
    UNREFERENCED_PARAMETER(deltaTime);
    UNREFERENCED_PARAMETER(pScene);

    DLog(eLogType::Info, "Hello from script!");
  }

};

};
