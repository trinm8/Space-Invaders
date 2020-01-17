//
// Created by timsa on 04-Dec-19.
//

#include "WorldController.h"
#include "json.hpp"
#include <fstream>

int WorldController::update(std::vector<std::shared_ptr<Controller>>& controller)
{
        if (currentEnemies != nullptr && currentEnemies->isExpired()) {
                currentEnemies = nullptr;
        }
        return 0;
}

int WorldController::onCollision(Controller& other) { return 0; }

int WorldController::initLevel(std::vector<std::shared_ptr<Controller>>& controllers,
                               const std::shared_ptr<Observer>& SFMLmanager, int expectedLevelNr)
{
        std::ifstream levelfile;
        nlohmann::json jsonparser;
        levelnr = expectedLevelNr;
        levelfile.open("Assests/Levels/level" + std::to_string(levelnr) + ".json");
        levelfile >> jsonparser;
        last = jsonparser["last"];
        std::string location;
        location = jsonparser["enemy"]["texture"];
        int enemycount;
        int lives;
        try {
                enemycount = jsonparser["enemy"]["enemycount"];
                lives = jsonparser["enemy"]["lives"];

                if (enemycount < 1) {
                        throw 1;
                } else if (enemycount > 21) {
                        throw 2;
                }
                if (lives < 1) {
                        throw 3;
                }
        } catch (int error) {
                switch (error) {
                case 1: {
                        enemycount = 1;
                        std::cerr << "not Enough Enemies, changing to 1" << std::endl;
                        break;
                }
                case 2: {
                        enemycount = 21;
                        std::cerr << "Too many enemies, changing to 21" << std::endl;
                        break;
                }
                case 3: {
                        lives = 1;
                        std::cerr << "Lives cant be empty/negative, changing to 1" << std::endl;
                        break;
                }
                default: {
                }
                }
        }

        currentEnemies = std::make_shared<ControllerEnemy>(enemycount, SFMLmanager, "Assests/" + location);
        currentEnemies->setLives(lives);

        location = jsonparser["player"]["texture"];
        currentPlayer = std::make_shared<ControllerPlayer>(SFMLmanager, "Assests/" + location);
        try {
                lives = jsonparser["player"]["lives"];
                if (lives < 1)
                        throw 1;
        } catch (int error) {
                if (error) {
                        lives = 3;
                        std::cerr << "Lives cant be empty/negative, changing to 3" << std::endl;
                }
        }
        currentPlayer->setLives(lives);

        controllers.push_back(currentPlayer);
        controllers.push_back(currentEnemies);
        levelfile.close();
        return 0;
}

bool WorldController::LevelComplete() { return currentEnemies == nullptr; }

WorldController::WorldController(const std::shared_ptr<Observer>& sfmLmanager) : Controller(sfmLmanager)
{
        last = false;
        levelnr = 0;
}

int WorldController::getLevelnr() const { return levelnr; }

bool WorldController::isLast() const { return last; }

int WorldController::close()
{
        currentPlayer->makeExpired();
        currentEnemies->makeExpired();
        return 0;
}

bool WorldController::gameOver()
{
        return (currentPlayer->getLives() == 0 ||
                currentEnemies->getlowestY() <=
                    currentPlayer->getHitboxLeftCorner().second); // if enemies reached the player
}
