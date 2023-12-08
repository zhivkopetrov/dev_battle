#ifndef DEV_BATTLE_GUI_GUICONFIG_H_
#define DEV_BATTLE_GUI_GUICONFIG_H_

//System headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "dev_battle_gui/defines/GuiDefines.h"
#include "dev_battle_gui/field/config/FieldConfig.h"

//Forward declarations

struct GuiConfig {
  GameMode gameMode = GameMode::UNKNOWN;
  FieldConfig fieldCfg;
};

#endif /* DEV_BATTLE_GUI_GUICONFIG_H_ */

