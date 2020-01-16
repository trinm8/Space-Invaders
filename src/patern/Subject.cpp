//
// Created by timsa on 04-Dec-19.
//

#include "Subject.h"
#include <algorithm>

void Subject::addObserver(const std::shared_ptr<Observer>& observer) { observers.push_back(observer); }

void Subject::notify(Controller& controller, Events::event event)
{
        for (auto& observer : observers) {
                observer->onNotify(controller, event);
        }
}

Subject::~Subject()
{
        for (int i = 0; i < observers.size(); ++i) {
                observers.erase(observers.begin());
        }
}
