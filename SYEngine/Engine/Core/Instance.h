#pragma once


// If on UNIX-like system
#if unix 

#include <X11/Xlib.h>

#include "common.h"
#include "IUncopyable.h"

namespace SYE 
{

/*!
 * Holding basic information about current appplication instance
 *
 * Things about hardware can be found here.
 */
class InstanceContext
{
public:
  InstanceContext():
		_pDisplay(XOpenDisplay(NULL));
		_pScreen(DefaultScreenOfDisplay(_pDisplay));
  {
    // Extract screen width and height
    _screenWidth = static_cast<size_t>(_pSceen->width);
    _screenHeight = static_cast<size_t>(_pScreen->height);
  }
  ~InstanceContext() {}

  size_t GetScreenWidth() const
  {
    return _screenWidth;
  }
  size_t GetScreenHeight() const
  {
    return _screenHeight;
  }

private:
  //! Holding info about hardware and general info
  Display* _pDisplay;
  Screen* _pSceen;

  //! Hardware active screen width
  size_t _screenWidth;

  //! Hardware active screen height
  size_t _screenHeight;

};


/*!
 * First general to be instantiated class that takes care of the
 * most low level stuff.
 */
class ProcessInstance :
  public IUncopyable
{
public:
  ProcessInstance()
  {
  }


  size_t GetScreenWidth()
  {
    return _instanceContext.GetScreenWidth();
  }

  size_t GetScreenHeight()
  {
    return _instanceContext.GetScreenHeight();
  }

  void Cleanup()
  {}

private:
  //! Instance context
  InstanceContext _instanceContext;

};

}

#endif

#if _WIN32

#include <Windows.h>

#include "common.h"
#include "IUncopyable.h"

namespace SYE 
{

/*!
 * Holding basic information about current appplication instance
 *
 * Things abour hardware can be found here.
 *
 * \todo Make cross-platform.
 */
class InstanceContext
{
public:
  InstanceContext()
  {
    // initialize the DEVMODE structure
    ZeroMemory(&_devMode, sizeof(_devMode));
    _devMode.dmSize = sizeof(_devMode);

    // Try to get info 
    if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &_devMode))
    {
      // Extract screen width and height
      _screenWidth = static_cast<size_t>(_devMode.dmPelsWidth);
      _screenHeight = static_cast<size_t>(_devMode.dmPelsHeight);
    }
  }
  ~InstanceContext() {}

  size_t GetScreenWidth() const
  {
    return _screenWidth;
  }
  size_t GetScreenHeight() const
  {
    return _screenHeight;
  }

private:
  //! Holding info about hardware and general info
  DEVMODE _devMode;

  //! Hardware active screen width
  size_t _screenWidth;

  //! Hardware active screen height
  size_t _screenHeight;

};


/*!
 * First general to be instantiated class that takes care of the
 * most low level stuff.
 */
class ProcessInstance :
  public IUncopyable
{
public:
  ProcessInstance() :
    _hConsole(GetConsoleWindow())
  {
    // If engine running with editor
  #if USING_EDITOR

    // Move console window
    /*MoveWindow(
      _hConsole,
      EDITOR_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT + 20,
      static_cast<int>(_instanceContext.GetScreenWidth() - EDITOR_DEFAULT_WIDTH), 
      static_cast<int>(_instanceContext.GetScreenHeight() - GAME_WINDOW_DEFAULT_HEIGHT - 50),
      TRUE
    );*/

  #else

    // If realease, alpha or beta - hide console window
    #if RELEASE || ALPHA || BETA
        ShowWindow(_hConsole);
    #endif

  #endif
  }


  size_t GetScreenWidth()
  {
    return _instanceContext.GetScreenWidth();
  }

  size_t GetScreenHeight()
  {
    return _instanceContext.GetScreenHeight();
  }

  void Cleanup()
  {}

private:
  //! Handle Windows console
  HWND _hConsole;

  //! Instance context
  InstanceContext _instanceContext;

};

}

#endif
