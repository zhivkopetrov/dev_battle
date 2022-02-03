//Corresponding header
#include "dev_battle_gui/config/GuiConfigGenerator.h"

//C system headers

//C++ system headers

//Other libraries headers
#include "resource_utils/common/ResourceFileHeader.h"
#include "utils/file_system/FileSystemUtils.h"

//Own components headers
#include "generated/DevBattleGuiResources.h"

namespace {
//TODO parse the params from config
constexpr auto PROJECT_FOLDER_NAME = "dev_battle_gui";
constexpr auto LOADING_SCREEN_RESOURCES_PATH = "p/loading_screen/";

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

EngineConfig GuiConfigGenerator::generateEngineConfig() {
  const auto projectInstallPrefix =
      FileSystemUtils::getCurrentWorkingDirectory() + "/" + PROJECT_FOLDER_NAME;
  auto cfg = getDefaultEngineConfig(
      projectInstallPrefix, LOADING_SCREEN_RESOURCES_PATH);

  cfg.debugConsoleRsrcId = DevBattleGuiResources::VINQUE_RG;

  return cfg;
}

GuiConfig GuiConfigGenerator::generateGameConfig() {
  GuiConfig cfg;

  cfg.gameMode = GAME_MODE;
  cfg.fieldCfg.rows = GAME_FIELD_ROWS;
  cfg.fieldCfg.cols = GAME_FIELD_COLS;
  cfg.fieldCfg.fieldDimensions = { GAME_FIELD_START_X,
      GAME_FIELD_START_Y, GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT };
  cfg.fieldCfg.tileWidth = TILE_WIDTH;
  cfg.fieldCfg.tileHeight = TILE_HEIGHT;
  cfg.fieldCfg.tileSurfaceRsrcId = DevBattleGuiResources::TILE_SURFACE;
  cfg.fieldCfg.tileWholeRsrcId = DevBattleGuiResources::TILE_WHOLE;
  cfg.fieldCfg.tileTargetRsrcId = DevBattleGuiResources::TILE_TARGET;
  cfg.fieldCfg.debugFontRsrcId = DevBattleGuiResources::VINQUE_RG;

  return cfg;
}

