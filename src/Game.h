//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_GAME_H
#define SMFL_TEST_GAME_H

#include "Controller.h"
#include "SFMLmanager.h"
#include "WorldController.h"
#include <iostream>

class Game
{

        std::shared_ptr<WorldController> currentLevel;
        std::shared_ptr<SFMLmanager> graphicsmanager;
        std::vector<std::shared_ptr<Controller>> controllers;

        int initGame();

public:
        explicit Game() = default;

        int run();

        int update();

        int fixNewEntities();

        int expiredRemove();

        int collisionChecks();

        int loadnextlevel();

        int render();
};

#endif // SMFL_TEST_GAME_H
