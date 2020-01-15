cmake_minimum_required(VERSION 3.13)
project(SMFL_test)

set(CMAKE_CXX_STANDARD 17)

include_directories(src src/entity src/patern src/entity/Player src/ExternalTools src/patern/Commands src/entity/Bullet src/Visual)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

SET(SFML_ROOT ${PROJECT_SOURCE_DIR}/SFML)
#set(SFML_STATIC_LIBRARIES TRUE)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SFML_ROOT}/cmake/Modules/)
#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package (SFML REQUIRED COMPONENTS system graphics window audio)

#add_library(SFMLwindow ${PROJECT_SOURCE_DIR}/SFML/bin/sfml-window-d-2.dll)

include_directories(${SFML_INCLUDE_DIR})

add_executable(test src/main.cpp src/Game.cpp src/Game.h src/entity/Entity.cpp src/entity/Entity.h src/entity/world/World.cpp src/entity/world/World.h src/entity/Controller.cpp src/entity/Controller.h src/entity/world/WorldController.cpp src/entity/world/WorldController.h src/entity/world/WorldView.cpp src/entity/world/WorldView.h src/entity/View.cpp src/entity/View.h src/patern/Observer.cpp src/patern/Observer.h src/patern/Subject.cpp src/patern/Subject.h src/entity/Player/EntityPlayer.cpp src/entity/Player/EntityPlayer.h src/entity/Player/ControllerPlayer.cpp src/entity/Player/ControllerPlayer.h src/entity/Player/ViewPlayer.cpp src/entity/Player/ViewPlayer.h src/Visual/SFMLmanager.cpp src/Visual/SFMLmanager.h src/Events.h src/ExternalTools/nlohmann/json.hpp src/patern/Command.cpp src/patern/Command.h src/patern/Commands/MoveLeftCommand.cpp src/patern/Commands/MoveLeftCommand.h src/InputHandler.cpp src/InputHandler.h src/patern/Commands/MoveRightCommand.cpp src/patern/Commands/MoveRightCommand.h src/Visual/Transformation.cpp src/Visual/Transformation.h src/Defines.h src/patern/Commands/MoveUpCommand.cpp src/patern/Commands/MoveUpCommand.h src/patern/Stopwatch.cpp src/patern/Stopwatch.h src/entity/Bullet/EntityBullet.cpp src/entity/Bullet/EntityBullet.h src/entity/Bullet/ControllerBullet.cpp src/entity/Bullet/ControllerBullet.h src/Hitbox.cpp src/Hitbox.h src/entity/Enemy/ControllerEnemy.cpp src/entity/Enemy/ControllerEnemy.h src/entity/Enemy/EntityEnemy.cpp src/entity/Enemy/EntityEnemy.h)

target_link_libraries(test ${SFML_LIBRARIES})
#target_link_libraries(test SFMLwindow)
#target_link_libraries(test ${PROJECT_SOURCE_DIR}/SFML/bin/sfml-window-d-2.dll)
#target_link_directories("${PROJECT_SOURCE_DIR}/SFML/bin/")

install(TARGETS test DESTINATION ${PROJECT_SOURCE_DIR}/bin)