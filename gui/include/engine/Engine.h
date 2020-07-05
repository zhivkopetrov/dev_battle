#ifndef GUI_ENGINE_H_
#define GUI_ENGINE_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "engine/EngineConfig.hpp"
#include "managers/ManagerHandler.h"
#include "sdl_utils/input/InputEvent.h"

//Forward declarations

class Engine {
public:
  int32_t init(const EngineConfig &engineCfg);

  void deinit();

  int32_t recover();

  void start();

private:
  void mainLoop();

  bool processFrame();

  void drawFrame();

  void handleEvent();

  void onInitEnd(const EngineConfig &engineCfg);

  ManagerHandler _managerHandler;

  InputEvent _inputEvent;
};

#endif /* GUI_ENGINE_H_ */
