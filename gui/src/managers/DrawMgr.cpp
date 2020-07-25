//Corresponding header
#include "managers/DrawMgr.h"

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

DrawMgr *gDrawMgr = nullptr;

DrawMgr::DrawMgr(const DrawMgrBaseConfig &cfg) : DrawMgrBase(cfg) {
}

int32_t DrawMgr::init() {
  if (SUCCESS != DrawMgrBase::init()) {
    LOGERR("Error in DrawMgrBase::init() -> Terminating ...");
    return FAILURE;
  }

  return SUCCESS;
}

int32_t DrawMgr::recover() {
  if (SUCCESS != DrawMgrBase::recover()) {
    LOGERR("Error in DrawMgrBase::recover() -> Terminating ...");
    return FAILURE;
  }

  return SUCCESS;
}

void DrawMgr::deinit() {
  DrawMgrBase::deinit();
}

void DrawMgr::process() {
  DrawMgrBase::process();
}

void DrawMgr::handleEvent(const InputEvent &e) {
  DrawMgrBase::handleEvent(e);
}

const char* DrawMgr::getName() {
  return "DrawMgr";
}

