//Corresponding header
#include "game/Game.h"

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "game/config/GameConfig.hpp"
#include "utils/ErrorCode.h"
#include "utils/Log.h"

int32_t Game::init(GameConfig &cfg) {
  if (SUCCESS != _field.init(cfg.fieldCfg)) {
    LOGERR("Error in _field.init()");
    return FAILURE;
  }

  return SUCCESS;
}

void Game::handleEvent(const InputEvent &e) {
  _field.handleEvent(e);
}

void Game::draw() {
  _field.draw();
}
