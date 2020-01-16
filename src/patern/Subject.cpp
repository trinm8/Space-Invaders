//
// Created by timsa on 04-Dec-19.
//

#include "Subject.h"
#include <algorithm>

void Subject::addObserver(const std::shared_ptr<Observer>& observer) {
  observers.push_back(observer);
}

void Subject::removeObserver(const std::shared_ptr<Observer>& observer) {
    auto loc = std::find(observers.begin(), observers.end(), observer);
    if(loc != observers.end()){
        observers.erase(loc);
    }
}

void Subject::notify( Controller &controller, Events::event event) {
    for (int i = 0; i < observers.size(); ++i) {
        observers[i]->onNotify(controller, event);
    }
}
