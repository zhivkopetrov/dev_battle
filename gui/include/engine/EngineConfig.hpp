#ifndef GUI_ENGINECONFIG_HPP_
#define GUI_ENGINECONFIG_HPP_

//C system headers

//C++ system headers
#include <cstdint>
#include <string>

//Other libraries headers

//Own components headers

//Forward declarations
class MonitorWindow;
class Renderer;

#define FULL_SCREEN_MODE (1 | 16) // SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS
#define WINDOWED_MODE 4 // SDL_WINDOW_SHOWN

struct EngineConfig {
  EngineConfig() :
    renderer(nullptr),
    window(nullptr),
    displayMode(FULL_SCREEN_MODE),
    monitorWidth(0),
    monitorHeight(0),
    maxFrameRate(0),
    isMultithreadResAllowed(true) {
  }

  Renderer *renderer;
  MonitorWindow *window;
  std::string projectName;
  int32_t displayMode;
  int32_t monitorWidth;
  int32_t monitorHeight;
  uint32_t maxFrameRate;
  bool isMultithreadResAllowed;
};

#endif /* GUI_ENGINECONFIG_HPP_ */

