//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_ENTITY_H
#define SMFL_TEST_ENTITY_H

#include "Controller.h"
#include "Hitbox.h"
#include <memory>

class Controller;

class Entity
{
        /*! \class Entity
         *  The Entity class will keep track of all the data that the controller uses to update and function in the
         * game.
         */
        float x, y;
        Hitbox hitbox;
        double fireCooldown; /*!< A cooldown timer for shooting */
        int lives;
        bool deadly;
        float speedY;
        float speedX;
        int directionY;
        int directionX;
        bool screenlocked; /*!< Is the entity allowed to go offscreen */
        std::string textureLocation;

public:
        double getFireCooldown() const;

        void setFireCooldown(double fireCooldown);

        /*!
         * Makes the shooting cooldown goes down by a tick.
         * @param percent this is to make the counting go slower or faster. (Not really implemented yet)
         */
        void FireCooldownTick(double percent);

        void setHitbox(const Hitbox& hitbox);

        float getX() const;

        float getY() const;

        void setX(float x);

        void setY(float y);

        Hitbox& getHitbox();

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

        const std::string& getTextureLocation() const;

        void setTextureLocation(const std::string& textureLocation);
};

#endif // SMFL_TEST_ENTITY_H
