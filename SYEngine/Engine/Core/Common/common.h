/**
 * Common includes that are required in almost every header file.
 */


#ifndef COMMON_H_
#define COMMON_H_

#include <memory>
#include <stddef.h>
#include <string>

#include "macros.h"
#include "Logger.h"
#include "typedefs.h"
#include "assert.h"
#include "config_engine.h"
#include "config_components.h"


enum class eWindowType
{
  MAIN_GAME_WINDOW,
  COUNT
};



#endif // #ifndef COMMON_H_
