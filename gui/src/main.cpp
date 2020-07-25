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
#include "utils/ErrorCode.h"
#include "utils/Log.h"

namespace {
//TODO parse the params from config
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
constexpr auto HARDWARE_CONCURRENCY_HINT = 0;
constexpr auto MAX_RESOURCE_LOADING_THREADS = HARDWARE_CONCURRENCY_HINT;

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

//game field tiles
constexpr auto TILE_WIDTH = 78;
constexpr auto TILE_HEIGHT = 64;

//game field
constexpr auto GAME_MODE = GameMode::NORMAL;
constexpr auto GAME_FIELD_ROWS = 15;
constexpr auto GAME_FIELD_COLS = 20;
constexpr auto GAME_FIELD_START_X = 150;
constexpr auto GAME_FIELD_START_Y = 150;
//NOTE: (TILE_WIDTH / 2) and (TILE_HEIGHT / 2) guarantee the tile offset
constexpr auto GAME_FIELD_WIDTH =
    (GAME_FIELD_COLS * TILE_WIDTH) + (TILE_WIDTH / 2);
constexpr auto GAME_FIELD_HEIGHT =
    (GAME_FIELD_ROWS * TILE_HEIGHT) + (TILE_HEIGHT / 2);
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

  cfg.managerHandlerCfg.sdlContainersCfg.maxResourceLoadingThreads =
      MAX_RESOURCE_LOADING_THREADS;
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
  cfg.gameCfg.fieldCfg.fieldDimensions = { GAME_FIELD_START_X,
      GAME_FIELD_START_Y, GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT };
  cfg.gameCfg.fieldCfg.tileWidth = TILE_WIDTH;
  cfg.gameCfg.fieldCfg.tileHeight = TILE_HEIGHT;
  cfg.gameCfg.fieldCfg.tileSurfaceRsrcId = GuiResources::TILE_SURFACE;
  cfg.gameCfg.fieldCfg.tileWholeRsrcId = GuiResources::TILE_WHOLE;
  cfg.gameCfg.fieldCfg.tileTargetRsrcId = GuiResources::TILE_TARGET;
  cfg.gameCfg.fieldCfg.tileConfig.debugFontRsrcId = GuiResources::VINQUE_RG;
}

static int32_t runApplication() {
  Engine engine;

  EngineConfig engineCfg;
  populateConfig(engineCfg);

  if (SUCCESS != engine.init(engineCfg)) {
    LOGERR("Error in engine.init() Terminating ...");
    return FAILURE;
  }
  if (SUCCESS != engine.recover()) {
    LOGERR("Error in engine.recover() Terminating ...");
    return FAILURE;
  }

  return engine.start();
}

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {
  int32_t err = SUCCESS;

  //close default error stream. stdout stream will be used instead
  fclose(stderr);

  //used to measure engine init and total uptime
  Time time;

  //install user defined signal handlers
  SignalHandler::installSignal(SIGSEGV);
  SignalHandler::installSignal(SIGQUIT);

  //open SDL libraries
  if (SUCCESS != SDLLoader::init()) {
    LOGERR("Error in SDLLoader::init() -> Terminating ...");
    return FAILURE;
  } else {
    LOGG("SDLLoader::init() took: %ld ms", time.getElapsed().toMilliseconds());
  }

  /** Use additional method, because we want to explicitly
   * call the engine destructor before main terminates
   * (so proper SDL::deinit() could be called)
   * */
  if (SUCCESS == err) {
    err = runApplication();
    if (SUCCESS != err) {
      LOGERR("Error, runApplication() failed");
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

