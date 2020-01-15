//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_GAME_H
#define SMFL_TEST_GAME_H

#include <iostream>
#include "Controller.h"
#include "SFMLmanager.h"

class Game {

   std::unique_ptr<Controller> currentLevel;
   SFMLmanager graphicsmanager;
   std::vector<std::unique_ptr<Controller>> controllers;


   int initGame(SFMLmanager& manager);

public:

    Game();

    int run();

    int update();

    bool offscreen(float posX, float posY);

};


#endif //SMFL_TEST_GAME_H
