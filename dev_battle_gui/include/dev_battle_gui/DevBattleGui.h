#ifndef DEV_BATTLE_GUI_GUI_H_
#define DEV_BATTLE_GUI_GUI_H_

//System headers
#include <cstdint>

//Other libraries headers
#include "game_engine/Game.h"

//Own components headers
#include "dev_battle_gui/field/Field.h"

//Forward declarations
class InputEvent;

class DevBattleGui final : public Game {
public:
  ErrorCode init(const std::any& cfg) override;
  void deinit() override;

  void draw() const override;
  void handleEvent(const InputEvent &e) override;

  void process() override;

private:
  Field _field;
};

#endif /* DEV_BATTLE_GUI_GUI_H_ */
