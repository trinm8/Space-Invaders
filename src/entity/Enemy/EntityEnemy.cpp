//
// Created by timsa on 14-Jan-20.
//

#include "EntityEnemy.h"
#include <utility>

EntityEnemy::EntityEnemy(std::shared_ptr<EntityEnemy> next) : Entity() { nextEnemy = std::move(next); }

EntityEnemy::EntityEnemy() : Entity() { nextEnemy = nullptr; }

std::shared_ptr<EntityEnemy>& EntityEnemy::getNextEnemy() { return nextEnemy; }

void EntityEnemy::setNextEnemy(const std::shared_ptr<EntityEnemy>& nextEnemy) { EntityEnemy::nextEnemy = nextEnemy; }
