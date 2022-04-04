#Author Zhivko Petrov
cmake_minimum_required(VERSION 3.10.2)

project(dev_battle)

option(USE_IWYU "Should invoke Include-What-You-Use tool" FALSE)
option(DISABLE_ROS_TOOLING "Should disable ROS tooling" TRUE)

set(cmake_helpers_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake_helpers)
set(utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/utils)
set(resource_utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/resource_utils)
set(sdl_utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl_utils)
set(manager_utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/manager_utils)
set(game_engine_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/game_engine)
set(resource_builder_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools/resource_builder)

# static libraries
add_subdirectory(${cmake_helpers_DIR})
add_subdirectory(${utils_DIR})
add_subdirectory(${resource_utils_DIR})
add_subdirectory(${sdl_utils_DIR})
add_subdirectory(${manager_utils_DIR})
add_subdirectory(${game_engine_DIR})

# tools
add_subdirectory(${resource_builder_DIR})

# executables
add_subdirectory(dev_battle_gui)
