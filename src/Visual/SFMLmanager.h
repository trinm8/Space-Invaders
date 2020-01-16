//
// Created by timsa on 05-Dec-19.
//

#ifndef SMFL_TEST_SFMLMANAGER_H
#define SMFL_TEST_SFMLMANAGER_H

#include "Observer.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

class Subject;
class View;

class SFMLmanager : public Observer
{

        std::shared_ptr<sf::RenderWindow> window;
        std::vector<std::shared_ptr<View>> views;
        std::shared_ptr<sf::Font> font;
        std::vector<std::shared_ptr<sf::Text>> texts;
        std::shared_ptr<sf::Text> playerLife;
        bool once;

public:
        explicit SFMLmanager(std::shared_ptr<sf::RenderWindow> window);

        int draw();

        void onNotify(Controller& controller, Events::event event) override;

        void gameover(const std::string& message);

        void clearAll();
};

#endif // SMFL_TEST_SFMLMANAGER_H
