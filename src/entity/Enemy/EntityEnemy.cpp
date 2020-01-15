//
// Created by timsa on 14-Jan-20.
//

#include "EntityEnemy.h"

EntityEnemy::EntityEnemy(EntityEnemy& next) {
    nextEnemy = std::make_shared<EntityEnemy>(next);
}

EntityEnemy::EntityEnemy() {
    nextEnemy = nullptr;
}
