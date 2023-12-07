#Author Zhivko Petrov
cmake_minimum_required(VERSION 3.10.2)

project(
    dev_battle 
    LANGUAGES CXX
    VERSION 1.0.0
)

# Configurable CMake command line arguments
option(USE_IWYU "Should invoke Include-What-You-Use tool" FALSE)
option(DISABLE_ROS_TOOLING "Should disable ROS tooling" TRUE)

# Setup for static libs location
# The syntax ${lib}_DIR is utilized by the CMake find_package() functionality
set(cmake_helpers_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake_helpers)
set(utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/utils)
set(resource_utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/resource_utils)
set(sdl_utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl_utils)
set(manager_utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/manager_utils)
set(game_engine_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/game_engine)

# Support for Emscripten.
# TODO: consider moving the functionalition elsewhere
if(EMSCRIPTEN)
    set(EMSCRIPTEN_PORTS "\
        -s USE_SDL=2 \
        -s USE_SDL_TTF=2 \
        -s USE_SDL_MIXER=2 \
        -s USE_SDL_IMAGE=2 \
        -s SDL2_IMAGE_FORMATS='[png, jpg]' \
    ")
    set(ASSETS "--preload-file ${CMAKE_INSTALL_PREFIX}/dev_battle_gui/resources")
    set(LINKER_FLAGS "${ASSETS} -s ASYNCIFY=1")

    set(CMAKE_CXX_FLAGS 
        "${CMAKE_CXX_FLAGS} ${EMSCRIPTEN_PORTS}")
    set(CMAKE_EXE_LINKER_FLAGS 
        "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_PORTS} ${LINKER_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

# Consuming the cmake helpers will enable use of in-house CMake helper functions
add_subdirectory(${cmake_helpers_DIR})
find_package(cmake_helpers REQUIRED)

# Place binaries/dynamic libraries under  <build-dir>/bin
# Place archives (static libraries) under <build-dir>/lib
set_default_project_output_directories()

# The resource_builder binary is used to auto-generate asset meta information
# NOTE: ROS1/ROS2 does not work with a nested CMake structurre
set(resource_builder_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools/resource_builder)

# An ASSET_BUILD will only build the required functionality for the resource_builder application.
# Additionally it will generate assets for selected projects without building their source files.
if(ASSET_BUILD)
    add_subdirectory(${utils_DIR})
    add_subdirectory(${resource_utils_DIR})
    add_subdirectory(${resource_builder_DIR})

    # Partially process the executable to install it's assets
    add_subdirectory(dev_battle_gui)
    return()
endif()

# Static libraries
add_subdirectory(${utils_DIR})
add_subdirectory(${resource_utils_DIR})
add_subdirectory(${sdl_utils_DIR})
add_subdirectory(${manager_utils_DIR})
add_subdirectory(${game_engine_DIR})

# Executables
add_subdirectory(dev_battle_gui)
