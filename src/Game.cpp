//
// Created by timsa on 04-Dec-19.
//

#include "Game.h"
#include "Defines.h"
#include "Stopwatch.h"
#include <SFML/Graphics.hpp>

int Game::run()
{

        std::shared_ptr<sf::RenderWindow> window =
            std::make_shared<sf::RenderWindow>(sf::VideoMode(screensizex, screensizey), "Danny invaders");

        graphicsmanager = std::make_shared<SFMLmanager>(window);

        initGame();

        Global::Stopwatch::startGame();

        while (window->isOpen()) {
                Global::Stopwatch::startClock();

                sf::Event event{};
                while (window->pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                window->close();
                        }
                }

                while (Global::Stopwatch::isLaggingBehind()) {

                        update();

                        Global::Stopwatch::updateLag();
                }

                Global::Stopwatch::calculateDelta();

                render();
        }

        return 0;
}

int Game::initGame()
{
        currentLevel = std::make_unique<WorldController>(graphicsmanager);
        currentLevel->initLevel(controllers, graphicsmanager, 1);
        return 0;
}

int Game::update()
{
        for (int i = 0; i < controllers.size(); i++) {
                controllers[i]->update(controllers);
        }
        currentLevel->update(controllers);
        fixNewEntities();
        collisionChecks();
        expiredRemove();
        if (currentLevel->LevelComplete()) {
                if (loadnextlevel() == 1) {
                        controllers.clear();
                        return 0;
                }
        }
        if (currentLevel->gameOver()) {
                controllers.clear();
                graphicsmanager->gameover("GAME OVER , EARTH IS KILL , NO");
        }
        return 0;
}

int Game::collisionChecks()
{
        for (int i = 0; i < controllers.size(); ++i) {
                for (int j = i + 1; j < controllers.size(); ++j) {
                        if (controllers[i]->collides(*controllers[j])) {
                                controllers[i]->onCollision(*controllers[j]);
                                controllers[j]->onCollision(*controllers[i]);
                        }
                }
        }
        return 0;
}

int Game::expiredRemove()
{
        for (int i = 0; i < controllers.size(); ++i) {
                if (controllers[i]->isExpired()) {
                        controllers.erase(controllers.begin() + i);
                }
        }
        return 0;
}

int Game::fixNewEntities()
{
        for (auto& controller : controllers) {
                if (!controller->hasObserver()) {
                        controller->addObserver(graphicsmanager);
                        controller->gotObserver();
                }
        }
        return 0;
}

int Game::loadnextlevel()
{
        int nextLevel = currentLevel->getLevelnr() + 1;
        currentLevel->close();
        expiredRemove();
        if (currentLevel->isLast()) {
                graphicsmanager->gameover("YOU WIN");
                graphicsmanager->clearAll();
                return 1;
        }
        currentLevel = std::make_unique<WorldController>(graphicsmanager);
        currentLevel->initLevel(controllers, graphicsmanager, nextLevel);
        return 0;
}

int Game::render() { return graphicsmanager->draw(); }
