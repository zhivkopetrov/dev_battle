#ifndef GUI_FIELD_H_
#define GUI_FIELD_H_

//C system headers

//C++ system headers
#include <cstdint>
#include <vector>

//Other libraries headers
#include "manager_utils/drawing/SpriteBuffer.h"

//Own components headers
#include "field/Tile.h"

//Forward declarations
class InputEvent;
struct FieldConfig;

class Field {
public:
  int32_t init(const FieldConfig &cfg);

  void handleEvent(const InputEvent &e);

  void draw();

  void updateFieldSpriteBuffer();

  std::vector<std::vector<Tile>> _tiles;
  Image _tileTargetImg;

  SpriteBuffer _fieldSB;
};

#endif /* GUI_FIELD_H_ */
