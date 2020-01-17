//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_VIEW_H
#define SMFL_TEST_VIEW_H

#include "Observer.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>

class Entity;

class Subject;

class View
{
        /*! \class View
         *  The view class represents an Entity from as sprite on screen. It only has access to the model of the entity
         *  and neither the model nor the controller have a connect to the view class. The view class is told to update
         *  by the SFMLmanager.
         */
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> sprite;
        std::shared_ptr<Entity> model;

public:
        const std::shared_ptr<Entity>& getModel() const;

        View(std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<Entity> model,
             float screensizeX, float screensizeY);

        /*!
         * The update function will render the sprite to the screen.
         * @param window the window where the sprite needs to be drawn on
         */
        int update(const std::shared_ptr<sf::RenderWindow>& window);
};

#endif // SMFL_TEST_VIEW_H
