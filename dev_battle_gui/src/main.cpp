//System headers
#include <cstdint>

//Other libraries headers
#include "game_engine/Application.h"
#include "utils/ErrorCode.h"
#include "utils/log/Log.h"

//Own components headers
#include "dev_battle_gui/config/GuiConfigGenerator.h"
#include "dev_battle_gui/DevBattleGui.h"

int32_t main(int32_t argc, char **args) {
  Application app;

  const auto dependencies =
      GuiConfigGenerator::generateDependencies(argc, args);
  if (ErrorCode::SUCCESS != app.loadDependencies(dependencies)) {
    LOGERR("app.loadDependencies() failed");
    return EXIT_FAILURE;
  }

  auto game = std::make_unique<DevBattleGui>();
  app.obtain(std::move(game));

  const auto cfg = GuiConfigGenerator::generateConfig();
  if (ErrorCode::SUCCESS != app.init(cfg)) {
    LOGERR("app.init() failed");
    return EXIT_FAILURE;
  }

  if (ErrorCode::SUCCESS != app.run()) {
    LOGERR("app.run() failed");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

