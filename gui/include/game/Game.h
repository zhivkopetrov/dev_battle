#ifndef GUI_GAME_H_
#define GUI_GAME_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "game/field/Field.h"

//Forward declarations
class InputEvent;
struct GameConfig;

class Game {
public:
  int32_t init(GameConfig &cfg);

  void handleEvent(const InputEvent &e);

  void draw();

private:
  Field _field;
};

#endif /* GUI_GAME_H_ */
