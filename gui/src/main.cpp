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
constexpr auto PROJECT_FOLDER_NAME = "gui";
constexpr auto LOADING_SCREEN_RESOURCES_PATH =
    "gui/include/resources/p/loading_screen/";

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
  auto cfg = getDefaultEngineConfig(
      PROJECT_FOLDER_NAME, LOADING_SCREEN_RESOURCES_PATH);
  cfg.debugConsoleRsrcId = GuiResources::VINQUE_RG;

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

#include <iostream>

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

