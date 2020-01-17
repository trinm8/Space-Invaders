//
// Created by timsa on 05-Dec-19.
//

#ifndef SMFL_TEST_CONTROLLERPLAYER_H
#define SMFL_TEST_CONTROLLERPLAYER_H

#include "Controller.h"
#include "Events.h"

class ControllerPlayer : public Controller
{
        /*!
         * The controller which simulates the movements that are being made by the player. The big difference is that
         * this controller doesnt follow a strict update function but actually looks at keyboard inputs to decide what
         * to do next.
         */
public:
        explicit ControllerPlayer(const std::shared_ptr<Observer>& SFMLmanager, const std::string& textureLocation);

        int update(std::vector<std::shared_ptr<Controller>>& controller) override;

        int onCollision(Controller& other) override;

        ~ControllerPlayer() override;
};

#endif // SMFL_TEST_CONTROLLERPLAYER_H
