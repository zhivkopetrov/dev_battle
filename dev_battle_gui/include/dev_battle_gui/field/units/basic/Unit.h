#ifndef DEV_BATTLE_GUI_UNIT_H_
#define DEV_BATTLE_GUI_UNIT_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "manager_utils/drawing/Image.h"

//Own components headers

//Forward declarations
class InputEvent;
struct UnitConfig;

class Unit {
public:
  int32_t init(const UnitConfig &cfg);

  void handleEvent(const InputEvent &e);

  void draw();

protected:
  Image unitImg;
};

#endif /* DEV_BATTLE_GUI_UNIT_H_ */
