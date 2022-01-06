#ifndef GUI_ENGINE_H_
#define GUI_ENGINE_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "managers/ManagerHandler.h"
#include "sdl_utils/input/InputEvent.h"
#include "game/Game.h"
#include "engine/DebugConsole.h"

//Forward declarations
struct EngineConfig;

class Engine {
public:
  ~Engine();

  int32_t init(EngineConfig &engineCfg);

  int32_t recover();

  int32_t start();

private:
  void deinit();

  void mainLoop();

  bool processFrame();

  void drawFrame();

  void handleEvent();

  void onInitEnd(const EngineConfig &engineCfg);

  void populateDebugConsole(const int64_t elapsedMicroseconds);

  void limitFPS(const int64_t elapsedTime);

  ManagerHandler _managerHandler;

  InputEvent _inputEvent;

  Game _game;

  DebugConsole _debugConsole;
};

#endif /* GUI_ENGINE_H_ */
