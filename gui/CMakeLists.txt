#Author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

project(dev_battle_gui)

set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
   
add_executable(
    ${PROJECT_NAME} 
        ${_INC_DIR}/engine/Engine.h
        ${_INC_DIR}/engine/DebugConsole.h
        ${_INC_DIR}/engine/config/EngineConfig.hpp
        ${_INC_DIR}/game/Game.h
        ${_INC_DIR}/game/config/GameConfig.hpp
        ${_INC_DIR}/game/defines/GameDefines.h
        ${_INC_DIR}/game/field/Field.h
        ${_INC_DIR}/game/field/Tile.h
        ${_INC_DIR}/game/field/config/FieldConfig.hpp
        ${_INC_DIR}/game/field/config/TileConfig.hpp
        ${_INC_DIR}/game/field/units/config/UnitConfig.hpp
        ${_INC_DIR}/game/field/units/basic/Unit.h
    
        ${_SRC_DIR}/main.cpp
        ${_SRC_DIR}/engine/Engine.cpp
        ${_SRC_DIR}/engine/DebugConsole.cpp
        ${_SRC_DIR}/game/Game.cpp
        ${_SRC_DIR}/game/defines/GameDefines.cpp
        ${_SRC_DIR}/game/field/Field.cpp
        ${_SRC_DIR}/game/field/Tile.cpp
        ${_SRC_DIR}/game/field/units/basic/Unit.cpp
)

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})
#enable_target_sanitizer(${PROJECT_NAME} "memory")

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE
        manager_utils
)

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#invoke include-what-you-use (if it's enabled) for the current project
if(USE_IWYU)
    enable_target_include_what_you_use(${PROJECT_NAME})
endif(USE_IWYU)

#generate symbolic link for resourceBuilder after build is ready
#also add the -f (--force) command in order to
#override the existing symbolic link (if any)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND
    ln -sf gui/${PROJECT_NAME} guiSymLink)
           
#move symbolic link to project build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND
    mv guiSymLink ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME})
    
    