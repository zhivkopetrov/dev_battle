//Corresponding header
#include "managers/TimerMgr.h"

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

TimerMgr *gTimerMgr = nullptr;

int32_t TimerMgr::init() {
  if (SUCCESS != TimerMgrBase::init()) {
    LOGERR("Error in TimerMgrBase::init() -> Terminating ...");
    return FAILURE;
  }

  return SUCCESS;
}

int32_t TimerMgr::recover() {
  if (SUCCESS != TimerMgrBase::recover()) {
    LOGERR("Error in TimerMgrBase::recover() -> Terminating ...");
    return FAILURE;
  }
  return SUCCESS;
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

