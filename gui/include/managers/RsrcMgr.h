#ifndef GUI_RSRCMGR_H_
#define GUI_RSRCMGR_H_

//C system headers

//C++ system headers
#include <cstdint>
#include <vector>

//Other libraries headers

//Own components headers
#include "manager_utils/managers_base/RsrcMgrBase.h"

//Forward declarations
class InputEvent;
class RsrcFileExecutor;
class EngineProxyInterface;
class Renderer;

class RsrcMgr: public RsrcMgrBase {
public:
  explicit RsrcMgr(const SDLContainersConfig &cfg);

  virtual ~RsrcMgr() = default;

  //forbid the default constructor
  RsrcMgr() = delete;

  //forbid the copy and move constructors
  RsrcMgr(const RsrcMgr &other) = delete;
  RsrcMgr(RsrcMgr &&other) = delete;

  //forbid the copy and move assignment operators
  RsrcMgr& operator=(const RsrcMgr &other) = delete;
  RsrcMgr& operator=(RsrcMgr &&other) = delete;

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
   *  @return const char * - current manager name
   * */
  const char* getName() final;

  //================== END MgrBase related functions =====================

private:
  /* Concrete implementation of RsrcMgrBase
   *
   *          WARNING: this method will be called from the main(drawing)
   *                   thread. Do not forget to lock your data!
   * */
  void onLoadTextureMultipleCompleted(const int32_t batchId) final;
};

extern RsrcMgr *gRsrcMgr;

#endif /* GUI_RSRCMGR_H_ */

