//Corresponding header
#include "managers/TimerMgr.h"

//C system headers

//C++ system headers
#include <cstdlib>

//Other libraries headers

//Own components headers
#include "utils/Log.h"

TimerMgr *gTimerMgr = nullptr;

int32_t TimerMgr::init() {
  if (EXIT_SUCCESS != TimerMgrBase::init()) {
    LOGERR("Error in TimerMgrBase::init() -> Terminating ...");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int32_t TimerMgr::recover() {
  if (EXIT_SUCCESS != TimerMgrBase::recover()) {
    LOGERR("Error in TimerMgrBase::recover() -> Terminating ...");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void TimerMgr::deinit() {
  TimerMgrBase::deinit();
}

void TimerMgr::process() {
  TimerMgrBase::process();
}

void TimerMgr::handleEvent(const InputEvent &e) {
  TimerMgrBase::handleEvent(e);
}

const char* TimerMgr::getName() {
  return "TimerMgr";
}

