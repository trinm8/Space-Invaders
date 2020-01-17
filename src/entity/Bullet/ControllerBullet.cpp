//
// Created by timsa on 26-Dec-19.
//

#include "ControllerBullet.h"

ControllerBullet::ControllerBullet(float posX, float posY, int direction)
{
        model = std::make_shared<Entity>();
        model->setHitbox(Hitbox(0.02, 0.1));
        model->setX(posX);
        // we have to make sure the bullet doesnt spawn in the object that shot it
        model->setY(posY + (model->getHitbox().getH() / 2) * (float)direction);
        model->setLives(1);
        model->setDeadly(true);
        model->setDirectionY(direction);
        model->setSpeedY(0.005f);
        model->setScreenlocked(false);
        model->setTextureLocation("Assests/bullet.png");
        needsObserver = true;
}

int ControllerBullet::update(std::vector<std::shared_ptr<Controller>>& controller)
{
        moveVertical();
        if (isOffScreen(model->getX(), model->getY())) {
                makeExpired();
        }
        return 0;
}

int ControllerBullet::onCollision(Controller& other)
{
        expired = true;
        notify(*this, Events::expired);
        return 0;
}
