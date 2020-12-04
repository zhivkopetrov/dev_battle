#ifndef GUI_UNITFACTORY_H_
#define GUI_UNITFACTORY_H_

//C system headers

//C++ system headers
#include <cstdint>
#include <vector>
#include <unordered_map>

//Other libraries headers

//Own components headers
#include "game/units/basic/config/BasicUnitConfig.hpp"
#include "game/units/hero/config/HeroConfig.hpp"
#include "utils/data_type/EnumClassUtils.hpp"

//Forward declarations

class UnitFactory {
public:
  int32_t init(const std::vector<BasicUnitConfig> &basicUnitsCfg,
               const std::vector<HeroConfig> &heroesCfg);

  int32_t produceBasicUnit(const UnitType unitType,
                           const BasicUnitRank basicUnitRank,
                           BasicUnitConfig &outBasicUnitConfig) const;

  int32_t produceHero(const UnitType unitType, HeroConfig &outHeroConfig) const;

private:
  std::unordered_map<UnitType, BasicUnitConfig, EnumClassHash> _basicUnitsCfg;
  std::unordered_map<UnitType, HeroConfig, EnumClassHash> _heroesCfg;
};

#endif /* GUI_UNITFACTORY_H_ */
