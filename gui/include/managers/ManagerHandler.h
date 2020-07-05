#ifndef GUI_MANAGERHANDLER_H_
#define GUI_MANAGERHANDLER_H_

//C system headers

//C++ system headers
#include <cstdint>
#include <string>

//Other libraries headers

//Own components headers

//Forward declarations
class MgrBase;
class Renderer;
class MonitorWindow;

namespace Managers {
enum Indexes {
  DRAW_MGR_IDX, RSRC_MGR_IDX, TIMER_MGR_IDX,

  TOTAL_MGRS_COUNT
};
}

struct ManagerHandlerCfg {
  explicit ManagerHandlerCfg(Renderer *inputRenderer,
                             MonitorWindow *inputWindow,
                             const int32_t inputDisplayMode,
                             const int32_t inputMonitorWidth,
                             const int32_t inputMonitorHeight,
                             const std::string &inputProjectName,
                             const bool inputIsMultithreadResAllowed)
      : renderer(inputRenderer), window(inputWindow),
        displayMode(inputDisplayMode), monitorWidth(inputMonitorWidth),
        monitorHeight(inputMonitorHeight), projectName(inputProjectName),
        isMultithreadResAllowed(inputIsMultithreadResAllowed) {
  }

  Renderer *renderer;
  MonitorWindow *window;
  const int32_t displayMode;
  const int32_t monitorWidth;
  const int32_t monitorHeight;
  const std::string projectName;
  const bool isMultithreadResAllowed;
};

class ManagerHandler {
public:
  int32_t init(const ManagerHandlerCfg &cfg);

  /** @brief used to deinitialize all engine managers.
   * */
  void deinit();

  /** @brief used to process tall the engine managers (poll them on every
   *         engine cycle so the managers can do any internal updates, if
   *                                                     such are needed).
   * */
  void process();

  //================== END engine interface functions ====================

private:
  /** @brief used to reset the global manager pointer to nullptr at deinit
   *         so sanity checks could catch possible failures on system
   *         deinit
   *
   *  const int32_t - selected manager id
   * */
  void nullifyGlobalManager(const int32_t managerId);

  /** A container for all managers. We use polymorphical approach
   * so we can iterate it more easily
   * */
  MgrBase *_managers[Managers::TOTAL_MGRS_COUNT];
};

#endif /* GUI_MANAGERHANDLER_H_ */

