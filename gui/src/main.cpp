//C system headers

//C++ system headers
#include <cstdint>
#include <thread>

//Other libraries headers
#include "sdl_utils/SDLLoader.h"
#include "sdl_utils/drawing/MonitorWindow.h"
#include "sdl_utils/drawing/Renderer.h"

//Own components headers
#include "engine/Engine.h"
#include "engine/EngineConfig.hpp"

#include "utils/time/Time.h"
#include "utils/debug/SignalHandler.h"
#include "utils/Log.h"

namespace {
constexpr auto MONITOR_WIDTH = 1920;
constexpr auto MONITOR_HEIGHT = 1080;
constexpr auto MAX_FRAME_RATE = 60;
constexpr auto PROJECT_NAME = "dev_battle_gui";
constexpr bool ALLOW_MULTITHREAD_RES_LOADING = true;
}


static void parseConfig(EngineConfig &cfg) {
  cfg.monitorWidth = MONITOR_WIDTH;
  cfg.monitorWidth = MONITOR_HEIGHT;
  cfg.displayMode = FULL_SCREEN_MODE;
  cfg.maxFrameRate = MAX_FRAME_RATE;
  cfg.projectName = PROJECT_NAME;
  cfg.isMultithreadResAllowed = ALLOW_MULTITHREAD_RES_LOADING;
}

static int32_t runApplication() {
  int32_t err = EXIT_SUCCESS;

  EngineConfig engineCfg;
  parseConfig(engineCfg);

  MonitorWindow mainWindow(engineCfg.monitorWidth, engineCfg.monitorHeight);
  Renderer renderer;
  Engine engine;

  if (EXIT_SUCCESS == err) {
    engineCfg.renderer = &renderer;
    engineCfg.window = &mainWindow;
    if (EXIT_SUCCESS != mainWindow.init(engineCfg.displayMode)) {
      LOGERR("Error, mainWindow.init() failed");
      return EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    if (EXIT_SUCCESS != renderer.init(mainWindow.getWindow())) {
      LOGERR("Error, renderer.init() failed");
      return EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    if (EXIT_SUCCESS != engine.init(engineCfg)) {
      LOGERR("Error in engine.init() Terminating ...");
      return EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    if (EXIT_SUCCESS != engine.recover()) {
      LOGERR("Error in engine.recover() Terminating ...");
      return EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    std::thread engineThread = std::thread(&Engine::start, &engine);

    //enter rendering loop
    renderer.executeRenderCommands_RT();

    //sanity check
    if (engineThread.joinable()) {
      engineThread.join();
    }

    engine.deinit();
    renderer.deinit();
    mainWindow.deinit();
  }

  return err;
}

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {
  int32_t err = EXIT_SUCCESS;

  //close default error stream. stdout stream will be used instead
  fclose(stderr);

  //used to measure engine init and total uptime
  Time time;

  //install user defined signal handlers
  SignalHandler::installSignal(SIGSEGV);
  SignalHandler::installSignal(SIGQUIT);

  //open SDL libraries
  if (EXIT_SUCCESS != SDLLoader::init()) {
    LOGERR("Error in SDLLoader::init() -> Terminating ...");
    err = EXIT_FAILURE;
  } else {
    LOGG("SDLLoader::init() took: %ld ms", time.getElapsed().toMilliseconds());
  }

  /** Use additional method, because we want to explicitly
   * call the engine destructor before main terminates
   * (so proper SDL::deinit() could be called)
   * */
  if (EXIT_SUCCESS == err) {
    if (EXIT_SUCCESS != runApplication()) {
      LOGERR("Error, runApplication() failed");

      err = EXIT_FAILURE;
    }
  }

  //close SDL libraries
  SDLLoader::deinit();

  const auto upTimeSeconds = time.getElapsedFromStart().toSeconds();

  LOGG("Total engine uptime: Hours: %ld, Minutes: %ld, Seconds: %ld",
       upTimeSeconds / 3600, upTimeSeconds / 60, upTimeSeconds);

  return err;
}

