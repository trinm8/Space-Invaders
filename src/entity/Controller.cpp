//
// Created by timsa on 04-Dec-19.
//

#include "Controller.h"
#include "ControllerBullet.h"
#include "Defines.h"

const std::shared_ptr<Entity> &Controller::getModel() const {
    return model;
}

int Controller::moveLeft() {
    float newX = model->getX()-0.1f;
    if(isOffScreen(newX, model->getY())) return 0;
    model->setX(newX);
    return 0;
}

int Controller::moveRight() {
    float newX = model->getX()+0.1f;
    if(isOffScreen(newX, model->getY())) return 0;
    model->setX(newX);
    return 0;
}

int Controller::moveUp() {
    float newY = model->getY()+0.1f;
    if(isOffScreen(model->getX(), newY)) return 0;
    model->setY(newY);
    return 0;
}

int Controller::moveDown() {
    float newY = model->getY()-0.1f;
    if(isOffScreen(model->getX(), newY)) return 0;
    model->setY(newY);
    return 0;
}

bool Controller::isOffScreen(float newX, float newY) {

    return (0 < newY + (model->getHitbox().getH()/2) || newY - (model->getHitbox().getH()/2) < -MaxLogicY) ||
            (0 > newX - (model->getHitbox().getW()/2) || newX + (model->getHitbox().getW()/2) > MaxLogicX);
    /*
    return -(MaxLogicY >= y + (model->getHitbox().getH())/2 && y - (model->getHitbox().getH())/2 <= -MaxLogicY)
    || (MaxLogicX >= x + (model->getHitbox().getW())/2 && x - (model->getHitbox().getW())/2 <= -MaxLogicX);*/
}

int Controller::shoot(std::vector<std::unique_ptr<Controller>> &Controllers) {
    if(model->getFireCooldown() != 0) return 0;
    std::unique_ptr<ControllerBullet> bullet = std::make_unique<ControllerBullet>(model->getX(), model->getY() + model->getHitbox().getH());
    notify(*bullet, Events::event::CreateBulletView);
    Controllers.push_back(std::move(bullet));
    model->setFireCooldown(50);
    return 0;
}
