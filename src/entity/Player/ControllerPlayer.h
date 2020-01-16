//
// Created by timsa on 05-Dec-19.
//

#ifndef SMFL_TEST_CONTROLLERPLAYER_H
#define SMFL_TEST_CONTROLLERPLAYER_H

#include "Controller.h"
#include "EntityPlayer.h"
#include "Events.h"

class ControllerPlayer: public Controller {

public:

    ControllerPlayer();

    ControllerPlayer(std::shared_ptr<Observer> SFMLmanager);

    int update(std::vector<std::shared_ptr<Controller>>& controller);

    int onCollision(Controller &other) override;

    virtual ~ControllerPlayer();

};


#endif //SMFL_TEST_CONTROLLERPLAYER_H
