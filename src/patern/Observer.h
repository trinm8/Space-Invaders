//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_OBSERVER_H
#define SMFL_TEST_OBSERVER_H

#include "Events.h"
#include <iostream>
#include <memory>

class Controller;
class View;

class Observer {

public:
    virtual void onNotify(Controller& controller, Events::event event) = 0;
};


#endif //SMFL_TEST_OBSERVER_H
