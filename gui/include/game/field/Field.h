#ifndef GUI_FIELD_H_
#define GUI_FIELD_H_

//C system headers

//C++ system headers
#include <cstdint>
#include <vector>

//Other libraries headers

//Own components headers
#include "game/field/Tile.h"

//Forward declarations
class InputEvent;
struct FieldConfig;

class Field {
public:
  int32_t init(FieldConfig &cfg);

  void handleEvent(const InputEvent &e);

  void draw();

  std::vector<std::vector<Tile>> _tiles;
  Image _tileTargetImg;
};

#endif /* GUI_FIELD_H_ */
