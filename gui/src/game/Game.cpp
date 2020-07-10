//Corresponding header
#include "game/Game.h"

//C system headers

//C++ system headers
#include <cstdlib>

//Other libraries headers

//Own components headers
#include "game/config/GameConfig.hpp"
#include "utils/Log.h"

int32_t Game::init(const GameConfig &cfg) {
  if (EXIT_SUCCESS != _field.init(cfg.fieldCfg)) {
    LOGERR("Error in _field.init()");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void Game::handleEvent(const InputEvent &e) {
  _field.handleEvent(e);
}

void Game::draw() {
  _field.draw();
}
