//
// Created by timsa on 14-Jan-20.
//

#include "ControllerEnemy.h"

#include "EntityEnemy.h"
#include <random>
#include <utility>

/*
 * We Loop reset the current model to the start of the list and add time to the time between when the last shot has been
 * fired.
 * We then look if the enemy that is closest to the edge is actually going to hit it or not, if so we move a level down
 * and change the direction of the enemy movement.
 * Next we loop over all the enemies and move them to their new position and see if we need to reduce their firecooldown
 * the value we pass is to change how quickly we want it to go down.
 * After that we see if we are allowed to shoot again. if so we get all the enemies who's timer is low enough to shoot
 * and dont have any enemies infront of them.
 */
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

/*
 * We create a new chain of enemies. We create a chain by constantly updating the model pointer to the newest entity and
 * then linking then making a new Entity by making it's nextEnemy pointer point at the pointer.
 * After the chain has been created we then loop through and update all the standard values.
 */
ControllerEnemy::ControllerEnemy(int enemyCount, const std::shared_ptr<Observer>& SFMLmanager,
                                 const std::string& textureLocation)
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
        float ypos = -0.45f;
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

/*
 * we keep track of the max/min X position by looping through the current chain and seeing which is closest to the
 * edge by constanly comparing it to the current maxX if its closer to the edge the enemies are traveling to we will
 * store this new value.
 */
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

/*
 * We loop through the list and lower every enemy to the next y value
 */
void ControllerEnemy::lowerLevel()
{
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                current->setY(current->getY() - 0.05f);
        }
}

/*
 * We loop through the list of enemies and check each hitbox with the hitbox of the other controller.
 */
bool ControllerEnemy::collides(class Controller& otherController)
{
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {

                model = current;

                std::pair<float, float> cornerL1 = getHitboxLeftCorner();
                std::pair<float, float> cornerL2 = otherController.getHitboxLeftCorner();
                std::pair<float, float> cornerR1 = getHitboxRightCorner();
                std::pair<float, float> cornerR2 = otherController.getHitboxRightCorner();

                // if squares are next to or above/under each other
                if ((cornerL1.first > cornerR2.first || cornerL2.first > cornerR1.first) ||
                    (cornerR1.second > cornerL2.second || cornerL1.second < cornerR2.second)) {
                        continue;
                }

                return true;
        }
        model = start;
        return false;
}

/*
 * We loop through the list and check for the enemy that has to be deleted.
 * if we find it we then rearange the pointers of the enemies before and after it to make it so we can safely remove
 * the enemy without breaking the chain.
 * Special cases are commented in code itself.
 */
void ControllerEnemy::removeEnemy()
{
        std::shared_ptr<EntityEnemy> current = start;
        std::shared_ptr<EntityEnemy> wanted = std::static_pointer_cast<EntityEnemy>(model);
        if (getEnemysize() == 1) { // if we have to delete the last enemy, consider the controller expired
                model = nullptr;
                start = nullptr;
                expired = true;
                return;
        }
        if (current.get() == wanted.get()) { // to be removed == first element
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

/*
 * We resolve the collision on the enemy the model pointer is currently pointing at. If it runs out of lives we
 * tell the graphics and remove the enemy from the list.
 */
int ControllerEnemy::onCollision(Controller& other)
{
        if (other.isDeadly()) {
                takeDamage(1);
                if (model->getLives() < 1) {
                        notify(*this, Events::event::expired);
                        removeEnemy();
                        return 0;
                }
        }
        return 0;
}

/*
 * To see if there is an enemy infront of the given enemy we have to loop through the chain and check if there is a
 * enemy with a lower y-position but the same x-position. The reason we dont use the "==" operator is because we store
 * position in floats, this leads to small errors because of rounding so we have to check using the epsilon.
 */
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

/*
 * We check if there are enemies whos fireCooldown is 0 and have no other enemies infront of them. if this is the case
 * we add them to a ready vector and return them.
 */
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

/*
 * We find the enemy with the lowest posY value
 */
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

void ControllerEnemy::setLives(int lives)
{
        for (std::shared_ptr<EntityEnemy> current = start; current != nullptr; current = current->getNextEnemy()) {
                current->setLives(lives);
        }
}
