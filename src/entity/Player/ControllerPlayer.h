//
// Created by timsa on 05-Dec-19.
//

#ifndef SMFL_TEST_CONTROLLERPLAYER_H
#define SMFL_TEST_CONTROLLERPLAYER_H

#include "Controller.h"
#include "Events.h"

class ControllerPlayer: public Controller {

public:

    explicit ControllerPlayer(std::shared_ptr<Observer> SFMLmanager);

    int update(std::vector<std::shared_ptr<Controller>>& controller) override;

    int onCollision(Controller &other) override;

    ~ControllerPlayer() override;

};


#endif //SMFL_TEST_CONTROLLERPLAYER_H
