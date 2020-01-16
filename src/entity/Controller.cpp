//
// Created by timsa on 04-Dec-19.
//

#include "Controller.h"

#include <utility>
#include "ControllerBullet.h"
#include "Defines.h"
#include "Stopwatch.h"

Controller::Controller(){
    expired = false;
}

Controller::Controller(std::shared_ptr<Observer> SFMLmanager) {
    expired = false;
    needsObserver = false;
    addObserver(std::move(SFMLmanager));
}


const std::shared_ptr<Entity> &Controller::getModel() const {
    return model;
}

bool Controller::isOffScreen(float X, float Y) {

    return (0 < Y + (model->getHitbox().getH() / 2) || Y - (model->getHitbox().getH() / 2) < -MaxLogicY) ||
           (0 > X - (model->getHitbox().getW() / 2) || X + (model->getHitbox().getW() / 2) > MaxLogicX);
    /*
    return -(MaxLogicY >= y + (model->getHitbox().getH())/2 && y - (model->getHitbox().getH())/2 <= -MaxLogicY)
    || (MaxLogicX >= x + (model->getHitbox().getW())/2 && x - (model->getHitbox().getW())/2 <= -MaxLogicX);*/
}

int Controller::shoot(std::vector<std::shared_ptr<Controller>> &Controllers) {
    if(model->getFireCooldown() != 0) return 0;
    std::shared_ptr<ControllerBullet> bullet = std::make_shared<ControllerBullet>(model->getX(), model->getY() + (model->getSpeedY() + model->getHitbox().getH() * (float) model->getDirectionY()) , model->getDirectionY());
    notify(*bullet, Events::event::CreateBulletView);
    Controllers.push_back(std::move(bullet));
    model->setFireCooldown(2000);
    return 0;
}

void Controller::setPos(float x, float y) {
    model->setX(x);
    model->setY(y);
}

bool Controller::isExpired() const {
    return expired;
}

void Controller::makeExpired() {
    expired = true;
    notify(*this, Events::event::Expired);

}

Hitbox Controller::getHitbox() {
    return model->getHitbox();
}

std::pair<float, float> Controller::getHitboxLeftCorner() {
    return std::pair<float , float>(model->getX() - getHitbox().getW()/2, model->getY() + getHitbox().getH()/2);
}

std::pair<float, float> Controller::getHitboxRightCorner() {
    return std::pair<float, float>(model->getX() + getHitbox().getW()/2, model->getY() - getHitbox().getH()/2);
}

bool Controller::collides(Controller &otherController) {
    std::pair<float, float> cornerL1 = getHitboxLeftCorner();
    std::pair<float, float> cornerL2 = otherController.getHitboxLeftCorner();
    std::pair<float, float> cornerR1 = getHitboxRightCorner();
    std::pair<float, float> cornerR2 = otherController.getHitboxRightCorner();

    return !((cornerL1.first > cornerR2.first || cornerL2.first > cornerR1.first) ||
             (cornerR1.second > cornerL2.second || cornerL1.second < cornerR2.second));

    //std::cout << "hit" << std::endl;
}

bool Controller::isDeadly() {
    return model->isDeadly();
}

int Controller::takeDamage(int value) {
    model->setLives(model->getLives() - value);
    return 0;
}

int Controller::moveVertical() {
    float newY = model->getY() + (model->getSpeedY()*(float)model->getDirectionY());
    if(model->isScreenlocked() && isOffScreen(model->getX(), newY)) return 0;
    model->setY(newY);
    return 0;
}

int Controller::moveHorizontal() {
    float newX = model->getX() + (model->getSpeedX() * (float)model->getDirectionX());
    if(model->isScreenlocked() && isOffScreen(newX, model->getY())) return 0;
    model->setX(newX);
    return 0;
}

Controller::~Controller() {

}

bool Controller::hasObserver() {
    return !needsObserver;
}

void Controller::gotObserver() {
    needsObserver = false;
}

int Controller::getLives() const {
    return model->getLives();
}


