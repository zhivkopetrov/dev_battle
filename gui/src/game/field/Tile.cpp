//Corresponding header
#include "game/field/Tile.h"

//C system headers

//C++ system headers
#include <cstdlib>
#include <string>

//Other libraries headers

//Own components headers
#include "game/field/config/TileConfig.hpp"

namespace {
constexpr auto TILE_WIDTH = 78;
constexpr auto TILE_HEIGHT = 64;
constexpr auto BASE_OFFSET = 150;
constexpr auto DEBUG_TEXT_OFFSET_X = 1;
constexpr auto DEBUG_TEXT_OFFSET_Y = 13;
}

static Point getTileCoordinates(const int row, const int col) {
  const auto rowOffset = row * TILE_HEIGHT / 4;
  auto colOffset = 0;
  //if row is odd
  if (1 & row) {
    colOffset = TILE_WIDTH / 2;
  }

  return Point(BASE_OFFSET + colOffset + col * TILE_WIDTH,
      BASE_OFFSET - rowOffset + row * TILE_HEIGHT);
}

int32_t Tile::init(const TileConfig &cfg) {
  _tileImg.create(cfg.tileRsrcId);
  const auto tilePos = getTileCoordinates(cfg.row, cfg.col);
  _tileImg.setPosition(tilePos);

  std::string debugText;
  debugText.reserve(8); //max debug string size
  debugText.append("[").append(std::to_string(cfg.row)).append(",").append(
      std::to_string(cfg.col)).append("]");
  _debugText.create(cfg.debugFontRsrcId, debugText.c_str(), Colors::RED,
      Point(tilePos.x + DEBUG_TEXT_OFFSET_X, tilePos.y + DEBUG_TEXT_OFFSET_Y));

  static int frame = 0;
  _tileImg.setFrame(frame++ % 4);

  return EXIT_SUCCESS;
}

void Tile::draw() {
  _tileImg.draw();
  _debugText.draw();
}

