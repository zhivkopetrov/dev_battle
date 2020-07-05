//Corresponding header
#include "managers/RsrcMgr.h"

//C system headers

//C++ system headers
#include <cstdlib>

//Other libraries headers

//Own components headers
#include "utils/Log.h"

RsrcMgr *gRsrcMgr = nullptr;

RsrcMgr::RsrcMgr(Renderer *renderer, const std::string &projectName,
                 const bool isMultithreadResAllowed)
    : RsrcMgrBase(renderer, projectName, isMultithreadResAllowed) {
}

int32_t RsrcMgr::init() {
  if (EXIT_SUCCESS != RsrcMgrBase::init()) {
    LOGERR("Error in RsrcMgr::init() -> Terminating ...");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int32_t RsrcMgr::recover() {
  int32_t err = EXIT_SUCCESS;

  if (EXIT_SUCCESS != RsrcMgrBase::recover()) {
    LOGERR("Error in RsrcMgr::recover() -> Terminating ...");

    err = EXIT_FAILURE;
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

