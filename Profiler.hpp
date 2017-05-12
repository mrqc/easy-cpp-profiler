#ifndef __PROFILER_HPP_
#define __PROFILER_HPP_

#include <ctime>
#include <ratio>
#include <chrono>
#include <iostream>
#include <thread>

#define PROF_START_T(block, comment, threshold) \
  std::chrono::high_resolution_clock::time_point __profilerBegin_##block = std::chrono::high_resolution_clock::now(); \
  std::chrono::high_resolution_clock::time_point __profilerLapBegin_##block = std::chrono::high_resolution_clock::now(); \
  bool __profilerLapCalled_##block = false; \
  std::chrono::duration<double> __profilerLapDuration_##block; \
  std::ios __coutStateSaved_##block(nullptr); \
  float __profilerThreshold_##block = threshold; \
  const char* __profilerMessage_##block = comment;

#define PROF_START(block, comment) \
  PROF_START_T(block, comment, 0.5);

#define PROF_PRINT(block, string, width, value) \
  __coutStateSaved_##block.copyfmt(std::cout); \
  std::cout << string << std::setw(width) << __profilerMessage_##block; \
  std::cout.copyfmt(__coutStateSaved_##block); \
  std::cout << " " << std::fixed << value << " SECS\n"; \

#define PROF_LAP(block) \
  __profilerLapDuration_##block = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - __profilerLapBegin_##block); \
  __profilerLapBegin_##block = std::chrono::high_resolution_clock::now(); \
  if (__profilerLapDuration_##block.count() > __profilerThreshold_##block) { \
    PROF_PRINT(block, "PROFILER LAP DURATION", 16, __profilerLapDuration_##block.count()); \
  } \
  __profilerLapCalled_##block = true;

#define PROF_END(block) \
  if (__profilerLapCalled_##block) { \
    PROF_LAP(block); \
  } \
  std::chrono::high_resolution_clock::time_point __profilerEnd_##block = std::chrono::high_resolution_clock::now(); \
  std::chrono::duration<double> __profilerDuration_##block = std::chrono::duration_cast<std::chrono::duration<double>>(__profilerEnd_##block - __profilerBegin_##block); \
  if (__profilerDuration_##block.count() > __profilerThreshold_##block) { \
    PROF_PRINT(block, "PROFILER DURATION", 20, __profilerDuration_##block.count()); \
  } \

#define PROF_DEBUG() \
  std::cout << "(" << std::this_thread::get_id() << ") " << __FILE__ << " : " << __LINE__ << std::endl;

#endif
