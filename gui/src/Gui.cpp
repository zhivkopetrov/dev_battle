//Corresponding header
#include "Gui.h"

//C system headers

//C++ system headers

//Other libraries headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

//Own components headers
#include "config/GuiConfig.h"

int32_t Gui::init(const std::any& cfg) {
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

void Gui::deinit() {

}

void Gui::draw() {
  _field.draw();
}

void Gui::handleEvent(const InputEvent &e) {
  _field.handleEvent(e);
}

