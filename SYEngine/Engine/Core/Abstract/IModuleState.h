#pragma once

#include <assert.h>
#include <queue>

#include "config_engine.h"

namespace SYE 
{

enum class eModuleState
{
  Null,
  OK,
  Warning,
  Error,
  CriticalError
};

enum class eModuleWarning
{
  kNull,
  kDuplicateEntries,
};

enum class eModuleError
{
  kNull
};

enum class eModuleCriticalError
{
  kNull
};


/**
 * Interface for every main engine module. Giving it necessary things that modules must have.
 *
 * It gives module state attribute and state getters/setters.
 */
class IModuleState
{
  // Methods.
public:
  IModuleState() noexcept;
  virtual ~IModuleState() noexcept;

protected:
private:


  // Attributes.
public:
protected:
  void SetModuleState(eModuleState newState);
  eModuleState GetModuleState() const;

  void PushWarning(eModuleWarning warningId, std::string_view details);
  void PushError(eModuleError errorId, std::string_view details);
  void PushCriticalError(eModuleCriticalError criticalErrorId, std::string_view details);

  std::pair<eModuleWarning, std::string> PollWarning();
  std::pair<eModuleError, std::string> PollError();
  std::pair<eModuleCriticalError, std::string> PollCriticallError();

private:
  eModuleState _state;
  std::queue< std::pair<eModuleWarning, std::string> > _warnings;
  std::queue< std::pair<eModuleError, std::string> > _errors;
  std::queue< std::pair<eModuleCriticalError, std::string> > _criticalErrors;
};

}

