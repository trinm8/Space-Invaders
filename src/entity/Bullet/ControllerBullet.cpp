//
// Created by timsa on 26-Dec-19.
//

#include "ControllerBullet.h"
#include "EntityBullet.h"

ControllerBullet::ControllerBullet(float posX, float posY, int direction){
    model = std::make_unique<EntityBullet>();
    model->setHitbox(Hitbox(0.01, 0.01));
    model->setX(posX);
    model->setY(posY);
    model->setLives(1);
    model->setDeadly(true);
    model->setDirectionY(direction);
    model->setSpeedY(0.1f);
}

int ControllerBullet::update(std::vector<std::unique_ptr<Controller>>& controller) {
    moveVertical();
    if(isOffScreen(model->getX(), model->getY())){
        makeExpired();
    }
    return 0;
}

int ControllerBullet::onCollision(Controller &other) {
    expired = true;
    notify(*this, Events::Expired);
    return 0;
}
