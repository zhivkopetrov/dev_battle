#ifndef DEV_BATTLE_GUI_UNITCONFIG_H_
#define DEV_BATTLE_GUI_UNITCONFIG_H_

//System headers
#include <cstdint>
#include <vector>

//Other libraries headers
#include "utils/drawing/Point.h"

//Own components headers

//Forward declarations

namespace Config {
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
} //namespace Config

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

struct UnitConfig {
  std::vector<uint64_t> unitActionAnimRsrcIds;
  std::vector<uint64_t> unitAttackAnimRsrcIds;
  UnitType unitType = UnitType::UNKNOWN;
};

struct HeroConfig {
  UnitConfig unitConfig;
  std::vector<uint64_t> heroActionAnimRsrcIds;
  Point startPos;
};

#endif /* DEV_BATTLE_GUI_UNITCONFIG_H_ */

