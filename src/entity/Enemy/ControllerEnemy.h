//
// Created by timsa on 14-Jan-20.
//

#ifndef SMFL_TEST_CONTROLLERENEMY_H
#define SMFL_TEST_CONTROLLERENEMY_H

#include "Controller.h"
#include "EntityEnemy.h"

class ControllerEnemy : public Controller
{

        std::shared_ptr<EntityEnemy> start;

        int timebetweenshots;

public:
        ControllerEnemy(int enemyCount, const std::shared_ptr<Observer> &SFMLmanager,
                        const std::string &textureLocation);

        int update(std::vector<std::shared_ptr<Controller>>& controller) override;

        bool reachedEdge();

        void lowerLevel();

        bool collides(Controller& otherController) override;

        void removeEnemy();

        int getEnemysize();

        int onCollision(Controller& other) override;

        bool enemyinfront(const std::shared_ptr<EntityEnemy>& toCheck);

        std::vector<std::shared_ptr<EntityEnemy>> getShootReadyEnemies();

        float getlowestY();

    void setTextureLocation(const std::string &location) override;
};

#endif // SMFL_TEST_CONTROLLERENEMY_H
