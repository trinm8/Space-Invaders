//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_GAME_H
#define SMFL_TEST_GAME_H

#include <iostream>
#include "Controller.h"
#include "WorldController.h"
#include "SFMLmanager.h"

class Game {

   std::shared_ptr<WorldController> currentLevel;
   std::shared_ptr<SFMLmanager> graphicsmanager;
   std::vector<std::shared_ptr<Controller>> controllers;


   int initGame();

public:

    Game();

    int run();

    int update();

    bool offscreen(float posX, float posY);

    int fixNewEntities();

    int expiredRemove();

    int collisionChecks();

    int loadnextlevel();

};


#endif //SMFL_TEST_GAME_H
