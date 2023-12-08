#ifndef DEV_BATTLE_GUI_GUIINICONFIGPARSER_H_
#define DEV_BATTLE_GUI_GUIINICONFIGPARSER_H_

//System headers
#include <cstdint>
#include <string>
#include <string_view>

//Other libraries headers
#include "game_engine/defines/ActionEventDefines.h"
#include "game_engine/defines/InputEventDefines.h"
#include "sdl_utils/drawing/defines/RendererDefines.h"
#include "sdl_utils/drawing/defines/MonitorDefines.h"
#include "utils/drawing/Rectangle.h"
#include "utils/ErrorCode.h"

//Own components headers

//Forward declarations

struct GuiIniConfig {
  struct Window {
    WindowDisplayMode windowDisplayMode {};
    WindowBorderMode windowBorderMode {};
    Rectangle windowRect {};
    std::string name;
  };

  struct Renderer {
    RendererPolicy executinPolicy {};
    RendererScaleQuality scaleQuality {};
    uint32_t flagsMask {};
    uint32_t resourceLoadingThreadsNum {};
  };

  struct Engine {
    uint32_t targetFps {};
    ActionEventHandlerPolicy actionEventHandlerPolicy {};
    InputEventHandlerPolicy inputEventHandlerPolicy {};
  };

  Window windowCfg;
  Renderer rendererCfg;
  Engine engineCfg;
};

ErrorCode parseConfig(std::string_view filePath, GuiIniConfig& outCfg);

#endif /* DEV_BATTLE_GUI_GUIINICONFIGPARSER_H_ */

