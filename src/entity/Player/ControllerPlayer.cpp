//
// Created by timsa on 05-Dec-19.
//

#include "ControllerPlayer.h"

ControllerPlayer::ControllerPlayer(const std::shared_ptr<Observer>& SFMLmanager, const std::string& textureLocation)
    : Controller(SFMLmanager)
{
        model = std::make_shared<Entity>();
        model->setTextureLocation(textureLocation);
        notify(*this, Events::event::createView);
        model->getHitbox().setW(0.2);
        model->getHitbox().setH(0.25);
        model->setX(2.f);
        model->setY(-2.5f);
        model->setLives(3);
        model->setDeadly(false);
        model->setDirectionY(1);
        model->setSpeedX(0.003f);
        model->setScreenlocked(true);
        notify(*this, Events::event::updatePlayerHealth); //makes it so the player health initialzed on screen
}
/*
 * We check for the latest player input and change the direction if needed and execute a move or shoot if the button is
 * pressed. We also tick down the firecooldown if its not 0.
 */
int ControllerPlayer::update(std::vector<std::shared_ptr<Controller>>& controller)
{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                model->setDirectionX(-1);
                moveHorizontal();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                model->setDirectionX(1);
                moveHorizontal();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                shoot(controller);
        if (model->getFireCooldown() > 0) {
                model->FireCooldownTick(1);
        }
        return 0;
}

/*
 * We check if there is a collision and take damage if the other is deadly. we also notify that the HUD needs to be
 * updated.
 */
int ControllerPlayer::onCollision(Controller& other)
{
        if (other.isDeadly()) {
                takeDamage(1);
                notify(*this, Events::event::updatePlayerHealth);
        }
        return 0;
}

ControllerPlayer::~ControllerPlayer()
{
        expired = true;
        notify(*this, Events::expired);
}
