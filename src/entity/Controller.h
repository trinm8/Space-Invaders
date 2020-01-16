//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_CONTROLLER_H
#define SMFL_TEST_CONTROLLER_H

#include "Entity.h"
#include "Subject.h"
#include "View.h"
#include "Hitbox.h"
#include <iostream>

class Controller : public Subject
{

protected:
        bool expired;

        int direction{};

        std::shared_ptr<Entity> model;

        bool needsObserver;

public:
        Controller();

        explicit Controller(const std::shared_ptr<Observer>& SFMLmanager);

        virtual int update(std::vector<std::shared_ptr<Controller>>& controller) = 0;

        [[nodiscard]] const std::shared_ptr<Entity>& getModel() const;

        int moveHorizontal();

        int moveVertical();

        virtual int shoot(std::vector<std::shared_ptr<Controller>>& Controllers);

        virtual bool isOffScreen(float X, float Y);

        bool isExpired() const;

        void makeExpired();

        Hitbox& getHitbox();

        std::pair<float, float> getHitboxLeftCorner();

        std::pair<float, float> getHitboxRightCorner();

        virtual bool collides(Controller& otherController);

        bool isDeadly();

        int takeDamage(int value);

        virtual int onCollision(Controller& other) = 0;

        ~Controller() override;

        bool hasObserver();

        void gotObserver();

        int getLives() const;

        virtual void setTextureLocation(const std::string& location);
};

#endif // SMFL_TEST_CONTROLLER_H
