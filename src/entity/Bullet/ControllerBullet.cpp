//
// Created by timsa on 26-Dec-19.
//

#include "ControllerBullet.h"
#include "EntityBullet.h"

ControllerBullet::ControllerBullet(float posX, float posY) {
    model = std::make_unique<EntityBullet>();
    model->setX(posX);
    model->setY(posY);
}

int ControllerBullet::update(std::vector<std::unique_ptr<Controller>>& controller) {
    moveUp();
    return 0;
}

int ControllerBullet::moveUp() {
    float newY = model->getY()+0.1f;
    model->setY(newY);
    return 0;
}
