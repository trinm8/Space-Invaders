//
// Created by timsa on 14-Jan-20.
//

#include "ControllerEnemy.h"

#include "EntityEnemy.h"
#include <random>
#include <utility>

int ControllerEnemy::update(std::vector<std::shared_ptr<Controller>>& controller)
{

        model = start;
        timebetweenshots++;

        if (reachedEdge()) {
                lowerLevel();
                direction *= -1;
        }

        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                model = current;
                model->setDirectionX(direction);
                moveHorizontal();
                if (model->getFireCooldown() > 0) {
                        model->FireCooldownTick(1);
                }

                // float newX = current->getX() + (0.01f * (float)direction);
                // current->setX(newX);
                /*        if(isOffScreen(newX, current->getY())){

                } else{

                }*/
        }

        if (timebetweenshots >= 300) {
                std::vector<std::shared_ptr<EntityEnemy>> ready = getShootReadyEnemies();
                if (!ready.empty() && !reachedEdge()) {
                        // std::random_device randomDevice;
                        // std::default_random_engine e(randomDevice);
                        // std::uniform_int_distribution<int> uniform_dist(1, static_cast<int>(ready.size() - 1));
                        // int nextshoot = uniform_dist(e);
                        int nextshoot = static_cast<int>(rand() % ready.size() - 1 + 1);
                        model = ready[nextshoot];
                        shoot(controller);
                        timebetweenshots = 0;
                }
        }

        return 0;
}

// we create a linked list of enemies and will parse through them to update each one of them
ControllerEnemy::ControllerEnemy(int enemyCount, const std::shared_ptr<Observer> &SFMLmanager,
                                 const std::string &textureLocation)
    : Controller(SFMLmanager)
{
        direction = -1;
        timebetweenshots = 0;

        model = std::make_shared<EntityEnemy>();
        model->setTextureLocation(textureLocation);
        notify(*this, Events::createView);
        for (int i = 0; i < enemyCount - 1; ++i) {
                std::shared_ptr<EntityEnemy> created =
                    std::make_shared<EntityEnemy>(std::static_pointer_cast<EntityEnemy>(model));
                model = created;
                model->setTextureLocation(textureLocation);
                notify(*this, Events::createView);
        }
        start = std::static_pointer_cast<EntityEnemy>(model);

        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                current->setHitbox(Hitbox(0.2, 0.25));
                current->setDeadly(false);
                current->setLives(1);
                current->setSpeedX(0.001f);
                current->setSpeedY(0.0f);
                current->setDirectionY(-1);
                current->setScreenlocked(true);
                current->setFireCooldown(0);
        }

        int counter = 0;
        float ypos = -0.3f;
        float xpos = 3.5f;
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                current->setX(xpos);
                current->setY(ypos);
                xpos -= 0.5f;
                counter++;
                if (counter == 7) {
                        ypos -= 0.4f;
                        xpos = 3.5f;
                        counter = 0;
                }
        }
}

bool ControllerEnemy::reachedEdge()
{
        float maxX = start->getX();
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                if (direction < 0) {
                        if (current->getX() < maxX) {
                                maxX = current->getX();
                        }
                } else {
                        if (current->getX() > maxX) {
                                maxX = current->getX();
                        }
                }
        }
        return isOffScreen(maxX + (0.01f * (float)direction), -1.5f);
}

void ControllerEnemy::lowerLevel()
{
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                current->setY(current->getY() - 0.05f);
        }
}

bool ControllerEnemy::collides(class Controller& otherController)
{
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {

                model = current;

                std::pair<float, float> cornerL1 = getHitboxLeftCorner();
                std::pair<float, float> cornerL2 = otherController.getHitboxLeftCorner();
                std::pair<float, float> cornerR1 = getHitboxRightCorner();
                std::pair<float, float> cornerR2 = otherController.getHitboxRightCorner();

                //if squares are next to or above/under each other
                if ((cornerL1.first > cornerR2.first || cornerL2.first > cornerR1.first) ||
                    (cornerR1.second > cornerL2.second || cornerL1.second < cornerR2.second)) {
                        continue;
                }

                return true;
        }
        model = start;
        return false;
}

void ControllerEnemy::removeEnemy()
{
        std::shared_ptr<EntityEnemy> current = start;
        std::shared_ptr<EntityEnemy> wanted = std::static_pointer_cast<EntityEnemy>(model);
        if (getEnemysize() == 1) { //if we have to delete the last enemy, consider the controller expired
                model = nullptr;
                start = nullptr;
                expired = true;
                return;
        }
        if (current.get() == wanted.get()) { //to be removed == first element
                current = current->getNextEnemy();
                wanted->setNextEnemy(nullptr);
                model = current;
                start = current;
                return;
        }
        while (current->getNextEnemy() != wanted) {
                current = current->getNextEnemy();
        }

        if (wanted->getNextEnemy() != nullptr) { // if to be removed == last element
                current->setNextEnemy(wanted->getNextEnemy());
                wanted->setNextEnemy(nullptr);
        } else {
                current->setNextEnemy(nullptr);
        }
}

int ControllerEnemy::getEnemysize()
{
        if (start == nullptr)
                return 0;
        std::shared_ptr<EntityEnemy> current = start;
        int counter = 1;
        while (current->getNextEnemy() != nullptr) {
                counter++;
                current = current->getNextEnemy();
        }
        return counter;
}

int ControllerEnemy::onCollision(Controller& other)
{
        if (other.isDeadly()) {
                takeDamage(1);
                if (model->getLives() < 1) {
                        notify(*this, Events::event::expired);
                        removeEnemy();
                        // model = start;
                        return 0;
                }
        }
        return 0;
}

bool ControllerEnemy::enemyinfront(const std::shared_ptr<EntityEnemy>& toCheck)
{
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                if (std::abs(current->getX() - toCheck->getX()) < std::numeric_limits<double>::epsilon() &&
                    current != toCheck && current->getY() < toCheck->getY()) {
                        return true;
                }
        }
        return false;
}

std::vector<std::shared_ptr<EntityEnemy>> ControllerEnemy::getShootReadyEnemies()
{
        std::vector<std::shared_ptr<EntityEnemy>> ready;
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                if (!enemyinfront(current) && current->getFireCooldown() == 0) {
                        ready.push_back(current);
                }
        }
        return ready;
}

float ControllerEnemy::getlowestY()
{
        float minY = 0;
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                if (current->getY() < minY) {
                        minY = current->getY();
                }
        }
        return minY;
}

void ControllerEnemy::setLives(int lives) {
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                current->setLives(lives);
        }
}
