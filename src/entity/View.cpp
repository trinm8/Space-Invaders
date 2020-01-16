//
// Created by timsa on 04-Dec-19.
//

#include "View.h"
#include "Subject.h"
#include "Controller.h"
#include "Transformation.h"
#include "Stopwatch.h"
#include "Defines.h"

View::View(std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<Entity> model,
           float screensizeX, float screensizeY) : texture(std::move(texture)), sprite(std::move(sprite)){
    this->model = model;
    this->sprite->setTexture(*this->texture);
    this->sprite->setScale(Global::Transformation::scaleX(screensizeX), Global::Transformation::scaleY(screensizeY));
    //this->sprite->setScale(Global::Transformation::scaleX(screensizeX) * model->getHitbox().getW(), Global::Transformation::scaleY(screensizeY) * model->getHitbox().getH());
    this->sprite->setOrigin( this->sprite->getTexture()->getSize().x * 0.5f,this->sprite->getTexture()->getSize().y * 0.5f);

}

int View::update(const std::shared_ptr<sf::RenderWindow> window) {

    //std::cout << "RelativeVisual: " << Global::Transformation::transformationX(model->getX()) << ", " << Global::Transformation::transformationY(model->getY()) << std::endl;
    //std::cout << model->getX() << ", " <<  model->getY() << std::endl;

    //sf::RectangleShape hitbox(sf::Vector2( Global::Transformation::transformationX(model->getHitbox().getW()), std::abs(Global::Transformation::transformationY(model->getHitbox().getH()))));



    sprite->setPosition(Global::Transformation::transformationX(model->getX() + (model->getSpeedX() *  Global::Stopwatch::getDeltaTime())), Global::Transformation::transformationY(model->getY() +( model->getSpeedY() * Global::Stopwatch::getDeltaTime())));
    //sprite->setPosition(Global::Transformation::transformationX(model->getX() ), Global::Transformation::transformationY(model->getY()));
    //sprite->scale(Transformation::transformationX(1), Transformation::transformationY(1));
    //sprite->setPosition( model->getX(), model->getY());
    window->draw(*sprite);

    //hitbox.setPosition(sprite->getPosition().x - hitbox.getSize().x/2, sprite->getPosition().y - hitbox.getSize().y/2);

    //window->draw(hitbox);

    return 0;
}

const std::shared_ptr<Entity> &View::getModel() const {
    return model;
}
