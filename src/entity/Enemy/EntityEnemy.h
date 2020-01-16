//
// Created by timsa on 14-Jan-20.
//

#ifndef SMFL_TEST_ENTITYENEMY_H
#define SMFL_TEST_ENTITYENEMY_H

#include "Entity.h"

class EntityEnemy : public Entity
{

        std::shared_ptr<EntityEnemy> nextEnemy;

public:
        EntityEnemy();

        explicit EntityEnemy(std::shared_ptr<EntityEnemy> next);

        std::shared_ptr<EntityEnemy>& getNextEnemy();

        void setNextEnemy(const std::shared_ptr<EntityEnemy>& nextEnemy);
};

#endif // SMFL_TEST_ENTITYENEMY_H
