//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_SUBJECT_H
#define SMFL_TEST_SUBJECT_H

#include <iostream>
#include <vector>
#include <memory>
#include "Observer.h"
#include "Events.h"

class Controller;

class Subject {
 std::vector<std::shared_ptr<Observer>> observers;
 int observeCount;

protected:

    void notify( Controller& entity, Events::event events);

public:


    void addObserver(const std::shared_ptr<Observer>& observer);

    void removeObserver(const std::shared_ptr<Observer>& observer);

};


#endif //SMFL_TEST_SUBJECT_H
