//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_GAME_H
#define SMFL_TEST_GAME_H

#include "Controller.h"
#include "SFMLmanager.h"
#include "LevelController.h"
#include <iostream>

class Game
{
        /*! \class Game
         *  The gameclass is the main framework keeping all the components of the game together. It consists of the
         *  variables currentlevel which is a pointer to the currently playing level, a pointer to the graphics manager,
         *  the graphics manager is responsible for updating all the visual parts of our game. Lastly the controllers is
         *  a list of all the controllers currently running in the game. The game has no idea which kind of controllers
         *  these are, it only updates them and makes interaction between them possible.
         */

        std::shared_ptr<LevelController> currentLevel;
        std::shared_ptr<SFMLmanager> graphicsmanager;
        std::vector<std::shared_ptr<Controller>> controllers; //!< the vector with all the controllers that are in game

        /*!
         * Initializes the first level of the game
         */
        int initGame();

        /*!
         * the main game loop, this will itterate over all the controllers, update them and lastly render them
         */
        int update();

        /*!
         * if there are new entities created by the currently existing controllers they will not have a proper
         * connection to the visual side of the game. This function will add the graphicsmanager as an observer
         */
        int fixNewEntities();

        /*!
         * if there are controllers that are no longer valid (i.e. killed/outofbounds) the game class will remove them
         * the game
         */
        int expiredRemove();

        /*!
         * the collision checker will loop over all the controllers and check if there are any collisions between them.
         * This is done by a simple intersection check between hitboxes and followed by a functioncall to the affected
         * controllers to handle the collision
         */
        int collisionChecks();

        /*!
         * if the level current level is finished this function will initiate the next level
         */
        int loadnextlevel();

        /*!
         * makes a function call to graphics manager to start rendering the new game state
        */
        int render();

public:
        explicit Game() = default;

        /*!
         * the main game loop to update the state of the game. It is implemented with the idea that when the CPU starts
         * lagging behind it starts by updating the logic more often (and waiting to render) so the CPU can catch up. We
         * then deltatime which is a normalized value to make sure our graphics don't stutter.
         */
        int run();
};

#endif // SMFL_TEST_GAME_H
