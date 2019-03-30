#pragma once


#include "common.h"

namespace SYE
{

class IGuidCounted
{
public:
  IGuidCounted() :
    _guid(_nextGuid)
  {
    // Increment counters.
    ++_nextGuid;
    ++_totalCount;
  }
  ~IGuidCounted()
  {
    --_totalCount;
  }
  size_t GetGuid() const { return _guid; }
  size_t GetTotalCount() const { return _totalCount; }

private:
  // TODO: Check overflow
  static size_t _nextGuid;
  static size_t _totalCount;

  // Global unique ID through whole engine.
  size_t _guid;
};

};
