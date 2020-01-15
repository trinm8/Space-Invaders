//
// Created by timsa on 05-Dec-19.
//

#ifndef SMFL_TEST_SFMLMANAGER_H
#define SMFL_TEST_SFMLMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Observer.h"

class Subject;
class View;

class SFMLmanager: public Observer {

    std::shared_ptr<sf::RenderWindow> window;
    std::vector<std::shared_ptr<View>> views;

public:

    SFMLmanager() = default;

    SFMLmanager(sf::RenderWindow& window);

    int placeholder();

    [[nodiscard]] const std::shared_ptr<sf::RenderWindow> &getWindow() const;

    int draw();

    void onNotify(Controller& controller , Events::event event);


};


#endif //SMFL_TEST_SFMLMANAGER_H
