#ifndef GUI_GAMEDEFINES_H_
#define GUI_GAMEDEFINES_H_

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

#endif /* GUI_GAMEDEFINES_H_ */

