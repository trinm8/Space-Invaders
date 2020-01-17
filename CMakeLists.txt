cmake_minimum_required(VERSION 3.10)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 14)

include_directories(src src/entity src/patern src/entity/Player src/ExternalTools/nlohmann src/patern/Commands src/entity/Bullet src/Visual src/entity/Enemy src/entity/world)

if(WIN32)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

SET(SFML_ROOT ${PROJECT_SOURCE_DIR}/SFML)
#set(SFML_STATIC_LIBRARIES TRUE)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SFML_ROOT}/cmake/Modules/)
#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package (SFML REQUIRED COMPONENTS system graphics window audio)

#add_library(SFMLwindow ${PROJECT_SOURCE_DIR}/SFML/bin/sfml-window-d-2.dll)

include_directories(${SFML_INCLUDE_DIR})

endif(WIN32)



if(UNIX)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/LinuxBin)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics audio)

INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
endif(UNIX)

add_executable(SpaceInvaders src/main.cpp src/Game.cpp src/Game.h src/entity/Entity.cpp src/entity/Entity.h src/entity/Controller.cpp src/entity/Controller.h src/entity/world/WorldController.cpp src/entity/world/WorldController.h src/entity/View.cpp src/entity/View.h src/patern/Observer.h src/patern/Subject.cpp src/patern/Subject.h src/entity/Player/ControllerPlayer.cpp src/entity/Player/ControllerPlayer.h src/Visual/SFMLmanager.cpp src/Visual/SFMLmanager.h src/Events.h src/ExternalTools/nlohmann/json.hpp src/Visual/Transformation.cpp src/Visual/Transformation.h src/Defines.h src/patern/Stopwatch.cpp src/patern/Stopwatch.h src/entity/Bullet/ControllerBullet.cpp src/entity/Bullet/ControllerBullet.h src/Hitbox.cpp src/Hitbox.h src/entity/Enemy/ControllerEnemy.cpp src/entity/Enemy/ControllerEnemy.h src/entity/Enemy/EntityEnemy.cpp src/entity/Enemy/EntityEnemy.h)

TARGET_LINK_LIBRARIES(SpaceInvaders ${SFML_LIBRARIES})
#target_link_libraries(test SFMLwindow)
#target_link_libraries(test ${PROJECT_SOURCE_DIR}/SFML/bin/sfml-window-d-2.dll)
#target_link_directories("${PROJECT_SOURCE_DIR}/SFML/bin/")
if(UNIX)
INSTALL(TARGETS SpaceInvaders DESTINATION ${PROJECT_SOURCE_DIR}/LinuxBin)
endif(UNIX)

if(WIN32)
install(TARGETS SpaceInvaders DESTINATION ${PROJECT_SOURCE_DIR}/bin)
endif(WIN32)