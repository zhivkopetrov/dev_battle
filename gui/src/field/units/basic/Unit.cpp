//Corresponding header
#include "field/units/basic/Unit.h"

//C system headers

//C++ system headers

//Other libraries headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

//Own components headers
#include "field/units/config/UnitConfig.h"

int32_t Unit::init([[maybe_unused]]const UnitConfig &cfg) {
  return SUCCESS;
}

void Unit::handleEvent([[maybe_unused]]const InputEvent &e) {

}

void Unit::draw() {

}

