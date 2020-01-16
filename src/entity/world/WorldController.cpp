//
// Created by timsa on 04-Dec-19.
//

#include "WorldController.h"
#include "json.hpp"
#include <fstream>

int WorldController::update(std::vector<std::shared_ptr<Controller>> &controller) {
    for (int i = 0; i < currentEnemies.size(); ++i) {
        if(currentEnemies[i]->isExpired()){
            currentEnemies.erase(currentEnemies.begin()+i);
            if(i == 0 && !currentEnemies.empty()){
                controller.push_back(std::move(currentEnemies[i]));
            }
            i--;
        }
    }
    return 0;
}



int WorldController::onCollision(Controller &other) {
    return 0;
}


int WorldController::initLevel(std::vector<std::shared_ptr<Controller>> &controllers, const std::shared_ptr<Observer>& SFMLmanager, int levelnr) {
    std::ifstream levelfile;
    nlohmann::json jsonparser;
    this->levelnr = levelnr;
    levelfile.open("Assests/Levels/level" + std::to_string(levelnr) + ".json");
    levelfile >> jsonparser;
    this->last = jsonparser["last"];
    int wavecount = jsonparser["wavecount"];
    for (int i = 0; i != wavecount; ++i) {
        std::string enemyname = "enemy" + std::to_string(i);
        currentEnemies.push_back(std::make_shared<ControllerEnemy>(jsonparser[enemyname]["enemycount"], SFMLmanager, jsonparser[enemyname]["lives"]));
    }

    currentPlayer = std::make_shared<ControllerPlayer>(SFMLmanager);

    controllers.push_back(currentPlayer);
    controllers.push_back(currentEnemies[0]);
    levelfile.close();
    return 0;
}

bool WorldController::LevelComplete() {
    return currentEnemies.empty();
}

WorldController::WorldController(const std::shared_ptr<Observer> &sfmLmanager) : Controller(sfmLmanager) {

}

int WorldController::getLevelnr() const {
    return levelnr;
}

bool WorldController::isLast() const {
    return last;
}

int WorldController::close() {
    currentPlayer->makeExpired();
    return 0;
}

bool WorldController::gameOver() {
    return (currentPlayer->getLives() == 0 || currentEnemies[0]->getlowestY() <= currentPlayer->getHitboxLeftCorner().second);
}

