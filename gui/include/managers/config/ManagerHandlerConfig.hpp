#ifndef GUI_MANAGERHANDLERCFG_HPP_
#define GUI_MANAGERHANDLERCFG_HPP_

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "sdl_utils/containers/config/SDLContainersConfig.hpp"
#include "manager_utils/managers_base/config/DrawMgrBaseConfig.hpp"

//Forward declarations

struct ManagerHandlerConfig {
  SDLContainersConfig sdlContainersCfg;
  DrawMgrBaseConfig drawMgrBaseCfg;
};

#endif /* GUI_MANAGERHANDLERCFG_HPP_ */
