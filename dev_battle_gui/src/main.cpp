//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "game_engine/Application.h"
#include "utils/ErrorCode.h"
#include "utils/Log.h"

//Own components headers
#include "dev_battle_gui/config/GuiConfigGenerator.h"
#include "dev_battle_gui/DevBattleGui.h"

static ApplicationConfig generateConfig(int32_t argc, char **args) {
  ApplicationConfig cfg;
  cfg.engineCfg = GuiConfigGenerator::generateEngineConfig();
  cfg.gameCfg = GuiConfigGenerator::generateGameConfig();
  cfg.argc = argc;
  cfg.args = args;
  return cfg;
}

int32_t main(int32_t argc, char **args) {
  std::unique_ptr<Game> game = std::make_unique<DevBattleGui>();
  Application app(std::move(game));

  const auto cfg = generateConfig(argc, args);
  if (SUCCESS != app.init(cfg)) {
    LOGERR("app.init() failed");
    return FAILURE;
  }

  return app.run();
}

