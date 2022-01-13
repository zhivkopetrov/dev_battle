#ifndef DEV_BATTLE_GUI_GUIDEFINES_H_
#define DEV_BATTLE_GUI_GUIDEFINES_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers

//Forward declarations

enum class GameMode {
  UNKNOWN,
  NORMAL,
  EXTENDED,
  SUPER_EXTENDED
};

GameMode toGameMode(const int32_t mode);

#endif /* DEV_BATTLE_GUI_GUIDEFINES_H_ */

