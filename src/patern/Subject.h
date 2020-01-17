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
        /*! \class Subject
         *  The subject class is a part of the Observer pattern that is used for the logic <=> view communication that
         * happens in the game, currently every logic component that needs a visual representation is a subject.
         * This class is Always inherited and i'snt meant to be used on its own.
         */
        std::vector<std::shared_ptr<Observer>> observers;

protected:
        /*!
         * This function will let all the observers know that there has been a change that needs their attention
         * @param entity the entity where the change happened
         * @param events the change that happend
         */
        void notify(Controller& entity, Events::event events);

public:
        void addObserver(const std::shared_ptr<Observer>& observer);

        virtual ~Subject();
};

#endif // SMFL_TEST_SUBJECT_H
