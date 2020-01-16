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
    int lives;
    bool deadly;
    float speedY;
    float speedX;
    int directionY;
    int directionX;
    bool screenlocked;


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

    int getLives() const;

    void setLives(int lives);

    bool isDeadly() const;

    void setDeadly(bool deadly);

    float getSpeedY() const;

    void setSpeedY(float speedY);

    int getDirectionY() const;

    void setDirectionY(int directionY);

    float getSpeedX() const;

    void setSpeedX(float speedX);

    int getDirectionX() const;

    void setDirectionX(int directionX);

    bool isScreenlocked() const;

    void setScreenlocked(bool screenlocked);

};


#endif //SMFL_TEST_ENTITY_H
