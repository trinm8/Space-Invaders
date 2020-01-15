//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_ENTITY_H
#define SMFL_TEST_ENTITY_H

#include <memory>
#include "Hitbox.h"
#include "Controller.h"

class Controller;

class Entity {

    float x, y;
    Hitbox hitbox;
    double fireCooldown;

public:
    double getFireCooldown() const;

    void setFireCooldown(double fireCooldown);

    void FireCooldownTick(double percent);

    void setHitbox(const Hitbox &hitbox);

    float getX() const;

    float getY() const;

    void setX(float x);

    void setY(float y);

    Hitbox &getHitbox();

};


#endif //SMFL_TEST_ENTITY_H
