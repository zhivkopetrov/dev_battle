//Corresponding header
#include "engine/DebugConsole.h"

//C system headers

//C++ system headers
#include <cstdlib>
#include <string>

//Other libraries headers

//Own components headers
#include "sdl_utils/input/InputEvent.h"
#include "utils/LimitValues.hpp"
#include "utils/time/Time.h"
#include "utils/Log.h"

#define UPDATE_SKIPS 20

DebugConsole::DebugConsole()
    : _maxFrames(INIT_UINT32_VALUE), _updateCounter(UPDATE_SKIPS),
      _isActive(false) {

}

int32_t DebugConsole::init(const uint64_t fontRsrcId,
                           const int64_t maxFrameRate) {
  _fpsText.create(fontRsrcId, "0", Colors::YELLOW, Point(20, 20));
  _activeWidgetsText.create(fontRsrcId, "0", Colors::YELLOW, Point(20, 50));
  _maxFrames = maxFrameRate;

  return EXIT_SUCCESS;
}

void DebugConsole::handleEvent(const InputEvent &e) {
  if (TouchEvent::KEYBOARD_RELEASE == e.type) {
    if (Keyboard::KEY_TILDA == e.key) {
      _isActive = !_isActive;
    }
  }
}

//update fps text once in a while to get a stable(not constantly changing) image
void DebugConsole::update(const int64_t elapsedTime,
                          const uint32_t activeWidgets) {
  --_updateCounter;
  if (0 < _updateCounter) {
    return;
  }
  _updateCounter = UPDATE_SKIPS;

  int64_t frames = MILLISECOND / elapsedTime;
  if (frames > _maxFrames) {
    frames = _maxFrames;
  }

  std::string fpsStr = "FPS: ";
  fpsStr.append(std::to_string(frames));
  _fpsText.setText(fpsStr.c_str());

  std::string widgetsStr = "Active widgets: ";
  widgetsStr.append(std::to_string(activeWidgets));
  _activeWidgetsText.setText(widgetsStr.c_str());
}

void DebugConsole::draw() {
  _fpsText.draw();
  _activeWidgetsText.draw();
}

