//
// Created by timsa on 14-Jan-20.
//

#ifndef SMFL_TEST_ENTITYENEMY_H
#define SMFL_TEST_ENTITYENEMY_H

#include "Entity.h"

class EntityEnemy : public Entity
{
        /*! \class EntityEnemy
         *  This is the data class for the INDIVIDUAL enemies, not the whole block of enemies like the ControllerEnemy
         * is. the major difference between this and the Entity class is that we have a nextEnemy pointer that tells the
         * enemy of its neighbor.
         */
        std::shared_ptr<EntityEnemy> nextEnemy;

public:
        EntityEnemy();

        explicit EntityEnemy(std::shared_ptr<EntityEnemy> next);

        std::shared_ptr<EntityEnemy>& getNextEnemy();

        void setNextEnemy(const std::shared_ptr<EntityEnemy>& nextEnemy);
};

#endif // SMFL_TEST_ENTITYENEMY_H
