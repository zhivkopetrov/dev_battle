//Corresponding header
#include "game/field/units/basic/Unit.h"

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "game/field/units/config/UnitConfig.hpp"
#include "utils/ErrorCode.h"
#include "utils/Log.h"

int32_t Unit::init([[maybe_unused]]const UnitConfig &cfg) {
  return SUCCESS;
}

void Unit::handleEvent([[maybe_unused]]const InputEvent &e) {

}

void Unit::draw() {

}

