//
// Created by timsa on 05-Dec-19.
//

#include <SFML/System.hpp>
#include "ControllerPlayer.h"
#include "EntityPlayer.h"
#include "ViewPlayer.h"
#include "InputHandler.h"
#include "Command.h"

ControllerPlayer::ControllerPlayer(Observer& SFMLmanager) {
    model = std::make_shared<EntityPlayer>();
    addObserver(std::shared_ptr<Observer>(&SFMLmanager));
    notify(*this, Events::event::CreatePlayerView);
    model->getHitbox().setW(0.1);
    model->getHitbox().setH(0.1);
    model->setX(2.f);
    model->setY(-2.5f);
}

int ControllerPlayer::update(std::vector<std::unique_ptr<Controller>>& controller) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  moveLeft();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) moveRight();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) shoot(controller);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moveUp();
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) moveDown();
    std::cout << "Absolute: " << getModel()->getX() << ", " << getModel()->getY() << std::endl;
    if(model->getFireCooldown() != 0){
        model->FireCooldownTick(1);
    }
    return 0;
}
