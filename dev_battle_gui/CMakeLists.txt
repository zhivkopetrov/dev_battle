#Author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

project(dev_battle_gui)

set(_INC_FOLDER_NAME include)
set(_RESOURCE_FOLDER_NAME resources)
set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}/${PROJECT_NAME})
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
   
add_executable(
    ${PROJECT_NAME} 
        ${_INC_DIR}/DevBattleGui.h
        ${_INC_DIR}/config/GuiConfig.h
        ${_INC_DIR}/defines/GuiDefines.h
        ${_INC_DIR}/field/Field.h
        ${_INC_DIR}/field/Tile.h
        ${_INC_DIR}/field/config/FieldConfig.h
        ${_INC_DIR}/field/config/TileConfig.h
        ${_INC_DIR}/field/units/config/UnitConfig.h
        ${_INC_DIR}/field/units/basic/Unit.h
     
        ${_SRC_DIR}/main.cpp
        ${_SRC_DIR}/DevBattleGui.cpp
        ${_SRC_DIR}/defines/GuiDefines.cpp
        ${_SRC_DIR}/field/Field.cpp
        ${_SRC_DIR}/field/Tile.cpp
        ${_SRC_DIR}/field/units/basic/Unit.cpp
)

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE
        $<BUILD_INTERFACE:
            ${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}
            ${CMAKE_CURRENT_SOURCE_DIR}/${_RESOURCE_FOLDER_NAME}
        >
        $<INSTALL_INTERFACE:
            ${_INC_FOLDER_NAME}
            ${_RESOURCE_FOLDER_NAME}
        >
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE
        game_engine::game_engine
)

set_target_cpp_standard(${PROJECT_NAME} 20)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})
#enable_target_sanitizer(${PROJECT_NAME} "memory")

# Install resources and auto-generated headers and resource bin filles
install(
    DIRECTORY ${_RESOURCE_FOLDER_NAME}/
    DESTINATION ${PROJECT_NAME}/${_RESOURCE_FOLDER_NAME}
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
    ln -sf ${PROJECT_NAME}/${PROJECT_NAME} guiSymLink)
           
#move symbolic link to project build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND
    mv guiSymLink ${CMAKE_SOURCE_DIR}/build/gui)
    
    