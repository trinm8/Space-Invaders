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

    bool expired;

    int direction;

    std::shared_ptr<Entity> model;

    bool needsObserver;

public:

    Controller();

    Controller(std::shared_ptr<Observer> SFMLmanager);

    virtual int update(std::vector<std::shared_ptr<Controller>>& controller) = 0;

    [[nodiscard]] const std::shared_ptr<Entity> &getModel() const;

    int moveHorizontal();

    int moveVertical();

    virtual int shoot(std::vector<std::shared_ptr<Controller>> &Controllers);

    virtual bool isOffScreen(float X, float Y);

    virtual void setPos(float x, float y);

    bool isExpired() const;

    void makeExpired();

    Hitbox getHitbox();

    std::pair<float, float> getHitboxLeftCorner();

    std::pair<float, float> getHitboxRightCorner();

    virtual bool collides(Controller& otherController);

    bool isDeadly();

    int takeDamage(int value);

    virtual int onCollision(Controller& other) = 0;

    virtual ~Controller();

    bool hasObserver();

    void gotObserver();

    int getLives() const;

};


#endif //SMFL_TEST_CONTROLLER_H
