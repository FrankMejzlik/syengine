#pragma once

/**
 * Interface forbidding copying of class.
 *
 * Just inherit from this instance.
 */

namespace WeSp 
{

class IUncopyable
{
public:
  IUncopyable() {}
  IUncopyable(IUncopyable& other) = delete;
  IUncopyable& operator=(const IUncopyable& other) = delete;
};

}