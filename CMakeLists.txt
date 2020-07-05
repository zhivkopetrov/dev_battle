#Author Zhivko Petrov
cmake_minimum_required(VERSION 3.10.2)

project(dev_battle)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)
set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)
set(CMAKE_HELPERS_INCLUDED TRUE)

# static libraries
add_subdirectory(utils)
add_subdirectory(resource_utils)
add_subdirectory(sdl_utils)
add_subdirectory(manager_utils)

# tools
add_subdirectory(tools)

# executables
add_subdirectory(server)
add_subdirectory(gui)
