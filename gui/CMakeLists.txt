#Author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

project(dev_battle_gui)

set(_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
   
add_executable(
    ${PROJECT_NAME} 
        ${_INCLUDE_DIR}/engine/Engine.h
        ${_INCLUDE_DIR}/engine/DebugConsole.h
        ${_INCLUDE_DIR}/engine/config/EngineConfig.hpp
        ${_INCLUDE_DIR}/managers/config/ManagerHandlerConfig.hpp
        ${_INCLUDE_DIR}/managers/ManagerHandler.h
        ${_INCLUDE_DIR}/managers/DrawMgr.h
        ${_INCLUDE_DIR}/managers/RsrcMgr.h
        ${_INCLUDE_DIR}/managers/TimerMgr.h
        ${_INCLUDE_DIR}/game/Game.h
        ${_INCLUDE_DIR}/game/config/GameConfig.hpp
        ${_INCLUDE_DIR}/game/defines/GameDefines.h
        ${_INCLUDE_DIR}/game/field/Field.h
        ${_INCLUDE_DIR}/game/field/Tile.h
        ${_INCLUDE_DIR}/game/field/config/FieldConfig.hpp
        ${_INCLUDE_DIR}/game/field/config/TileConfig.hpp
        ${_INCLUDE_DIR}/game/units/defines/UnitDefines.h
        ${_INCLUDE_DIR}/game/units/config/UnitConfig.hpp
        ${_INCLUDE_DIR}/game/units/factory/UnitFactory.h
        ${_INCLUDE_DIR}/game/units/basic/config/BasicUnitConfig.hpp
        ${_INCLUDE_DIR}/game/units/basic/defines/BasicUnitDefines.h
        ${_INCLUDE_DIR}/game/units/basic/Unit.h
        ${_INCLUDE_DIR}/game/units/hero/config/HeroConfig.hpp
        
    
        ${_SRC_DIR}/main.cpp
        ${_SRC_DIR}/engine/Engine.cpp
        ${_SRC_DIR}/engine/DebugConsole.cpp
        ${_SRC_DIR}/managers/ManagerHandler.cpp
        ${_SRC_DIR}/managers/DrawMgr.cpp
        ${_SRC_DIR}/managers/RsrcMgr.cpp
        ${_SRC_DIR}/managers/TimerMgr.cpp
        ${_SRC_DIR}/game/Game.cpp
        ${_SRC_DIR}/game/defines/GameDefines.cpp
        ${_SRC_DIR}/game/field/Field.cpp
        ${_SRC_DIR}/game/field/Tile.cpp
        ${_SRC_DIR}/game/units/factory/UnitFactory.cpp
        ${_SRC_DIR}/game/units/basic/Unit.cpp
)

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE
        utils
        resource_utils
        sdl_utils
        manager_utils
)

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE
        include
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
    
    