//Corresponding header
#include "dev_battle_gui/DevBattleGui.h"

//System headers

//Other libraries headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

//Own components headers
#include "dev_battle_gui/config/GuiConfig.h"

ErrorCode DevBattleGui::init(const std::any &cfg) {
  try {
    const auto &gameCfg = std::any_cast<const GuiConfig&>(cfg);
    if (ErrorCode::SUCCESS != _field.init(gameCfg.fieldCfg)) {
      LOGERR("Error in _field.init()");
      return ErrorCode::FAILURE;
    }
  } catch (const std::bad_any_cast &e) {
    LOGERR("std::any_cast<GuiConfig&> failed, %s", e.what());
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

void DevBattleGui::deinit() {

}

void DevBattleGui::draw() const {
  _field.draw();
}

void DevBattleGui::handleEvent(const InputEvent &e) {
  _field.handleEvent(e);
}

void DevBattleGui::process() {

}

