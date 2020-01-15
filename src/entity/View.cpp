//
// Created by timsa on 04-Dec-19.
//

#include "View.h"
#include "Subject.h"
#include "Controller.h"
#include "Transformation.h"
#include "Defines.h"

View::View(std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<Entity> model,
           float screensizeX, float screensizeY) : texture(std::move(texture)), sprite(std::move(sprite)){
    this->model = model;
    this->sprite->setTexture(*this->texture);
    this->sprite->setScale(Global::Transformation::scaleX(screensizeX), Global::Transformation::scaleY(screensizeY));
    this->sprite->setOrigin( this->sprite->getTexture()->getSize().x * 0.5,this->sprite->getTexture()->getSize().y * 0.5);

}

int View::update(const std::shared_ptr<sf::RenderWindow> window) {

    //std::cout << "RelativeVisual: " << Global::Transformation::transformationX(model->getX()) << ", " << Global::Transformation::transformationY(model->getY()) << std::endl;
    //std::cout << model->getX() << ", " <<  model->getY() << std::endl;

    sprite->setPosition(Global::Transformation::transformationX(model->getX()), Global::Transformation::transformationY(model->getY()));
    //sprite->scale(Transformation::transformationX(1), Transformation::transformationY(1));
    //sprite->setPosition( model->getX(), model->getY());
    window->draw(*sprite);
    return 0;
}
