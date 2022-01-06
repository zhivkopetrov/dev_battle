#ifndef GUI_GUICONFIG_H_
#define GUI_GUICONFIG_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "defines/GuiDefines.h"
#include "field/config/FieldConfig.h"

//Forward declarations

struct GuiConfig {
  GameMode gameMode = GameMode::UNKNOWN;
  FieldConfig fieldCfg;
};

#endif /* GUI_GUICONFIG_H_ */

