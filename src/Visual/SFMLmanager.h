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
/*!
 * The SFMLmanager class will be the main component for rendering everything on screen, it will handle everything from
 * creating views, updating and removing them and for the text on screen as well. It is an observer that watches every
 * controller that has a visual aspect for visual updates.
 */
        std::shared_ptr<sf::RenderWindow> window; /*!< The window where everything will be drawn on*/
        std::vector<std::shared_ptr<View>> views; /*!< The list of visual representation of Entity*/
        std::shared_ptr<sf::Font> font;
        std::vector<std::shared_ptr<sf::Text>> texts; /*!< The list of text that needs to appear on screen */
        std::shared_ptr<sf::Text> playerLife;
        bool gameOver;

public:
        /*!
         * @param window the window that will be drawn on
         */
        explicit SFMLmanager(std::shared_ptr<sf::RenderWindow> window);

        /*!
         * This function will iterate over all the Views and draw each one on screen.
         */
        int draw();

        void onNotify(Controller& controller, Events::event event) override;

        /*!
         * if a game over has been reached it will stop drawing the views and give an game over message
         * @param message the message that will be displayed on the screen.
         */
        void gameover(const std::string& message);

        void clearAll();
};

#endif // SMFL_TEST_SFMLMANAGER_H
