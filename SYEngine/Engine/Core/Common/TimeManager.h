#pragma once

// TODO: Implement

#include <chrono>

class TimeStamp
{
public:
  // Construct timestamp with current time
  TimeStamp():
    _timeStamp(std::chrono::steady_clock::now())
  {}


private:
  std::chrono::steady_clock::time_point _timeStamp;
};
 
class TimeManager
{
public:
  TimeManager();
  ~TimeManager();


  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

};

