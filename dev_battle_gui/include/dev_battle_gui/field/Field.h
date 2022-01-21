#ifndef DEV_BATTLE_GUI_FIELD_H_
#define DEV_BATTLE_GUI_FIELD_H_

//C system headers

//C++ system headers
#include <cstdint>
#include <vector>

//Other libraries headers
#include "manager_utils/drawing/Fbo.h"

//Own components headers
#include "dev_battle_gui/field/Tile.h"

//Forward declarations
class InputEvent;
struct FieldConfig;

class Field {
public:
  int32_t init(const FieldConfig &cfg);

  void handleEvent(const InputEvent &e);

  void draw() const;

  void updateFieldFbo();

  std::vector<std::vector<Tile>> _tiles;
  Image _tileTargetImg;

  Fbo _fieldFbo;
};

#endif /* DEV_BATTLE_GUI_FIELD_H_ */
