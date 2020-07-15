//Corresponding header
#include "game/field/Field.h"

//C system headers

//C++ system headers
#include <cstdlib>

//Other libraries headers

//Own components headers
#include "game/field/config/FieldConfig.hpp"
#include "utils/Log.h"

static Point getTileCoordinate(const int32_t row, const int32_t col,
                               const int32_t tileWidth,
                               const int32_t tileHeight) {
  const auto rowOffset = row * tileHeight / 4;
  auto colOffset = 0;
  //if row is odd
  if (1 & row) {
    colOffset = tileWidth / 2;
  }

  return Point(colOffset + col * tileWidth, (row * tileHeight) - rowOffset);
}

int32_t Field::init(FieldConfig &cfg) {
  if (0 >= cfg.rows || 0 >= cfg.cols) {
    LOGERR("Invalid configuration, rows: %d, cols: %d. Both 'rows' and 'cols' "
        "needs to be positive number", cfg.rows, cfg.cols);
    return EXIT_FAILURE;
  }

  _tiles.resize(cfg.rows);
  for (int row = 0; row < cfg.rows; ++row) {
    _tiles[row].resize(cfg.cols);
    cfg.tileConfig.row = row;
    for (int col = 0; col < cfg.cols; ++col) {
      //ensure left column, right column and last row have 'whole' rsrc frame
      cfg.tileConfig.tileRsrcId =
          ((row == cfg.rows - 1) || (col == cfg.cols - 1) || (col == 0)) ?
              cfg.tileWholeRsrcId : cfg.tileSurfaceRsrcId;

      cfg.tileConfig.col = col;
      cfg.tileConfig.screenCoordinates =
          getTileCoordinate(row, col, cfg.tileWidth, cfg.tileHeight);
      //apply field offset
      cfg.tileConfig.screenCoordinates.x += cfg.fieldDimensions.x;
      cfg.tileConfig.screenCoordinates.y += cfg.fieldDimensions.y;
      if (EXIT_SUCCESS != _tiles[row][col].init(cfg.tileConfig)) {
        LOGERR("_tiles[%d][%d].init() failed", row, col);
        return EXIT_FAILURE;
      }
    }
  }

  _fieldSB.create(cfg.fieldDimensions);
  updateFieldSpriteBuffer();

  return EXIT_SUCCESS;
}

void Field::handleEvent([[maybe_unused]]const InputEvent &e) {

}

void Field::draw() {
  _fieldSB.draw();
}

void Field::updateFieldSpriteBuffer() {
  _fieldSB.unlock();
  _fieldSB.reset();
  for (auto & row : _tiles) {
    for (auto &tile : row) {
      tile.drawOnSpriteBuffer(_fieldSB);
    }
  }
  _fieldSB.update();
  _fieldSB.lock();
}

