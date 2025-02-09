//
// Created by timsa on 26-Dec-19.
//

#ifndef SMFL_TEST_CONTROLLERBULLET_H
#define SMFL_TEST_CONTROLLERBULLET_H

#include "Controller.h"

class ControllerBullet : public Controller
{
        /*! \class ControllerBullet
         *  The controller for the bullet is as the name implies the controller for the bullet entities.
         */
public:
        /*!
         * @param posX, posY  Where the bullet has been shot from
         * @param direction Which direction is the bullet travelling in
         */
        ControllerBullet(float posX, float posY, int direction);

        int update(std::vector<std::shared_ptr<Controller>>& controller) override;

        int onCollision(Controller& other) override;
};

#endif // SMFL_TEST_CONTROLLERBULLET_H
