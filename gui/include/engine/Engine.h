#ifndef GUI_ENGINE_H_
#define GUI_ENGINE_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "managers/ManagerHandler.h"
#include "sdl_utils/input/InputEvent.h"
#include "manager_utils/drawing/Image.h"
#include "manager_utils/drawing/animation/FrameAnimation.h"

//Forward declarations
struct EngineConfig;

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

  FrameAnimation knightAnim;
  Image map;
};

#endif /* GUI_ENGINE_H_ */
