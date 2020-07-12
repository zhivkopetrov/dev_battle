//Corresponding header
#include "engine/Engine.h"

//C system headers
#include <unistd.h>

//C++ system headers
#include <cstdlib>
#include <string>
#include <thread>

//Other libraries headers

//Own components headers
#include "engine/config/EngineConfig.hpp"
#include "managers/DrawMgr.h"
#include "managers/RsrcMgr.h"
#include "managers/TimerMgr.h"
#include "utils/Log.h"

Engine::~Engine() {
  deinit();
}

int32_t Engine::init(EngineConfig &engineCfg) {
  if (EXIT_SUCCESS != _managerHandler.init(engineCfg.managerHandlerCfg)) {
    LOGERR("Error in _managerHandler.init()");
    return EXIT_FAILURE;
  }

  if (EXIT_SUCCESS != _inputEvent.init()) {
    LOGERR("Error in _inputEvent.init()");
    return EXIT_FAILURE;
  }

  if (EXIT_SUCCESS != _game.init(engineCfg.gameCfg)) {
    LOGERR("Error in _game.init()");
    return EXIT_FAILURE;
  }

  onInitEnd(engineCfg);

  return EXIT_SUCCESS;
}

int32_t Engine::recover() {
  return EXIT_SUCCESS;
}

void Engine::mainLoop() {
  //give some time to the main(rendering thread) to enter it's drawing loop
  usleep(1000); //1ms

  Time fpsTime;
  uint32_t fpsDelay = 0;

  while (true) {
    //begin measure the new frame elapsed time
    fpsTime.getElapsed();

    if (processFrame()) {
      //user has requested exit -> break the main loop
      gDrawMgrBase->shutdownRenderer();
      return;
    }

#if !ENABLE_VSYNC
    fpsDelay = static_cast<uint32_t>(fpsTime.getElapsed().toMicroseconds());

    const uint32_t MAX_MICROSECONDS_PER_FRAME = MILLISECOND
        / gDrawMgr->getMaxFrameRate();
    MAX_MICROSECONDS_PER_FRAME < fpsDelay ?
        fpsDelay = 0 : fpsDelay = MAX_MICROSECONDS_PER_FRAME - fpsDelay;

    //Sleep the logic thread if max FPS is reached.
    //No need to struggle the CPU.
    usleep(fpsDelay);
#endif //!ENABLE_VSYNC
  }
}

void Engine::deinit() {
  _managerHandler.deinit();
  _inputEvent.deinit();
}

int32_t Engine::start() {
  std::thread engineThread = std::thread(&Engine::mainLoop, this);

  //enter rendering loop
  gDrawMgr->startRenderingLoop();

  //sanity check
  if (engineThread.joinable()) {
    engineThread.join();
  }

  return EXIT_SUCCESS;
}

bool Engine::processFrame() {
  _managerHandler.process();

  while (_inputEvent.pollEvent()) {
    if (_inputEvent.checkForExitRequest()) {
      return true;
    }

    handleEvent();
  }

  drawFrame();

  return false;
}

void Engine::drawFrame() {
  gDrawMgr->clearScreen();

  _game.draw();

  gDrawMgr->finishFrame();
}

void Engine::handleEvent() {
  _game.handleEvent(_inputEvent);
}

void Engine::onInitEnd(const EngineConfig &engineCfg) {
  gDrawMgr->setSDLContainers(gRsrcMgr);
  gDrawMgr->setMaxFrameRate(engineCfg.maxFrameRate);
  gTimerMgr->onInitEnd();
}

