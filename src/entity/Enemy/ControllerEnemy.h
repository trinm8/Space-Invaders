//
// Created by timsa on 14-Jan-20.
//

#ifndef SMFL_TEST_CONTROLLERENEMY_H
#define SMFL_TEST_CONTROLLERENEMY_H

#include "Controller.h"
#include "EntityEnemy.h"

class ControllerEnemy: public Controller {

    std::shared_ptr<EntityEnemy> start;

public:

    ControllerEnemy(int enemyCount, Observer& SFMLmanager);

    int update(std::vector<std::unique_ptr<Controller>> &controller) override;

    bool reachedEdge();

    void lowerLevel();

    bool collides(Controller& otherController);

    void removeEnemy();

    int getEnemysize();

    int onCollision(Controller &other) override;
};


#endif //SMFL_TEST_CONTROLLERENEMY_H
