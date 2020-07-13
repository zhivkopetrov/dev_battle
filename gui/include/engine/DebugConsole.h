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

class DebugConsole {
public:
  DebugConsole();

  int32_t init(const uint64_t fontRsrcId, const int64_t maxFrameRate);

  /** @ brief used to toggle active/inactive status of the debug console
   * */
  void handleEvent(const InputEvent &e);

  void update(const int64_t elapsedTime, const uint32_t activeWidgets);

  void draw();

  inline bool isActive() const {
    return _isActive;
  }

private:
  Text _fpsText;
  Text _activeWidgetsText;

  int64_t _maxFrames;

  int32_t _updateCounter;

  bool _isActive;
};

#endif /* GUI_DEBUGCONSOLE_H_ */

