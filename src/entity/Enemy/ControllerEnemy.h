//
// Created by timsa on 14-Jan-20.
//

#ifndef SMFL_TEST_CONTROLLERENEMY_H
#define SMFL_TEST_CONTROLLERENEMY_H

#include "Controller.h"
#include "EntityEnemy.h"

class ControllerEnemy: public Controller {

public:

    ControllerEnemy(int enemyCount, Observer& SFMLmanager);

    int update(std::vector<std::unique_ptr<Controller>> &controller) override;
};


#endif //SMFL_TEST_CONTROLLERENEMY_H
