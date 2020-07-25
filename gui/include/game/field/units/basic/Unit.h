#ifndef GUI_UNIT_H_
#define GUI_UNIT_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "manager_utils/drawing/Image.h"

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

#endif /* GUI_UNIT_H_ */
