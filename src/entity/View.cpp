//
// Created by timsa on 04-Dec-19.
//

#include "View.h"

#include "Controller.h"
#include "Stopwatch.h"
#include "Subject.h"
#include "Transformation.h"
#include <utility>

View::View(std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<Entity> model,
           float screensizeX, float screensizeY)
    : texture(std::move(texture)), sprite(std::move(sprite))
{
        this->model = std::move(model);
        this->sprite->setTexture(*this->texture);
        this->sprite->setScale(Global::Transformation::scaleX(screensizeX),
                               Global::Transformation::scaleY(screensizeY));
        this->sprite->setOrigin(this->sprite->getTexture()->getSize().x * 0.5f,
                                this->sprite->getTexture()->getSize().y * 0.5f);
}

int View::update(const std::shared_ptr<sf::RenderWindow>& window)
{
        sprite->setPosition(Global::Transformation::transformationX(
                                model->getX() + (model->getSpeedX() * Global::Stopwatch::getDeltaTime())),
                            Global::Transformation::transformationY(
                                model->getY() + (model->getSpeedY() * Global::Stopwatch::getDeltaTime())));
        window->draw(*sprite);

        return 0;
}

const std::shared_ptr<Entity>& View::getModel() const { return model; }
