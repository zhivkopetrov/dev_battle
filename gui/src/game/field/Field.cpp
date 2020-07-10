//Corresponding header
#include "game/field/Field.h"

//C system headers

//C++ system headers
#include <cstdlib>

//Other libraries headers

//Own components headers
#include "game/field/config/FieldConfig.hpp"
#include "resources/GuiResources.h"
#include "utils/Log.h"

static Point getTileCoordinates(const int row, const int col) {
  //TODO fix me
  constexpr auto TILE_WIDTH = 78;
  constexpr auto TILE_HEIGHT = 64;
  constexpr auto BASE_OFFSET = 100;

  return Point(BASE_OFFSET + row * TILE_WIDTH, BASE_OFFSET + col * TILE_HEIGHT);
}

int32_t Field::init(const FieldConfig &cfg) {
  _tiles.resize(cfg.tileRows);
  for (int row = 0; row < cfg.tileRows; ++row) {
    _tiles[row].resize(cfg.tileCols);
    for (int col = 0; col < cfg.tileCols; ++col) {
      _tiles[row][col].create(GuiResources::TILE_SURFACE);
      _tiles[row][col].setPosition(getTileCoordinates(row, col));
    }
  }

  return EXIT_SUCCESS;
}

void Field::handleEvent([[maybe_unused]]const InputEvent &e) {

}

void Field::draw() {
  //TODO draw on sprite buffer

  for (auto & row : _tiles) {
    for (auto &tile : row) {
      tile.draw();
    }
  }
}

