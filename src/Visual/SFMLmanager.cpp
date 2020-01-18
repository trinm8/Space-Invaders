//
// Created by timsa on 05-Dec-19.
//

#include "SFMLmanager.h"
#include "Controller.h"
#include <utility>

/*
 * We load in the window on which we render the everything we want to show.
 * we set the font we want to use in our game.
 * we add our HUD text, currently only the player lives.
 */
SFMLmanager::SFMLmanager(std::shared_ptr<sf::RenderWindow> window)
{
        this->window = std::move(window);
        sf::Text health;
        this->font = std::make_shared<sf::Font>();
        if (!font->loadFromFile("Assests/letters.ttf")) {
            throw std::runtime_error("no letters.ttf found in the asset files");
        }
        health.setFont(*font);
        health.setString("Health");
        health.setCharacterSize(30);
        health.setStyle(sf::Text::Bold);
        health.setFillColor(sf::Color::White);
        playerLife = std::make_shared<sf::Text>(health);
        texts.push_back(playerLife);
        gameOver = false;
}

/*
 * We clear the last sprites off the screen.
 * We tell every view in our class to update itself and draw itself on the screen.
 * all the text on screen is also updated
 */
int SFMLmanager::draw()
{

        window->clear();

        for (auto& itr : views) {
                itr->update(window);
        }

        for (auto& text : texts) {
                window->draw(*text);
        }

        window->display();

        return 0;
}

/*
 * The notify part of the observer class.
 * expired = we look for the view that represents the model that has been marked for deletion and remove it.
 * createview = we make a texture and sprite based on the model were given and make a view out of it.
 */
void SFMLmanager::onNotify(Controller& controller, Events::event event)
{
        // TODO: next release, put events in a buffer so they are handled at updated
        if (event == Events::event::win) {
                gameover("YOU WIN");
                return;
        }
        if (event == Events::event::updatePlayerHealth) {
                playerLife->setString("Health " + std::to_string(controller.getModel()->getLives()));
                return;
        }
        if (event == Events::event::expired) {
                for (auto i = static_cast<int>(views.size() - 1); i > -1; --i) {
                        if (controller.getModel().get() == views[i]->getModel().get()) {
                                views.erase(views.begin() + i);
                                return;
                        }
                }
        }
        if (event == Events::createView) {
                sf::Texture texture;
                std::string location = controller.getModel()->getTextureLocation();
                if (!texture.loadFromFile(location)) {
                        throw std::runtime_error("Texture " + location + " not found");
                }
                texture.setSmooth(true);
                std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
                views.push_back(std::make_shared<View>(std::make_shared<sf::Texture>(texture), sprite,
                                                       controller.getModel(), window->getSize().x,
                                                       window->getSize().y));
        }
}

void SFMLmanager::clearAll() { views.clear(); }

void SFMLmanager::gameover(const std::string& message)
{

        if (gameOver)
                return;

        sf::Text text;
        text.setFont(*font);
        text.setString(message);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        texts.clear();
        texts.push_back(std::make_shared<sf::Text>(std::move(text)));
        gameOver = true;
}
