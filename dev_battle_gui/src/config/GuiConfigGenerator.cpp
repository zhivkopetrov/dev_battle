//Corresponding header
#include "dev_battle_gui/config/GuiConfigGenerator.h"

//System headers

//Other libraries headers
#include "resource_utils/common/ResourceFileHeader.h"
#include "utils/file_system/FileSystemUtils.h"

//Own components headers
#include "generated/DevBattleGuiResources.h"
#include "dev_battle_gui/config/GuiIniConfigParser.h"
#include "utils/log/Log.h"

namespace {
constexpr auto PROJECT_NAME = "dev_battle_gui";
constexpr auto LOADING_SCREEN_RESOURCES_PATH = "p/loading_screen/";
constexpr auto CONFIG_FILE_NAME = "config.ini";

//TODO parse the params from config
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

EngineConfig generateEngineConfig(
  const std::string binaryInstallPrefix, const GuiIniConfig& guiCfg) {
  auto cfg = getDefaultEngineConfig(
    binaryInstallPrefix, LOADING_SCREEN_RESOURCES_PATH);
  cfg.debugConsoleConfig.fontRsrcId = DevBattleGuiResources::VINQUE_RG;

  // Monitor/Screen config
  DrawMgrConfig& drawMgrCfg = cfg.managerHandlerCfg.drawMgrCfg;
  MonitorWindowConfig& monitorCfg = drawMgrCfg.monitorWindowConfig;
  const GuiIniConfig::Window& parsedWindowCfg = guiCfg.windowCfg;
  monitorCfg.name = parsedWindowCfg.name;
  monitorCfg.displayMode = parsedWindowCfg.windowDisplayMode;
  monitorCfg.borderMode = parsedWindowCfg.windowBorderMode;
  monitorCfg.pos = Point(parsedWindowCfg.windowRect.x, parsedWindowCfg.windowRect.y);
  monitorCfg.width = parsedWindowCfg.windowRect.w;
  monitorCfg.height = parsedWindowCfg.windowRect.h;

  // Renderer config
  RendererConfig& rendererCfg = drawMgrCfg.rendererConfig;
  const GuiIniConfig::Renderer& parsedRendererCfg = guiCfg.rendererCfg;
  rendererCfg.flagsMask = parsedRendererCfg.flagsMask;
  rendererCfg.executionPolicy = parsedRendererCfg.executinPolicy;
  rendererCfg.scaleQuality = parsedRendererCfg.scaleQuality;

  // Resource loading threads are strictly not directly tied to the renderer.
  // For simplicity - hide that detail from the end user.
  cfg.managerHandlerCfg.sdlContainersCfg.maxResourceLoadingThreads =
    parsedRendererCfg.resourceLoadingThreadsNum;

  // Engine config
  const GuiIniConfig::Engine& parsedEngineCfg = guiCfg.engineCfg;
  cfg.maxFrameRate = parsedEngineCfg.targetFps;
  cfg.inputEventHandlerPolicy = parsedEngineCfg.inputEventHandlerPolicy;
  cfg.actionEventHandlerPolicy = parsedEngineCfg.actionEventHandlerPolicy;

  return cfg;
}

GuiConfig generateGameConfig() {
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

} // end anonymous namespace

std::vector<DependencyDescription> GuiConfigGenerator::generateDependencies(
    int32_t argc, char **args) {
  std::vector<DependencyDescription> dependecies =
      getDefaultEngineDependencies(argc, args);

  return dependecies;
}

std::pair<ApplicationConfig, ErrorCode> GuiConfigGenerator::generateConfig() {
  // defined in dev_battle_gui CMakeLists.txt
  const std::string projectInstallPrefix = PROJECT_INSTALL_PREFIX;
  const std::string binaryInstallPrefix =
      projectInstallPrefix + "/" + PROJECT_NAME;
  const std::string iniCfgPath = binaryInstallPrefix + "/" + CONFIG_FILE_NAME;

  GuiIniConfig iniCfg;
  if (ErrorCode::SUCCESS != parseConfig(iniCfgPath, iniCfg)) {
    LOGERR("parseConfig() failed");
    return {{}, ErrorCode::FAILURE};
  }

  ApplicationConfig cfg;
  cfg.engineCfg = generateEngineConfig(binaryInstallPrefix, iniCfg);
  cfg.gameCfg = generateGameConfig();
  return {cfg, ErrorCode::SUCCESS};
}
