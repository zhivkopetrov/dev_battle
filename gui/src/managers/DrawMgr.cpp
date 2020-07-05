//Corresponding header
#include "managers/DrawMgr.h"

#include <cstdlib>

//Other libraries headers

//Own components headers
#include "utils/Log.h"

DrawMgr *gDrawMgr = nullptr;

DrawMgr::DrawMgr(Renderer *renderer, MonitorWindow *window,
                 const int32_t displayMode, const int32_t monitorWidth,
                 const int32_t monitorHeight)
    : DrawMgrBase(renderer, window, displayMode, monitorWidth, monitorHeight) {
}

int32_t DrawMgr::init() {
  if (EXIT_SUCCESS != DrawMgrBase::init()) {
    LOGERR("Error in DrawMgrBase::init() -> Terminating ...");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int32_t DrawMgr::recover() {
  if (EXIT_SUCCESS != DrawMgrBase::recover()) {
    LOGERR("Error in DrawMgrBase::recover() -> Terminating ...");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
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

