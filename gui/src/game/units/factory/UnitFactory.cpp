//Corresponding header
#include "game/units/factory/UnitFactory.h"

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

int32_t UnitFactory::init(const std::vector<BasicUnitConfig> &basicUnitsCfg,
                          const std::vector<HeroConfig> &heroesCfg) {

#warning basic units need 3 types PER unit (because of the ranks) FIX ME
  for (const auto &cfg : basicUnitsCfg) {
    const auto it = _basicUnitsCfg.find(cfg.unitCfg.unitType);
    if (it != _basicUnitsCfg.end()) {
      LOGERR("Invalid config. Duplication found in UnitType: %hhu",
          getEnumValue(cfg.unitCfg.unitType));
      return FAILURE;
    }
    _basicUnitsCfg.insert(it, cfg);
  }

  for (const auto &cfg : heroesCfg) {
    const auto it = _heroesCfg.find(cfg.unitCfg.unitType);
    if (it != _heroesCfg.end()) {
      LOGERR("Invalid config. Duplication found in UnitType: %hhu",
          getEnumValue(cfg.unitCfg.unitType));
      return FAILURE;
    }
    _basicUnitsCfg.insert(it, cfg);
  }

  return SUCCESS;
}

int32_t UnitFactory::produceBasicUnit(
    const UnitType unitType, const BasicUnitRank basicUnitRank,
    BasicUnitConfig &outBasicUnitConfig) const {
  return SUCCESS;
}

int32_t UnitFactory::produceHero(const UnitType unitType,
                                 HeroConfig &outHeroConfig) const {
  return SUCCESS;
}
