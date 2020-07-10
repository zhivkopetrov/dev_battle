#ifndef GUI_FIELD_H_
#define GUI_FIELD_H_

//C system headers

//C++ system headers
#include <cstdint>
#include <vector>

//Other libraries headers

//Own components headers
#include "manager_utils/drawing/Image.h"

//Forward declarations
class InputEvent;
struct FieldConfig;

class Field {
public:
  int32_t init(const FieldConfig &cfg);

  void handleEvent(const InputEvent &e);

  void draw();

  //TODO make a Tile class
  std::vector<std::vector<Image>> _tiles;
};

#endif /* GUI_FIELD_H_ */
