//Corresponding header
#include "game/field/Field.h"

//C system headers

//C++ system headers
#include <cstdlib>

//Other libraries headers

//Own components headers
#include "game/field/config/FieldConfig.hpp"
#include "utils/Log.h"

int32_t Field::init(FieldConfig &cfg) {
  if (0 >= cfg.rows || 0 >= cfg.cols) {
    LOGERR("Invalid configuration, rows: %d, cols: %d. Both 'rows' and 'cols' "
        "needs to be positive number", cfg.rows, cfg.cols);
    return EXIT_FAILURE;
  }

  _tiles.resize(cfg.rows);
  cfg.tileConfig.tileRsrcId = cfg.tileSurfaceRsrcId;
  const int surfaceOnlyTileRows = cfg.rows - 1;
  for (int row = 0; row < surfaceOnlyTileRows; ++row) {
    _tiles[row].resize(cfg.cols);
    cfg.tileConfig.row = row;
    for (int col = 0; col < cfg.cols; ++col) {
      cfg.tileConfig.col = col;
      if (EXIT_SUCCESS != _tiles[row][col].init(cfg.tileConfig)) {
        LOGERR("_tiles[%d][%d].init() failed", row, col);
        return EXIT_FAILURE;
      }
    }
  }

  //populate last row
  cfg.tileConfig.tileRsrcId = cfg.tileWholeRsrcId;
  const int lastRowIdx = surfaceOnlyTileRows;
  _tiles[lastRowIdx].resize(cfg.cols);
  cfg.tileConfig.row = lastRowIdx;
  for (int col = 0; col < cfg.cols; ++col) {
    cfg.tileConfig.col = col;
    if (EXIT_SUCCESS != _tiles[lastRowIdx][col].init(cfg.tileConfig)) {
      LOGERR("_tiles[%d][%d].init() failed", lastRowIdx, col);
      return EXIT_FAILURE;
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

