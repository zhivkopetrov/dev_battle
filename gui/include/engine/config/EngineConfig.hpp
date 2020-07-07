#ifndef GUI_ENGINECONFIG_HPP_
#define GUI_ENGINECONFIG_HPP_

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers

//Forward declarations
#include "managers/config/ManagerHandlerConfig.hpp"

struct EngineConfig {
  ManagerHandlerConfig managerHandlerCfg;
  uint32_t maxFrameRate = 0;
};

#endif /* GUI_ENGINECONFIG_HPP_ */

