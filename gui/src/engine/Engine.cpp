//Corresponding header
#include "engine/Engine.h"

//C system headers

//C++ system headers
#include <string>
#include <thread>
#include <chrono>

//Other libraries headers

//Own components headers
#include "engine/config/EngineConfig.hpp"
#include "managers/DrawMgr.h"
#include "managers/RsrcMgr.h"
#include "managers/TimerMgr.h"
#include "utils/ErrorCode.h"
#include "utils/Log.h"

Engine::~Engine() {
  deinit();
}

int32_t Engine::init(EngineConfig &engineCfg) {
  if (SUCCESS != _managerHandler.init(engineCfg.managerHandlerCfg)) {
    LOGERR("Error in _managerHandler.init()");
    return FAILURE;
  }

  if (SUCCESS != _inputEvent.init()) {
    LOGERR("Error in _inputEvent.init()");
    return FAILURE;
  }

  if (SUCCESS != _game.init(engineCfg.gameCfg)) {
    LOGERR("Error in _game.init()");
    return FAILURE;
  }

  if (SUCCESS != _debugConsole.init(
      engineCfg.debugConsoleRsrcId, engineCfg.maxFrameRate)) {
    LOGERR("Error in _debugConsole.init()");
    return FAILURE;
  }

  onInitEnd(engineCfg);

  return SUCCESS;
}

int32_t Engine::recover() {
  return SUCCESS;
}

void Engine::mainLoop() {
  //give some time to the main(rendering thread) to enter it's drawing loop
  using namespace std::literals;
  std::this_thread::sleep_for(1s);
  Time fpsTime;

  while (true) {
    fpsTime.getElapsed(); //begin measure the new frame elapsed time

    if (processFrame()) {
      //user has requested exit -> break the main loop
      gDrawMgrBase->shutdownRenderer();
      return;
    }

    const int64_t elapsedTime = fpsTime.getElapsed().toMicroseconds();
    if (_debugConsole.isActive()) {
      populateDebugConsole(elapsedTime);
    }

#if !ENABLE_VSYNC
    limitFPS(elapsedTime);
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

  return SUCCESS;
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

  if (_debugConsole.isActive()) {
    _debugConsole.draw();
  }

  gDrawMgr->finishFrame();
}

void Engine::handleEvent() {
  _game.handleEvent(_inputEvent);
  _debugConsole.handleEvent(_inputEvent);
}

void Engine::onInitEnd(const EngineConfig &engineCfg) {
  gDrawMgr->setSDLContainers(gRsrcMgr);
  gDrawMgr->setMaxFrameRate(engineCfg.maxFrameRate);
  gTimerMgr->onInitEnd();
}

void Engine::populateDebugConsole(const int64_t elapsedTime) {
  DebugConsoleData debugData;
  debugData.elapsedTime = elapsedTime;
  debugData.activeTimers = gTimerMgr->getActiveTimersCount();
  debugData.activeWidgets = gDrawMgr->getTotalWidgetCount();
  debugData.gpuMemoryUsage = gRsrcMgr->getGPUMemoryUsage();
  _debugConsole.update(debugData);
}

void Engine::limitFPS(const int64_t elapsedTime) {
  const int64_t maxMicosecsPerFrame =
      MILLISECOND / gDrawMgr->getMaxFrameRate();
  const int64_t fpsDelay = maxMicosecsPerFrame - elapsedTime;

  if (0 > fpsDelay) {
    //Sleep the logic thread if max FPS is reached.
    //No need to struggle the CPU.
    std::this_thread::sleep_for(std::chrono::microseconds(fpsDelay));
  }
}

