//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "game_engine/Application.h"
#include "resource_utils/common/ResourceFileHeader.h"
#include "utils/file_system/FileSystemUtils.h"
#include "utils/ErrorCode.h"
#include "utils/Log.h"

//Own components headers
#include "Gui.h"
#include "config/GuiConfig.h"
#include "resources/GuiResources.h"

namespace {
//TODO parse the params from config
constexpr auto windowDisplayMode = WindowDisplayMode::FULL_SCREEN;
constexpr auto windowBorderMode = WindowBorderMode::BORDERLESS;
constexpr auto MONITOR_WIDTH = 1920;
constexpr auto MONITOR_HEIGHT = 1080;
constexpr auto MAX_FRAME_RATE = 75;
constexpr auto PROJECT_NAME = "gui";
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

static EngineConfig populateEngineConfig() {
  EngineConfig cfg;

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
      PROJECT_NAME).append("/").append(
          ResourceFileHeader::getResourcesBinFolderName()).append("/");

  cfg.managerHandlerCfg.sdlContainersCfg.loadingScreenCfg.loadingScreenUsage =
      LoadingScreenUsage::ENABLED;
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

  return cfg;
}

static GuiConfig populateGuiConfig() {
  GuiConfig cfg;

  cfg.gameMode = GAME_MODE;
  cfg.fieldCfg.rows = GAME_FIELD_ROWS;
  cfg.fieldCfg.cols = GAME_FIELD_COLS;
  cfg.fieldCfg.fieldDimensions = { GAME_FIELD_START_X,
      GAME_FIELD_START_Y, GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT };
  cfg.fieldCfg.tileWidth = TILE_WIDTH;
  cfg.fieldCfg.tileHeight = TILE_HEIGHT;
  cfg.fieldCfg.tileSurfaceRsrcId = GuiResources::TILE_SURFACE;
  cfg.fieldCfg.tileWholeRsrcId = GuiResources::TILE_WHOLE;
  cfg.fieldCfg.tileTargetRsrcId = GuiResources::TILE_TARGET;
  cfg.fieldCfg.debugFontRsrcId = GuiResources::VINQUE_RG;

  return cfg;
}

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {
  const auto engineCfg = populateEngineConfig();
  const auto guiCfg = populateGuiConfig();

  std::unique_ptr<Game> game = std::make_unique<Gui>();
  Application app(std::move(game));
  if (SUCCESS != app.init(engineCfg, guiCfg)) {
    LOGERR("app.init() failed");
    return FAILURE;
  }

  return app.run();
}

