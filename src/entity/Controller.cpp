//
// Created by timsa on 04-Dec-19.
//

#include "Controller.h"

#include "ControllerBullet.h"
#include "Defines.h"
#include <utility>

Controller::Controller(const std::shared_ptr<Observer>& SFMLmanager)
{
        expired = false;
        needsObserver = false;
        direction = 0;
        addObserver(SFMLmanager);
}

const std::shared_ptr<Entity>& Controller::getModel() const { return model; }

/*
 * We check if we are outside of the current bounds of the game. This is predetermined at the moment because there
 * isnt a way yet to change the game size
 */
bool Controller::isOffScreen(float X, float Y)
{

        return (0 < Y + (model->getHitbox().getH() / 2) || Y - (model->getHitbox().getH() / 2) < -MaxLogicY) ||
               (0 > X - (model->getHitbox().getW() / 2) || X + (model->getHitbox().getW() / 2) > MaxLogicX);
}

/*
 * we first check if the countdown is 0 which marks if we are allowed to shoot.
 * Next we make an enemy controller and give it a position above the current postion so it would hit the entity that
 * shot it. We tell the graphics that a new view has to be made.
 * We then start the cooldown timer to make sure we cant keep shooting in rapid succesion.
 */
int Controller::shoot(std::vector<std::shared_ptr<Controller>>& Controllers)
{
        if (model->getFireCooldown() != 0)
                return 0;
        std::shared_ptr<ControllerBullet> bullet = std::make_shared<ControllerBullet>(
            model->getX(),
            model->getY() + (model->getSpeedY() + model->getHitbox().getH() * (float)model->getDirectionY()),
            model->getDirectionY());
        notify(*bullet, Events::event::createView);
        Controllers.push_back(std::move(bullet));
        model->setFireCooldown(400);
        return 0;
}

bool Controller::isExpired() const { return expired; }

void Controller::makeExpired()
{
        expired = true;
        notify(*this, Events::event::expired);
}

Hitbox& Controller::getHitbox() { return model->getHitbox(); }

std::pair<float, float> Controller::getHitboxLeftCorner()
{
        return {model->getX() - getHitbox().getW() / 2, model->getY() + getHitbox().getH() / 2};
}

std::pair<float, float> Controller::getHitboxRightCorner()
{
        return {model->getX() + getHitbox().getW() / 2, model->getY() - getHitbox().getH() / 2};
}

bool Controller::collides(Controller& otherController)
{
        std::pair<float, float> cornerL1 = getHitboxLeftCorner();
        std::pair<float, float> cornerL2 = otherController.getHitboxLeftCorner();
        std::pair<float, float> cornerR1 = getHitboxRightCorner();
        std::pair<float, float> cornerR2 = otherController.getHitboxRightCorner();

        return !((cornerL1.first > cornerR2.first || cornerL2.first > cornerR1.first) ||
                 (cornerR1.second > cornerL2.second || cornerL1.second < cornerR2.second));
}

bool Controller::isDeadly() { return model->isDeadly(); }

int Controller::takeDamage(int value)
{
        model->setLives(model->getLives() - value);
        return 0;
}

int Controller::moveVertical()
{
        float newY =
            model->getY() + (model->getSpeedY() * (float)model->getDirectionY());
        if (model->isScreenlocked() && isOffScreen(model->getX(), newY))
                return 0;
        model->setY(newY);
        return 0;
}

int Controller::moveHorizontal()
{
        float newX =
            model->getX() + (model->getSpeedX() * (float)model->getDirectionX());
        if (model->isScreenlocked() && isOffScreen(newX, model->getY()))
                return 0;
        model->setX(newX);
        return 0;
}

bool Controller::hasObserver() { return !needsObserver; }

void Controller::gotObserver() { needsObserver = false; }

int Controller::getLives() const { return model->getLives(); }

Controller::~Controller()
{
        expired = true;
        notify(*this, Events::event::expired);
}

Controller::Controller()
{
        expired = false;
        needsObserver = true;
}

void Controller::setLives(int lives) {
        model->setLives(lives);
}
