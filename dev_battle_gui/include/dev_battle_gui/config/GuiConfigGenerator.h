#ifndef DEV_BATTLE_GUI_INCLUDE_DEV_BATTLE_GUI_CONFIG_GUICONFIGGENERATOR_H_
#define DEV_BATTLE_GUI_INCLUDE_DEV_BATTLE_GUI_CONFIG_GUICONFIGGENERATOR_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "game_engine/config/ApplicationConfig.h"

//Own components headers
#include "dev_battle_gui/config/GuiConfig.h"

//Forward declarations

class GuiConfigGenerator {
public:
  GuiConfigGenerator() = delete;

  static std::vector<DependencyDescription> generateDependencies(int32_t argc,
                                                                 char **args);

  static ApplicationConfig generateConfig();
};

#endif /* DEV_BATTLE_GUI_INCLUDE_DEV_BATTLE_GUI_CONFIG_GUICONFIGGENERATOR_H_ */
