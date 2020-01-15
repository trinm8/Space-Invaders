//
// Created by timsa on 04-Dec-19.
//

#include "Entity.h"

float Entity::getX() const {
    return x;
}

float Entity::getY() const {
    return y;
}

void Entity::setX(float x) {
    Entity::x = x;
}

void Entity::setY(float y) {
    Entity::y = y;
}

Hitbox &Entity::getHitbox() {
    return hitbox;
}

void Entity::setHitbox(const Hitbox &hitbox) {
    Entity::hitbox = hitbox;
}

double Entity::getFireCooldown() const {
    return fireCooldown;
}

void Entity::setFireCooldown(double fireCooldown) {
    Entity::fireCooldown = fireCooldown;
}

void Entity::FireCooldownTick(double percent) {
    fireCooldown -= 1.0 * percent;
}

int Entity::getLives() const {
    return lives;
}

void Entity::setLives(int lives) {
    Entity::lives = lives;
}

bool Entity::isDeadly() const {
    return deadly;
}

void Entity::setDeadly(bool deadly) {
    Entity::deadly = deadly;
}

float Entity::getSpeedY() const {
    return speedY;
}

void Entity::setSpeedY(float speedY) {
    Entity::speedY = speedY;
}

int Entity::getDirectionY() const {
    return directionY;
}

void Entity::setDirectionY(int directionY) {
    Entity::directionY = directionY;
}

float Entity::getSpeedX() const {
    return speedX;
}

void Entity::setSpeedX(float speedX) {
    Entity::speedX = speedX;
}

int Entity::getDirectionX() const {
    return directionX;
}

void Entity::setDirectionX(int directionX) {
    Entity::directionX = directionX;
}

bool Entity::isScreenlocked() const {
    return screenlocked;
}

void Entity::setScreenlocked(bool screenlocked) {
    Entity::screenlocked = screenlocked;
}
