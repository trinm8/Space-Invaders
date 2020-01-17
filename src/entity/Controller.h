//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_CONTROLLER_H
#define SMFL_TEST_CONTROLLER_H

#include "Entity.h"
#include "Hitbox.h"
#include "Subject.h"
#include "View.h"
#include <iostream>

class Controller : public Subject
{
        /*! \class Controller
         *  This class is the main object that controls an entity, every other Controller inherents from this class.
         *  Every action that needs to be preformed as a gameobject will be handled by the Controller class.
         *  The Controller keeps a pointer to the model that stores all the data of this object. The actuall controller
         *  will handle this data, The controller has some data of its own that it uses for more general game rules then
         *  actual logical data.
         */

protected:
        bool expired; /*!< Keeps track if the entity needs to be removed */

        int direction{};

        std::shared_ptr<Entity> model; /*!< Pointer to the data itself */

        bool needsObserver; /*!< Does the controller have a SFMLmanager */

        int moveHorizontal();

        int moveVertical();

public:
        Controller();

        /*!
         * Creates a new controller with a SFMLmanager so that it can be rendered on screen.
         * @param SFMLmanager
         */
        explicit Controller(const std::shared_ptr<Observer>& SFMLmanager);

        /*!
         * Every time the game needs to update we call this function, It will process the next step of the entity
         * which can consist of moving and/or shooting. The update function is pure virtual because every entity handles
         * differently.
         * @param controller A reference to all the the controllers currently in game, this is used to add new entities
         * to the game from the controller itself.
         */
        virtual int update(std::vector<std::shared_ptr<Controller>>& controller) = 0;

        [[nodiscard]] const std::shared_ptr<Entity>& getModel() const;

        virtual int shoot(std::vector<std::shared_ptr<Controller>>& Controllers);

        virtual bool isOffScreen(float X, float Y);

        bool isExpired() const;

        void makeExpired();

        Hitbox& getHitbox();

        std::pair<float, float> getHitboxLeftCorner();

        std::pair<float, float> getHitboxRightCorner();

        /*!
         * We check if the other controller's hitbox is intersecting with the one of the current controller.
         * @param otherController the colliding object
         * @return if there is a collision
         */
        virtual bool collides(Controller& otherController);

        /*!
         * If the entity damages other entities on contact it is considered deadly
         */
        bool isDeadly();

        int takeDamage(int value);

        /*!
         * If this entity collides with another one it will process the collision on its own and might affect the other
         * entity if it has that effect.
         * @param other The other entity it has collided with.
         */
        virtual int onCollision(Controller& other) = 0;

        ~Controller() override;

        bool hasObserver();

        void gotObserver();

        int getLives() const;

        virtual void setLives(int lives);
};

#endif // SMFL_TEST_CONTROLLER_H
