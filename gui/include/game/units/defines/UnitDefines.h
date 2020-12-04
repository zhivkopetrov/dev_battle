#ifndef GUI_UNITDEFINES_H_
#define GUI_UNITDEFINES_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers

//Forward declarations

enum class UnitType : uint8_t {
  KNIGHT,
  SPEARMAN,
  ARCHER,

  HERO_KNIGHT,
  HERO_SPEARMAN,
  HERO_ARCHER,
  HERO_MAGE,

  UNKNOWN = 255
};

#endif /* GUI_UNITDEFINES_H_ */

