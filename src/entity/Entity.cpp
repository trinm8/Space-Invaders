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
