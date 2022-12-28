#Author Zhivko Petrov
cmake_minimum_required(VERSION 3.10.2)

project(dev_battle)

if(EMSCRIPTEN)
  set(USE_FLAGS "-s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[png, jpg]'")
  set(ASSETS "--preload-file ${CMAKE_INSTALL_PREFIX}/dev_battle_gui/resources")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS} ")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS} ${ASSETS} -s ASYNCIFY -s ASSERTIONS=1")
  set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

option(USE_IWYU "Should invoke Include-What-You-Use tool" FALSE)
option(DISABLE_ROS_TOOLING "Should disable ROS tooling" TRUE)

set(cmake_helpers_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake_helpers)
set(utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/utils)
set(resource_utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/resource_utils)
set(sdl_utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl_utils)
set(manager_utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/manager_utils)
set(game_engine_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/game_engine)

if(ASSET_BUILD)
  message("ASSET BUILD")
  add_subdirectory(${cmake_helpers_DIR})
  add_subdirectory(${utils_DIR})
  add_subdirectory(${resource_utils_DIR})
  add_subdirectory(tools)
  return()
endif()

# static libraries
add_subdirectory(${cmake_helpers_DIR})
add_subdirectory(${utils_DIR})
add_subdirectory(${resource_utils_DIR})
add_subdirectory(${sdl_utils_DIR})
add_subdirectory(${manager_utils_DIR})
add_subdirectory(${game_engine_DIR})

# executables
add_subdirectory(dev_battle_gui)
