//Corresponding header
#include "dev_battle_gui/field/Tile.h"

//System headers
#include <string>

//Other libraries headers
#include "manager_utils/drawing/Fbo.h"

//Own components headers
#include "dev_battle_gui/field/config/TileConfig.h"

namespace {
constexpr auto DEBUG_TEXT_OFFSET_X = 1;
constexpr auto DEBUG_TEXT_OFFSET_Y = 13;
}

ErrorCode Tile::init(const TileConfig &cfg) {
  _tileImg.create(cfg.tileRsrcId);
  _tileImg.setPosition(cfg.screenCoordinates);

  std::string debugText;
  debugText.reserve(8); //max debug string size
  debugText.append("[").append(std::to_string(cfg.row)).append(",").append(
      std::to_string(cfg.col)).append("]");
  _debugText.create(cfg.debugFontRsrcId, debugText.c_str(), Colors::RED,
      Point(cfg.screenCoordinates.x + DEBUG_TEXT_OFFSET_X,
            cfg.screenCoordinates.y + DEBUG_TEXT_OFFSET_Y));

  static int32_t frame = 0;
  _tileImg.setFrame(frame++ % 4);

  return ErrorCode::SUCCESS;
}

void Tile::draw() {
  _tileImg.draw();
  _debugText.draw();
}

void Tile::drawOnFbo(Fbo &fbo) const {
  fbo.addWidget(_tileImg);
  fbo.addWidget(_debugText);
}

