#ifndef DEV_BATTLE_GUI_GUI_H_
#define DEV_BATTLE_GUI_GUI_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "game_engine/Game.h"

//Own components headers
#include "dev_battle_gui/field/Field.h"

//Forward declarations
class InputEvent;

class DevBattleGui final : public Game {
public:
  int32_t init(const std::any& cfg) override;
  void deinit() override;

  void draw() const override;
  void handleEvent(const InputEvent &e) override;

private:
  Field _field;
};

#endif /* DEV_BATTLE_GUI_GUI_H_ */
