//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_VIEW_H
#define SMFL_TEST_VIEW_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include "Observer.h"

class Entity;

class Subject;

class View{
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;
    std::shared_ptr<Entity> model;
public:

    const std::shared_ptr<Entity> &getModel() const;

    View(std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<Entity> model,
         float screensizeX, float screensizeY);

    int update(const std::shared_ptr<sf::RenderWindow>& window);

};


#endif //SMFL_TEST_VIEW_H
