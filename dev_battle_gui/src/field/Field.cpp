//Corresponding header
#include "dev_battle_gui/field/Field.h"

//C system headers

//C++ system headers

//Other libraries headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

//Own components headers
#include "dev_battle_gui/field/config/FieldConfig.h"

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

int32_t Field::init(const FieldConfig &cfg) {
  if (0 >= cfg.rows || 0 >= cfg.cols) {
    LOGERR("Invalid configuration, rows: %d, cols: %d. Both 'rows' and 'cols' "
        "needs to be positive number", cfg.rows, cfg.cols);
    return FAILURE;
  }

  TileConfig tileConfig;
  tileConfig.debugFontRsrcId = cfg.debugFontRsrcId;

  _tiles.resize(cfg.rows);
  for (int row = 0; row < cfg.rows; ++row) {
    _tiles[row].resize(cfg.cols);
    tileConfig.row = row;
    for (int col = 0; col < cfg.cols; ++col) {
      //ensure left column, right column and last row have 'whole' rsrc frame
      tileConfig.tileRsrcId =
          ((row == cfg.rows - 1) || (col == cfg.cols - 1) || (col == 0)) ?
              cfg.tileWholeRsrcId : cfg.tileSurfaceRsrcId;

      tileConfig.col = col;
      tileConfig.screenCoordinates =
          getTileCoordinate(row, col, cfg.tileWidth, cfg.tileHeight);
      //apply field offset
      tileConfig.screenCoordinates.x += cfg.fieldDimensions.x;
      tileConfig.screenCoordinates.y += cfg.fieldDimensions.y;
      if (SUCCESS != _tiles[row][col].init(tileConfig)) {
        LOGERR("_tiles[%d][%d].init() failed", row, col);
        return FAILURE;
      }
    }
  }

  _fieldSB.create(cfg.fieldDimensions);
  updateFieldSpriteBuffer();

  return SUCCESS;
}

void Field::handleEvent([[maybe_unused]]const InputEvent &e) {

}

void Field::draw() const {
  _fieldSB.draw();
}

void Field::updateFieldSpriteBuffer() {
  _fieldSB.unlock();
  _fieldSB.reset();
  for (const auto & row : _tiles) {
    for (const auto &tile : row) {
      tile.drawOnSpriteBuffer(_fieldSB);
    }
  }
  _fieldSB.update();
  _fieldSB.lock();
}

