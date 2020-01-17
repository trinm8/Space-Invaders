//
// Created by timsa on 14-Jan-20.
//

#ifndef SMFL_TEST_CONTROLLERENEMY_H
#define SMFL_TEST_CONTROLLERENEMY_H

#include "Controller.h"
#include "EntityEnemy.h"

class ControllerEnemy : public Controller
{
        /*! \class ControllerEnemy
         *  This controller will manage not a single entity but rather all the individual enemies in our game. The way
         * it does this is by keeping a linked chain of EntityEnemy objects. It will iterate over these to get and
         * change data, this way we can simulate multiple entities who all move together and behave the same. If there
         * are override functions from the superclass Controller its because these Entities all need to be updated
         * except just one.
         */

        std::shared_ptr<EntityEnemy> start;

        int timebetweenshots;

        /*!
         * When an enemy wants to fire we need to check that it doesnt accidentally shoots one of its buddies, this is
         * done by looking if there is an enemy on the same x position but on a lower y level.
         * @param toCheck The current enemy we want to check
         * @return
         */
        bool enemyinfront(const std::shared_ptr<EntityEnemy>& toCheck);

        bool reachedEdge();

        void lowerLevel();

        std::vector<std::shared_ptr<EntityEnemy>> getShootReadyEnemies();

public:
        ControllerEnemy(int enemyCount, const std::shared_ptr<Observer>& SFMLmanager,
                        const std::string& textureLocation);

        int update(std::vector<std::shared_ptr<Controller>>& controller) override;

        /*!
         * Works the same way as the controllers collision only we check every EntityEnemy instead of just a single
         * Entity.
         * @param otherController the other colliding object
         * @return if there is a collision
         */
        bool collides(Controller& otherController) override;

        void removeEnemy();

        /*!
         * Returns the number of enemies that are alive not the actual size of the the enemy.
         * @return the amount of enemies that are currently alive (aka the size of the chain).
         */
        int getEnemysize();

        int onCollision(Controller& other) override;

        float getlowestY();

        void setLives(int lives) override;
};

#endif // SMFL_TEST_CONTROLLERENEMY_H
