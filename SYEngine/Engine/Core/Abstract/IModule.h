/**
 * Common interface for engine modules.
 */

#ifndef I_MODULE_H_
#define I_MODULE_H_

#include <map>
#include <memory>

#include "Logger.h"
#include "BaseModule.h"

namespace WeSp 
{

// Forward declarations.
class Engine;

/**
 * Interface for every engine module and submodule that should be standalone 
 * with clear API defined (all public methods are considered as part of API).
 *
 * 1) 
 *  Provides standartized way of instantiating and initializing of submodues for 
 *  simple change of submodules of this module.
 */
class IModule
{
public:
  virtual bool Initialize() = 0;
  virtual bool Terminate() = 0;
  
};

} // namespace WeSp

#endif // #ifndef I_MODULE_H_