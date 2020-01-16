//
// Created by timsa on 05-Dec-19.
//

#include <SFML/System.hpp>
#include "ControllerPlayer.h"
#include "EntityPlayer.h"
#include "ViewPlayer.h"
#include "InputHandler.h"
#include "Command.h"

ControllerPlayer::ControllerPlayer(std::shared_ptr<Observer> SFMLmanager): Controller(SFMLmanager) {
    model = std::make_shared<EntityPlayer>();
    //addObserver(std::shared_ptr<Observer>(&SFMLmanager));
    notify(*this, Events::event::CreatePlayerView);
    model->getHitbox().setW(0.2);
    model->getHitbox().setH(0.25);
    model->setX(2.f);
    model->setY(-2.5f);
    model->setLives(3);
    model->setDeadly(false);
    model->setDirectionY(1);
    model->setSpeedX(0.001f);
    model->setScreenlocked(true);
    notify(*this, Events::event::UpdatePlayerHealth);
}

int ControllerPlayer::update(std::vector<std::shared_ptr<Controller>>& controller) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        model->setDirectionX(-1);
        moveHorizontal();
    };
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        model->setDirectionX(1);
        moveHorizontal();
    };
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) shoot(controller);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moveUp();
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) moveDown();
    if(model->getFireCooldown() != 0){
        model->FireCooldownTick(1);
    }
    return 0;
}

int ControllerPlayer::onCollision(Controller &other) {
    if(other.isDeadly()){
        takeDamage(1);
        notify(*this, Events::event::UpdatePlayerHealth);
    }
    return 0;
}

ControllerPlayer::~ControllerPlayer() {
    expired = true;
    notify(*this, Events::Expired);
}
