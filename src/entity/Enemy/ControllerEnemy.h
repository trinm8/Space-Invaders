//
// Created by timsa on 14-Jan-20.
//

#ifndef SMFL_TEST_CONTROLLERENEMY_H
#define SMFL_TEST_CONTROLLERENEMY_H

#include "Controller.h"
#include "EntityEnemy.h"

class ControllerEnemy: public Controller {

    std::shared_ptr<EntityEnemy> start;

    int maxfiring;

    int timebetweenshots;

public:

    ControllerEnemy(int enemyCount, std::shared_ptr<Observer> SFMLmanager, int lives);

    int update(std::vector<std::shared_ptr<Controller>> &controller) override;

    bool reachedEdge();

    void lowerLevel();

    bool collides(Controller& otherController);

    void removeEnemy();

    int getEnemysize();

    int onCollision(Controller &other) override;

    bool enemyinfront(std::shared_ptr<EntityEnemy> toCheck);

    std::vector<std::shared_ptr<EntityEnemy>> getShootReadyEnemies();

    float getlowestY();
};


#endif //SMFL_TEST_CONTROLLERENEMY_H
