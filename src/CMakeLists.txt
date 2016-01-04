#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(myproject)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# Set version information in a config.h file
set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wall -Wextra -Wno-unused -pedantic")

set(ENGINE_NAME "engine")
add_library(${ENGINE_NAME}
    seal/IDList.cpp
    seal/world.cpp
    seal/entity.cpp
    seal/mouseeventhandler.cpp
    seal/entitygroup.cpp
    seal/line.cpp
    seal/vec2f.cpp
    seal/platform.cpp
    seal/particleeffect.cpp
    seal/pathnode.cpp
    seal/pathfinder.cpp
    seal/systems/System.cpp
    seal/components/DrawableComponent.cpp
    seal/components/TransformComponent.cpp
    seal/components/Component.cpp
    seal/systems/DrawingSystem.cpp
    seal/LightManager.cpp
    seal/Light.cpp
)

set(LIB_NAME "SharedCode")
add_library(${LIB_NAME}
    zui/uicomponent.cpp
    zui/window.cpp
    zui/inputcomponent.cpp
    zui/button.cpp
    zui/textbutton.cpp
    zui/imglistelement.cpp
    zui/imglist.cpp

    components/SpriteComponent.cpp
    components/PhysicsComponent.cpp
    components/ShapeComponent.cpp
    components/PlatformComponent.cpp
    components/ShaderComponent.cpp
    components/SpriteShaderComponent.cpp
    components/GroundComponent.cpp
    components/LightComponent.cpp

    systems/PhysicsSystem.cpp
    systems/KeyboardSystem.cpp
    systems/PlatformSystem.cpp
)

# Define sources and executable
set(EXECUTABLE_NAME "myproject")
add_executable(${EXECUTABLE_NAME} 
    #Include for directory support on windows
    #depend/dirent.h
    main.cpp 
    game.cpp
    )
# Define sources and executable
set(ANIM_EDITOR_NAME "animEditor")
set(ANIM_SOURCES
    #Include for directory support on windows
    #depend/dirent.h
    animmain.cpp
    animeditor.cpp
    )


# Detect and add SFML
set(CMAKE_MODULE_PATH "/usr/local/share/SFML/cmake/Modules/")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(${EXECUTABLE_NAME} ${LIB_NAME} ${ENGINE_NAME})
# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)
