#ifndef GUI_TIMERMGR_H_
#define GUI_TIMERMGR_H_

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "manager_utils/managers_base/TimerMgrBase.h"

//Forward declarations
class InputEvent;

class TimerMgr: public TimerMgrBase {
public:
  TimerMgr() = default;
  virtual ~TimerMgr() = default;

  //forbid the copy and move constructors
  TimerMgr(const TimerMgr &other) = delete;
  TimerMgr(TimerMgr &&other) = delete;

  //forbid the copy and move assignment operators
  TimerMgr& operator=(const TimerMgr &other) = delete;
  TimerMgr& operator=(TimerMgr &&other) = delete;

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
  void handleEvent(const InputEvent &e) final;

  /** @brief returns the name of the current manager
   *
   *  @return const char* - current manager name
   * */
  const char* getName() final;

  //================== END MgrBase related functions =====================
};

extern TimerMgr *gTimerMgr;

#endif /* GUI_TIMERMGR_H_ */

