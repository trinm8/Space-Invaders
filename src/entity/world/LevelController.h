//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_WORLDCONTROLLER_H
#define SMFL_TEST_WORLDCONTROLLER_H

#include "Controller.h"
#include "ControllerEnemy.h"
#include "ControllerPlayer.h"

class LevelController : public Controller
{
        /*!
         * This controller keeps track of the state of the current level, you could say its a controller that uses other
         * controllers as models. Its purpose is to keep track of what the state is of important entities in the game at
         * the moment, BUT DOES NOT UPDATE THEM that is the job of the game class.
         */
        std::shared_ptr<ControllerPlayer> currentPlayer;
        std::shared_ptr<ControllerEnemy> currentEnemies;
        int levelnr;
        bool last; /*!< keeps track if its the last level so it can generate a game over*/

public:
        /*!
         * @param sfmLmanager The visual component for the background of the level, Not implemented yet
         */
        explicit LevelController(const std::shared_ptr<Observer>& sfmLmanager);

        /*!
         * Make the level ready to be played by adding all the needed entities.
         * @param controllers The list of controllers so all created entities reach the game class
         * @param SFMLmanager The SFMLmanager that will render all the entities
         * @param expectedLevelNr The current level we are on.
         * @return reserved for future exception handling
         */
        int initLevel(std::vector<std::shared_ptr<Controller>>& controllers,
                      const std::shared_ptr<Observer>& SFMLmanager, int expectedLevelNr);

        int update(std::vector<std::shared_ptr<Controller>>& controller) override;

        /*!
         * The idea of the collision itself was to make the background itself a hazard but this hasnt been implemented yet
         * @param other the other object it collided with.
         */
        int onCollision(Controller& other) override;

        bool LevelComplete();

        bool gameOver();

        [[nodiscard]] int getLevelnr() const;

        bool isLast() const;

        /*!
         * This will remove all the important entities from the current level so it can load the next for example.
         */
        int close();
};

#endif // SMFL_TEST_WORLDCONTROLLER_H
