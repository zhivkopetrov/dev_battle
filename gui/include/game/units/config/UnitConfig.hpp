#ifndef GUI_UNITCONFIG_HPP_
#define GUI_UNITCONFIG_HPP_

//C system headers

//C++ system headers
#include <cstdint>
#include <vector>

//Other libraries headers

//Own components headers
#include "game/units/defines/UnitDefines.h"

//Forward declarations

namespace UnitConfigs {
enum KnightAttackConfig {
  KNIGHT_ATTACK_1,
  KNIGHT_ATTACK_2,
  KNIGHT_ATTACK_3,
  KNIGHT_ATTACK_4,
  KNIGHT_ATTACK_COUNT
};

enum SpearmanAttackConfig {
  SPEARMAN_ATTACK_1,
  SPEARMAN_ATTACK_2,
  SPEARMAN_ATTACK_3,
  SPEARMAN_ATTACK_4,
  SPEARMAN_ATTACK_COUNT
};

enum ArcherAttackConfig {
  ARCHER_ATTACK_UP,
  ARCHER_ATTACK_STRAIGHT,
  ARCHER_ATTACK_DOWN,
  ARCHER_ATTACK_COUNT
};

enum MageAttackConfig {
  MAGE_ATTACK_1,
  MAGE_ATTACK_2,
  MAGE_ATTACK_3,
  MAGE_ATTACK_COUNT
};

enum UnitActionConfig {
  UNIT_POSITION_IDLE,
  UNIT_POSITION_RUN,
  UNIT_POSITION_HIT,
  UNIT_POSITION_DEAD,
  UNIT_POSITION_COUNT
};

enum HeroActionConfig {
  HERO_ACTION_JUMP,
  HERO_ACTION_ROLL,
  HERO_ACTION_DASH,
  HERO_ACTION_COUNT
};
} //namespace UnitConfigs

struct UnitVitalData {
  uint8_t maxHealth = 0;
  uint8_t maxSpeed = 0;
  uint8_t maxRange = 0;
};

struct UnitConfig {
  std::vector<uint64_t> unitActionAnimRsrcIds;
  std::vector<uint64_t> unitAttackAnimRsrcIds;
  UnitType unitType;
};

#endif /* GUI_UNITCONFIG_HPP_ */

