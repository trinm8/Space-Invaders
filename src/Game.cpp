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

        // we keep the game running as long as the window is opened
        while (window->isOpen()) {
                Global::Stopwatch::startClock();

                // SFML keeps track if there are any changes to the window it self
                sf::Event event{};
                while (window->pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                window->close();
                        }
                }

                // we ask the stopwatch if we are lagging behind on our wanted ticks, if so we keep looping until the
                // lag is gone
                while (Global::Stopwatch::isLaggingBehind()) {

                        update();

                        Global::Stopwatch::updateLag();
                }

                // we calculate how long it took for the update phase so we now how much interpolation in the graphics
                // need to be done
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
        // we tell every controller to update itself, we give the controllers acces to the list of the controllers so
        // they can add new game objects of their own (bullets for example). Because we can add new entities in the
        // vector we dont use a range loop.
        for (int i = 0; i < controllers.size(); i++) {
                controllers[i]->update(controllers);
        }
        currentLevel->update(controllers);   // we tell the level to update itself
        fixNewEntities();
        collisionChecks();
        expiredRemove();
        if (currentLevel->LevelComplete()) {
                if (loadnextlevel() == 1) { // return 1 = Victory
                        graphicsmanager->gameover("YOU WIN");
                        graphicsmanager->clearAll();
                        controllers.clear();
                        return 0;
                }
        }
        if (currentLevel->gameOver()) {
                controllers.clear();
                graphicsmanager->gameover("GAME OVER");
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
                return 1;
        }
        currentLevel = std::make_unique<WorldController>(graphicsmanager);
        currentLevel->initLevel(controllers, graphicsmanager, nextLevel);
        return 0;
}

int Game::render() { return graphicsmanager->draw(); }
