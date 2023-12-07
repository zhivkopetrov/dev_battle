//Corresponding header
#include "dev_battle_gui/field/units/basic/Unit.h"

//System headers

//Other libraries headers
#include "utils/log/Log.h"

//Own components headers
#include "dev_battle_gui/field/units/config/UnitConfig.h"

ErrorCode Unit::init([[maybe_unused]]const UnitConfig &cfg) {
  return ErrorCode::SUCCESS;
}

void Unit::handleEvent([[maybe_unused]]const InputEvent &e) {

}

void Unit::draw() {

}

