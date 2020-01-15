//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_CONTROLLER_H
#define SMFL_TEST_CONTROLLER_H

#include <iostream>
#include "Entity.h"
#include "View.h"
#include "Subject.h"

class Controller: public Subject {



protected:

    std::shared_ptr<Entity> model;

public:

    Controller() = default;

    virtual int update(std::vector<std::unique_ptr<Controller>>& controller) = 0;

    [[nodiscard]] const std::shared_ptr<Entity> &getModel() const;

    virtual int moveLeft();

    virtual int moveRight();

    virtual int moveUp();

    virtual int moveDown();

    virtual int shoot(std::vector<std::unique_ptr<Controller>> &Controllers);

    virtual bool isOffScreen(float newX, float newY);

};


#endif //SMFL_TEST_CONTROLLER_H
