#pragma once

#include <map>

namespace SYE 
{

class BaseModule;

class EngineContext
{
public:
  EngineContext();

  bool ShouldRun() const;
  void SetShouldRun(bool newValue);

  void SetModule(size_t indexKey, BaseModule* pModule);
  BaseModule* GetModule(size_t indexKey) const;

private:
  /** If this Engine instance shoud continue running */
  bool _shouldRun;

  /** Table of active modules of this Engine instance */
  std::map<size_t, BaseModule*> _pModules;

public:
};

} // namespace SYE
