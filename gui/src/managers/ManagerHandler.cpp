//Corresponding header
#include "managers/ManagerHandler.h"

//C system headers

//C++ system headers
#include <cstdlib>

//Other libraries headers

//Own components headers
#include "managers/config/ManagerHandlerConfig.hpp"
#include "managers/DrawMgr.h"
#include "managers/RsrcMgr.h"
#include "managers/TimerMgr.h"
#include "utils/Log.h"

int32_t ManagerHandler::init(const ManagerHandlerConfig &cfg) {
  //gDrawMgr should be initialized first, because it contains the renderer
  //Other managers may want to load graphical resources
  gDrawMgr = new DrawMgr(cfg.drawMgrBaseCfg);
  if (!gDrawMgr) {
    LOGERR("Error! Bad alloc for DrawMgr class -> Terminating...");
    return EXIT_FAILURE;
  }

  gRsrcMgr = new RsrcMgr(cfg.sdlContainersCfg);
  if (!gRsrcMgr) {
    LOGERR("Error! Bad alloc for RsrcMgr class -> Terminating...");
    return EXIT_FAILURE;
  }

  gTimerMgr = new TimerMgr;
  if (!gTimerMgr) {
    LOGERR("Error! Bad alloc for TimerMgr class -> Terminating...");
    return EXIT_FAILURE;
  }

  //put global managers into container so they can be easily iterated
  //and used polymorphically
  _managers[Managers::DRAW_MGR_IDX] = gDrawMgr;
  _managers[Managers::RSRC_MGR_IDX] = gRsrcMgr;
  _managers[Managers::TIMER_MGR_IDX] = gTimerMgr;

  Time initTime;
  for (int32_t i = 0; i < Managers::TOTAL_MGRS_COUNT; ++i) {
    if (EXIT_SUCCESS != _managers[i]->init()) {
      LOGERR("Error in %s init() -> Terminating...", _managers[i]->getName());
      return EXIT_FAILURE;
    }

    LOGG("%s init() passed successfully for %ld ms", _managers[i]->getName(),
        initTime.getElapsed().toMilliseconds());
  }

  return EXIT_SUCCESS;
}

void ManagerHandler::deinit() {
  /** Following the logic that DrawMgr should be initialized first ->
   * it should be deinitialized last
   * / a.k.a. last one to shut the door :) /
   * */
  for (int32_t i = Managers::TOTAL_MGRS_COUNT - 1; i >= 0; --i) {
    if (_managers[i]) //Sanity check
    {
      _managers[i]->deinit();

      delete _managers[i];
      _managers[i] = nullptr;

      nullifyGlobalManager(i);
    }
  }
}

void ManagerHandler::process() {
  for (int32_t i = 0; i < Managers::TOTAL_MGRS_COUNT; ++i) {
    _managers[i]->process();
  }
}

void ManagerHandler::nullifyGlobalManager(const int32_t managerId) {
  /** Explicitly set the singleton pointer to nullptr, because someone might
   * still try to use them -> if so, the sanity checks should catch them
   * */
  switch (managerId) {
  case Managers::DRAW_MGR_IDX:
    gDrawMgr = nullptr;
    break;

  case Managers::RSRC_MGR_IDX:
    gRsrcMgr = nullptr;
    break;

  case Managers::TIMER_MGR_IDX:
    gTimerMgr = nullptr;
    break;

  default:
    LOGERR("Unknown managerId: %d provided", managerId);
    break;
  }
}

