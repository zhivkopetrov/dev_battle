#ifndef GUI_GUI_H_
#define GUI_GUI_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "game_engine/Game.h"

//Own components headers
#include "field/Field.h"

//Forward declarations
class InputEvent;

class Gui final : public Game {
public:
  int32_t init(const std::any& cfg) override;
  void deinit() override;

  void draw() override;
  void handleEvent(const InputEvent &e) override;

private:
  Field _field;
};

#endif /* GUI_GUI_H_ */
