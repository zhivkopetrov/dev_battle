//Corresponding header
#include "dev_battle_gui/config/GuiIniConfigParser.h"

//System headers

//Other libraries headers
#include "utils/file/IniFileUtils.h"
#include "utils/data_type/EnumClassUtils.h"
#include "utils/log/Log.h"
#include "utils/ErrorCode.h"

//Own components headers

namespace {
// window section
constexpr auto WINDOW_SECTION_NAME = "window";
constexpr auto WINDOW_NAME = "name";
constexpr auto WINDOW_DISPLAY_MODE_NAME = "display_mode";
constexpr auto WINDOW_BORDER_MODE_NAME = "border_mode";
constexpr auto WINDOW_X_NAME = "window_x";
constexpr auto WINDOW_Y_NAME = "window_y";
constexpr auto WINDOW_WIDTH_NAME = "window_width";
constexpr auto WINDOW_HEIGHT_NAME = "window_height";

// renderer section
constexpr auto RENDERER_SECTION_NAME = "renderer";
constexpr auto RENDERER_FLAGS_MASK_NAME = "flags_mask";
constexpr auto RENDERER_SCALE_QUALITY_NAME = "scale_quality";
constexpr auto RENDERER_EXECUTION_POLICY_NAME = "execution_policy";
constexpr auto RENDERER_RESOURCE_LOADING_THREADS_NUM_NAME =
  "resource_loading_threads_num";

// engine section
constexpr auto ENGINE_SECTION_NAME = "engine";
constexpr auto ENGINE_TARGET_FPS_NAME = "target_fps";
constexpr auto ENGINE_INPUT_EVENT_HANDLER_POLICY_NAME =
  "input_event_handler_policy";
constexpr auto ENGINE_ACTION_EVENT_HANDLER_POLICY_NAME =
  "action_event_handler_policy";

ErrorCode populateWindowSection(
  const IniFileData &data, GuiIniConfig::Window &outCfg) {
  auto it = data.find(WINDOW_SECTION_NAME);
  if (it == data.end()) {
    LOGERR("Error, section name: '%s' not found", WINDOW_SECTION_NAME);
    return ErrorCode::FAILURE;
  }
  const IniFileSection &section = it->second;

  bool success = 
    IniFileUtils::getKeyValueString(section, WINDOW_NAME, outCfg.name);
  if (!success) return ErrorCode::FAILURE;

  int32_t intParam{};
  success = 
    IniFileUtils::getKeyValueInt(section, WINDOW_DISPLAY_MODE_NAME, intParam);
  if (!success) return ErrorCode::FAILURE;
  outCfg.windowDisplayMode = toEnum<WindowDisplayMode>(intParam);

  success = 
    IniFileUtils::getKeyValueInt(section, WINDOW_BORDER_MODE_NAME, intParam);
  if (!success) return ErrorCode::FAILURE;
  outCfg.windowBorderMode = toEnum<WindowBorderMode>(intParam);

  success = 
    IniFileUtils::getKeyValueInt(section, WINDOW_X_NAME, outCfg.windowRect.x);
  if (!success) return ErrorCode::FAILURE;

  success = 
    IniFileUtils::getKeyValueInt(section, WINDOW_Y_NAME, outCfg.windowRect.y);
  if (!success) return ErrorCode::FAILURE;

  success = 
    IniFileUtils::getKeyValueInt(section, WINDOW_WIDTH_NAME, outCfg.windowRect.w);
  if (!success) return ErrorCode::FAILURE;

  success = 
    IniFileUtils::getKeyValueInt(section, WINDOW_HEIGHT_NAME, outCfg.windowRect.h);
  if (!success) return ErrorCode::FAILURE;

  return ErrorCode::SUCCESS;
}

ErrorCode populateRendererSection(
  const IniFileData &data, GuiIniConfig::Renderer &outCfg) {
  auto it = data.find(RENDERER_SECTION_NAME);
  if (it == data.end()) {
    LOGERR("Error, section name: '%s' not found", RENDERER_SECTION_NAME);
    return ErrorCode::FAILURE;
  }
  const IniFileSection &section = it->second;

  bool success = 
    IniFileUtils::getKeyValueUint(section, RENDERER_FLAGS_MASK_NAME, outCfg.flagsMask);
  if (!success) return ErrorCode::FAILURE;

  int32_t intParam{};
  success = IniFileUtils::getKeyValueInt(section, RENDERER_SCALE_QUALITY_NAME, intParam);
  if (!success) return ErrorCode::FAILURE;
  outCfg.scaleQuality = toEnum<RendererScaleQuality>(intParam);

  success = IniFileUtils::getKeyValueInt(
    section, RENDERER_EXECUTION_POLICY_NAME, intParam);
  if (!success) return ErrorCode::FAILURE;
  outCfg.executinPolicy = toEnum<RendererPolicy>(intParam);

  success = IniFileUtils::getKeyValueUint(
    section, RENDERER_RESOURCE_LOADING_THREADS_NUM_NAME, outCfg.resourceLoadingThreadsNum);
  if (!success) return ErrorCode::FAILURE;

  return ErrorCode::SUCCESS;
}

ErrorCode populateEngineSection(
  const IniFileData &data, GuiIniConfig::Engine &outCfg) {
  auto it = data.find(ENGINE_SECTION_NAME);
  if (it == data.end()) {
    LOGERR("Error, section name: '%s' not found", ENGINE_SECTION_NAME);
    return ErrorCode::FAILURE;
  }
  const IniFileSection &section = it->second;

  bool success = 
    IniFileUtils::getKeyValueUint(section, ENGINE_TARGET_FPS_NAME, outCfg.targetFps);
  if (!success) return ErrorCode::FAILURE;

  int32_t intParam{};
  success = IniFileUtils::getKeyValueInt(section, ENGINE_INPUT_EVENT_HANDLER_POLICY_NAME, intParam);
  if (!success) return ErrorCode::FAILURE;
  outCfg.inputEventHandlerPolicy = toEnum<InputEventHandlerPolicy>(intParam);

  success = IniFileUtils::getKeyValueInt(
    section, ENGINE_ACTION_EVENT_HANDLER_POLICY_NAME, intParam);
  if (!success) return ErrorCode::FAILURE;
  outCfg.actionEventHandlerPolicy = toEnum<ActionEventHandlerPolicy>(intParam);

  return ErrorCode::SUCCESS;
}

}  // end anonymous namespace

ErrorCode parseConfig(std::string_view filePath, GuiIniConfig& outCfg) {
  IniFileData fileData;
  ErrorCode err = IniFileUtils::parseFile(filePath, fileData);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("IniFileUtils::parseFile() failed");
    return ErrorCode::FAILURE;
  }

  err = populateWindowSection(fileData, outCfg.windowCfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("Error, populateImageSection() failed");
    return ErrorCode::FAILURE;
  }

  err = populateRendererSection(fileData, outCfg.rendererCfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("Error, populateRendererSection() failed");
    return ErrorCode::FAILURE;
  }

  err = populateEngineSection(fileData, outCfg.engineCfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("Error, populateEngineSection() failed");
    return ErrorCode::FAILURE;
  }

  //TODO1: add validate step for all params
  //TODO2: add print method for all used params

  return ErrorCode::SUCCESS;
}
