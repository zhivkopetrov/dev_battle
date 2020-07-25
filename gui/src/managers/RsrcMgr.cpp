//Corresponding header
#include "managers/RsrcMgr.h"

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

RsrcMgr *gRsrcMgr = nullptr;

RsrcMgr::RsrcMgr(const SDLContainersConfig &cfg) : RsrcMgrBase(cfg) {
}

int32_t RsrcMgr::init() {
  if (SUCCESS != RsrcMgrBase::init()) {
    LOGERR("Error in RsrcMgr::init() -> Terminating ...");
    return FAILURE;
  }

  return SUCCESS;
}

int32_t RsrcMgr::recover() {
  int32_t err = SUCCESS;

  if (SUCCESS != RsrcMgrBase::recover()) {
    LOGERR("Error in RsrcMgr::recover() -> Terminating ...");

    err = FAILURE;
  }

  return err;
}

void RsrcMgr::deinit() {
  RsrcMgrBase::deinit();
}

const char* RsrcMgr::getName() {
  return "RsrcMgr";
}

void RsrcMgr::process() {

}

void RsrcMgr::handleEvent(const InputEvent &e) {
  RsrcMgrBase::handleEvent(e);
}

void RsrcMgr::onLoadTextureMultipleCompleted(
    [[maybe_unused]]const int32_t batchId) {
  //TODO populate me when needed
}

