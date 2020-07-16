#ifndef GUI_DEBUGCONSOLE_H_
#define GUI_DEBUGCONSOLE_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "manager_utils/drawing/Text.h"

//Forward declarations
class InputEvent;

struct DebugConsoleData {
  int64_t elapsedTime = 0;
  int64_t activeTimers = 0;
  uint64_t gpuMemoryUsage = 0;
  uint32_t activeWidgets = 0;
};

class DebugConsole {
public:
  DebugConsole();

  int32_t init(const uint64_t fontRsrcId, const int64_t maxFrameRate);

  /** @ brief used to toggle active/inactive status of the debug console
   * */
  void handleEvent(const InputEvent &e);

  void update(const DebugConsoleData &data);

  void draw();

  bool isActive() const {
    return _isActive;
  }

private:
  enum DebugTexts {
      FPS_COUNTER,
      ACTIVE_TIMERS,
      ACTIVE_WIDGETS,
      GPU_MEMORY_USAGE,

      DEBUG_TEXTS_COUNT
  };

  Text _debugTexts[DEBUG_TEXTS_COUNT];

  int64_t _maxFrames;

  int32_t _updateCounter;

  bool _isActive;
};

#endif /* GUI_DEBUGCONSOLE_H_ */

