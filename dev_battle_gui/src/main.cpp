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

int32_t main(int32_t argc, char **args) {
  Application app;

  const auto dependencies =
      GuiConfigGenerator::generateDependencies(argc, args);
  if (SUCCESS != app.loadDependencies(dependencies)) {
    LOGERR("app.loadDependencies() failed");
    return FAILURE;
  }

  auto game = std::make_unique<DevBattleGui>();
  app.obtain(std::move(game));

  const auto cfg = GuiConfigGenerator::generateConfig();
  if (SUCCESS != app.init(cfg)) {
    LOGERR("app.init() failed");
    return FAILURE;
  }

  return app.run();
}

