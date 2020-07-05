#ifndef GUI_DRAWMGR_H_
#define GUI_DRAWMGR_H_

//C system headers

//C++ system headers
#include <cstddef>

//Other libraries headers

//Own components headers
#include "manager_utils/managers_base/DrawMgrBase.h"

//Forward declarations

class DrawMgr: public DrawMgrBase {
public:
  /** @brief
   *
   *  @param Renderer *      - the actual renderer used for drawing
   *  @param MonitorWindow * - the program window
   *  @param const int32_t   - monitor display mode
   *                                     (full screen, windowed, etc ...)
   *  @param const int32_t   - the width of a single monitor (in px)
   *  @param const int32_t   - the height of a single monitor (in px)
   * */
  explicit DrawMgr(Renderer* renderer,
                   MonitorWindow* window,
                   const int32_t displayMode,
                   const int32_t monitorWidth,
                   const int32_t monitorHeight);

  virtual ~DrawMgr() = default;

  // forbid the default constructor
  DrawMgr() = delete;

  // forbid the copy and move constructors
  DrawMgr(const DrawMgr& other) = delete;
  DrawMgr(DrawMgr&& other) = delete;

  // forbid the copy and move assignment operators
  DrawMgr& operator=(const DrawMgr& other) = delete;
  DrawMgr& operator=(DrawMgr&& other) = delete;

  //================= START MgrBase related functions ====================

  /** @brief used to initialize the current manager.
   *         NOTE: this is the first function that will be called.
   *
   *  @return int32_t - error code
   * */
  int32_t init() final;

  /** @brief used to recover the current manager.
   *         NOTE: this function that will be called if init() passed
   *                                                       successfully.
   *         NOTE2: recover() function will be called after the
   *                successful pass of init() function, even if system
   *                was shutdown correctly.
   *
   *  @return int32_t - error code
   * */
  int32_t recover() final;

  /** @brief used to deinitialize the current manager.
   * */
  void deinit() final;

  /** @brief used to process the current manager (poll him on every
   *         engine cycle so the managers can do any internal updates, if
   *                                                     such are needed).
   * */
  void process() final;

  /** @brief captures user inputs (if any)
   *
   *  @param const InputEvent & - user input event
   * */
  void handleEvent(const InputEvent& e) final;

  /** @brief returns the name of the current manager
   *
   *  @return const char * - current manager name
   * */
  const char* getName() final;
};

extern DrawMgr *gDrawMgr;

#endif /* GUI_DRAWMGR_H_ */

