#Author Zhivko Petrov
cmake_minimum_required(VERSION 3.10.2)

project(dev_battle)

include(${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake_helpers/helpers.cmake)
set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake_helpers/find_modules)

# static libraries
add_subdirectory(lib/utils)
add_subdirectory(lib/resource_utils)
add_subdirectory(lib/sdl_utils)
add_subdirectory(lib/manager_utils)

# tools
add_subdirectory(tools)

# executables
add_subdirectory(gui)
