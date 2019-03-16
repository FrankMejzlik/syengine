#pragma once

#include "EngineError.h"


#define PUSH_ENGINE_ERROR(type, shortDesc, longDesc)  PushEngineError(type, __FILE__, __LINE__, shortDesc, longDesc); DLog(eLogType::Error, "%s", std::string(shortDesc).c_str())
#define PUSH_EDITOR_ERROR(type, shortDesc, longDesc)  PushEngineError(type, __FILE__, __LINE__, shortDesc, longDesc); DLog(eLogType::Error, "%s", std::string(shortDesc).c_str())

using namespace SYE;

namespace SYE 
{

class IErrorLogging
{
  // Structures
public:
  enum eState
  {
    cError,
    cValid,
    cWarning    
  };

public:
  IErrorLogging();
  virtual ~IErrorLogging() noexcept;

  void PushEngineError(
    eEngineError type, 
    std::string filePath, size_t lineNumber, 
    std::string shortDescription = "", std::string longDescription = ""
  ) const;

  void SetState(eState newState) const
  {
    // Switch through new desired state
    switch (newState)
    {
    case eState::cValid:
      // Valid cannot overwrite error or warning
      if (_currentState != eState::cError &&_currentState != eState::cWarning)
      {
        _currentState = eState::cValid;
      }

      break;

    case eState::cError:
      _currentState = eState::cError;
      break;

    case eState::cWarning:
      // Warning cannot overwrite error
      if (_currentState != eState::cError)
      {
        _currentState = eState::cWarning;
      }

      break;
    }

    _currentState = newState;
  }

  eState GetState() const
  {
    return _currentState;
  }

  EngineError GetLastError() const;
  EngineError GetNextError() const;
  EngineError PopNextError() const;

protected:
  mutable std::queue<EngineError> _engineErrorQueue;
  mutable eState _currentState;
};

}
