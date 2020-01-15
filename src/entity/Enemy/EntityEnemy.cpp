//
// Created by timsa on 14-Jan-20.
//

#include "EntityEnemy.h"

EntityEnemy::EntityEnemy(std::shared_ptr<EntityEnemy> next) {
    nextEnemy = next;
}

EntityEnemy::EntityEnemy() {
    nextEnemy = nullptr;
}

std::shared_ptr<EntityEnemy> &EntityEnemy::getNextEnemy() {
    return nextEnemy;
}

void EntityEnemy::setNextEnemy(const std::shared_ptr<EntityEnemy> &nextEnemy) {
    EntityEnemy::nextEnemy = nextEnemy;
}
