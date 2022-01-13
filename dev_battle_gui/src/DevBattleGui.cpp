//Corresponding header
#include "dev_battle_gui/DevBattleGui.h"

//C system headers

//C++ system headers

//Other libraries headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

//Own components headers
#include "dev_battle_gui/config/GuiConfig.h"

int32_t DevBattleGui::init(const std::any& cfg) {
  try {
      const auto& gameCfg = std::any_cast<const GuiConfig&>(cfg);
      if (SUCCESS != _field.init(gameCfg.fieldCfg)) {
        LOGERR("Error in _field.init()");
        return FAILURE;
      }
  }
  catch(const std::bad_any_cast& e) {
      LOGERR("std::any_cast<GuiConfig&> failed, %s", e.what());
      return FAILURE;
  }

  return SUCCESS;
}

void DevBattleGui::deinit() {

}

void DevBattleGui::draw() {
  _field.draw();
}

void DevBattleGui::handleEvent(const InputEvent &e) {
  _field.handleEvent(e);
}

