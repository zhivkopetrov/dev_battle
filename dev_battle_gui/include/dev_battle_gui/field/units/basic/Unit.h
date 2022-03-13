#ifndef DEV_BATTLE_GUI_UNIT_H_
#define DEV_BATTLE_GUI_UNIT_H_

//System headers
#include <cstdint>

//Other libraries headers
#include "manager_utils/drawing/Image.h"
#include "utils/ErrorCode.h"

//Own components headers

//Forward declarations
class InputEvent;
struct UnitConfig;

class Unit {
public:
  ErrorCode init(const UnitConfig &cfg);

  void handleEvent(const InputEvent &e);

  void draw();

protected:
  Image unitImg;
};

#endif /* DEV_BATTLE_GUI_UNIT_H_ */
