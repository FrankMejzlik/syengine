#include "IModuleState.h"

using namespace SYE;

IModuleState::IModuleState() noexcept:
  _state(eModuleState::Null)
{}


IModuleState::~IModuleState() noexcept
{
  _state = eModuleState::Null;
}

void IModuleState::SetModuleState(eModuleState newState)
{
  _state = newState;
}

eModuleState IModuleState::GetModuleState() const
{
  return _state;
}

void IModuleState::PushWarning(eModuleWarning warningId, std::string_view details)
{
  _warnings.push(std::make_pair(warningId, static_cast<std::string>(details)));
}

void IModuleState::PushError(eModuleError errorId, std::string_view details)
{
  _errors.push(std::make_pair(errorId, static_cast<std::string>(details)));
}

void IModuleState::PushCriticalError(eModuleCriticalError criticalErrorId, std::string_view details)
{
  _criticalErrors.push(std::make_pair(criticalErrorId, static_cast<std::string>(details)));
}

std::pair<eModuleWarning, std::string> IModuleState::PollWarning()
{
  assert(!_warnings.empty());

  if (!_warnings.empty())
  {
    auto item = _warnings.front();
    _warnings.pop();

    return item;
  }
  else
  {
    return std::make_pair<eModuleWarning, std::string>(eModuleWarning::kNull, "");
  }
}

std::pair<eModuleError, std::string> IModuleState::PollError()
{
  assert(!_errors.empty());

  if (!_errors.empty())
  {
    auto item = _errors.front();
    _errors.pop();

    return item;
  }
  else
  {
    return std::make_pair<eModuleError, std::string>(eModuleError::kNull, "");
  }
}

std::pair<eModuleCriticalError, std::string> IModuleState::PollCriticallError()
{
  assert(!_criticalErrors.empty());

  if (!_criticalErrors.empty())
  {
    auto item = _criticalErrors.front();
    _criticalErrors.pop();

    return item;
  }
  else
  {
    return std::make_pair<eModuleCriticalError, std::string>(eModuleCriticalError::kNull, "");
  }
}
