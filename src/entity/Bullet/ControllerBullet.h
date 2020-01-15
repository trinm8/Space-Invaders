//
// Created by timsa on 26-Dec-19.
//

#ifndef SMFL_TEST_CONTROLLERBULLET_H
#define SMFL_TEST_CONTROLLERBULLET_H

#include "Controller.h"

class ControllerBullet: public Controller {

public:
    ControllerBullet(float posX, float posY);

    int update(std::vector<std::unique_ptr<Controller>>& controller) override;

    int moveUp() override;
};


#endif //SMFL_TEST_CONTROLLERBULLET_H
