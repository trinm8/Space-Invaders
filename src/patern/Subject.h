//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_SUBJECT_H
#define SMFL_TEST_SUBJECT_H

#include "Events.h"
#include "Observer.h"
#include <iostream>
#include <memory>
#include <vector>

class Controller;

class Subject
{
        std::vector<std::shared_ptr<Observer>> observers;

protected:
        void notify(Controller& entity, Events::event events);

public:
        void addObserver(const std::shared_ptr<Observer>& observer);

        virtual ~Subject();
};

#endif // SMFL_TEST_SUBJECT_H
