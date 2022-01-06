#Author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

project(dev_battle_server)

set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
   
add_executable(
    ${PROJECT_NAME} 
        ${_SRC_DIR}/main.cpp
)

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE
        resource_utils
        manager_utils
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
    ln -sf server/${PROJECT_NAME} serverSymLink)
           
#move symbolic link to project build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND
    mv serverSymLink ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME})
    
    