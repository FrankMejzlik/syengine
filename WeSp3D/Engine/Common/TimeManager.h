#pragma once

#include <chrono>

class TimeStamp
{
public:
  // Construct timestamp with current time
  TimeStamp():
    _timeStamp(std::chrono::steady_clock::now())
  {}
  // Constructs timestamp with specified time
  // TODO: different construct args: e.g. "12.02.1993"
  //TimeStamp();

  // Returns 
  //float GetSeconds();

private:
  std::chrono::steady_clock::time_point _timeStamp;
};

class TimeManager
{
public:
  TimeManager();
  ~TimeManager();

  //TimeStamp GetNow();

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
  //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;

};

