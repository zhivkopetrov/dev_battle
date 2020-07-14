//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "sdl_utils/SDLLoader.h"
#include "sdl_utils/drawing/MonitorWindow.h"
#include "sdl_utils/drawing/Renderer.h"

//Own components headers
#include "engine/Engine.h"
#include "engine/config/EngineConfig.hpp"
#include "resources/GuiResources.h"

#include "utils/time/Time.h"
#include "utils/file_system/FileSystemUtils.h"
#include "resource_utils/common/ResourceFileHeader.h"
#include "utils/debug/SignalHandler.h"
#include "utils/Log.h"

namespace {
//TODO parse the params from config

//TODO add a param for resource loading threads. if 0 is provided - hardware_concurency is used
constexpr auto windowDisplayMode = WindowDisplayMode::FULL_SCREEN;
constexpr auto windowBorderMode = WindowBorderMode::BORDERLESS;
constexpr auto MONITOR_WIDTH = 1920;
constexpr auto MONITOR_HEIGHT = 1080;
#if ENABLE_VSYNC
constexpr auto MAX_FRAME_RATE = 300;
#else
constexpr auto MAX_FRAME_RATE = 60;
#endif //ENABLE_VSYNC
constexpr auto ROOT_PROJECT_NAME = "dev_battle";
constexpr auto LOADING_SCREEN_RELATIVE_TO_ROOT_PATH =
    "gui/include/resources/p/loading_screen/";
constexpr auto ALLOW_MULTITHREAD_RES_LOADING = true;

constexpr auto MAX_RUNTIME_TEXTS = 400;
constexpr auto MAX_RUNTIME_SPRITE_BUFFERS = 50;
constexpr auto MAX_RUNTIME_IMAGES = 200;
constexpr auto MAX_RUNTIME_WIDGETS =  MAX_RUNTIME_TEXTS +
    MAX_RUNTIME_SPRITE_BUFFERS + MAX_RUNTIME_IMAGES;
constexpr auto MAX_RUNTIME_RENDERER_COMMANDS =
    MAX_RUNTIME_WIDGETS * 2;
//65k bytes
constexpr auto MAX_RENDERER_BACK_BUFFER_DATA_SIZE =
    std::numeric_limits<uint16_t>::max();

constexpr auto GAME_MODE = GameMode::NORMAL;
constexpr auto GAME_FIELD_ROWS = 15;
constexpr auto GAME_FIELD_COLS = 20;
}


static void populateConfig(EngineConfig &cfg) {
  cfg.maxFrameRate = MAX_FRAME_RATE;
  cfg.debugConsoleRsrcId = GuiResources::VINQUE_RG;

  cfg.managerHandlerCfg.drawMgrBaseCfg.rendererConfig.
    maxRuntimeRendererCommands = MAX_RUNTIME_RENDERER_COMMANDS;
  cfg.managerHandlerCfg.drawMgrBaseCfg.rendererConfig.maxRuntimeWidgets =
      MAX_RUNTIME_WIDGETS;
  cfg.managerHandlerCfg.drawMgrBaseCfg.rendererConfig.
    maxRendererBackBufferDataSize = MAX_RENDERER_BACK_BUFFER_DATA_SIZE;

  cfg.managerHandlerCfg.drawMgrBaseCfg.monitorWidth = MONITOR_WIDTH;
  cfg.managerHandlerCfg.drawMgrBaseCfg.monitorHeight = MONITOR_HEIGHT;
  cfg.managerHandlerCfg.drawMgrBaseCfg.windowDisplayMode = windowDisplayMode;
  cfg.managerHandlerCfg.drawMgrBaseCfg.windowBorderMode = windowBorderMode;

  cfg.managerHandlerCfg.sdlContainersCfg.isMultithreadResAllowed =
      ALLOW_MULTITHREAD_RES_LOADING;
  cfg.managerHandlerCfg.sdlContainersCfg.maxRuntimeSpriteBuffers =
      MAX_RUNTIME_SPRITE_BUFFERS;
  cfg.managerHandlerCfg.sdlContainersCfg.maxRuntimeTexts =
      MAX_RUNTIME_TEXTS;
  cfg.managerHandlerCfg.sdlContainersCfg.resourcesBinLocation =
      FileSystemUtils::getBuildDirectory();
  cfg.managerHandlerCfg.sdlContainersCfg.resourcesBinLocation.append(
      ROOT_PROJECT_NAME).append("/").append(
          ResourceFileHeader::getResourcesBinFolderName()).append("/");

  cfg.managerHandlerCfg.sdlContainersCfg.loadingScreenCfg.monitorWidth =
      MONITOR_WIDTH;
  cfg.managerHandlerCfg.sdlContainersCfg.loadingScreenCfg.monitorHeight =
      MONITOR_HEIGHT;
  const std::string loadingScreenFolderPath =
     FileSystemUtils::getRootDirectory() + LOADING_SCREEN_RELATIVE_TO_ROOT_PATH;
  cfg.managerHandlerCfg.sdlContainersCfg.loadingScreenCfg.backgroundImagePath =
      loadingScreenFolderPath + "background.png";
  cfg.managerHandlerCfg.sdlContainersCfg.loadingScreenCfg.
    progressBarOnImagePath = loadingScreenFolderPath + "progressOn.png";
  cfg.managerHandlerCfg.sdlContainersCfg.loadingScreenCfg.
    progressBarOffImagePath = loadingScreenFolderPath + "progressOff.png";

  cfg.gameCfg.gameMode = GAME_MODE;
  cfg.gameCfg.fieldCfg.rows = GAME_FIELD_ROWS;
  cfg.gameCfg.fieldCfg.cols = GAME_FIELD_COLS;
  cfg.gameCfg.fieldCfg.tileSurfaceRsrcId = GuiResources::TILE_SURFACE;
  cfg.gameCfg.fieldCfg.tileWholeRsrcId = GuiResources::TILE_WHOLE;
  cfg.gameCfg.fieldCfg.tileTargetRsrcId = GuiResources::TILE_TARGET;
  cfg.gameCfg.fieldCfg.tileConfig.debugFontRsrcId = GuiResources::VINQUE_RG;
}

static int32_t runApplication() {
  Engine engine;

  EngineConfig engineCfg;
  populateConfig(engineCfg);

  if (EXIT_SUCCESS != engine.init(engineCfg)) {
    LOGERR("Error in engine.init() Terminating ...");
    return EXIT_FAILURE;
  }
  if (EXIT_SUCCESS != engine.recover()) {
    LOGERR("Error in engine.recover() Terminating ...");
    return EXIT_FAILURE;
  }

  return engine.start();
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

  LOGG("Exit error code: %d, Total engine uptime: "
      "Hours: %ld, Minutes: %ld, Seconds: %ld",
      err, upTimeSeconds / 3600, upTimeSeconds / 60, upTimeSeconds);

  return err;
}

