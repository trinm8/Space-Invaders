//
// Created by timsa on 04-Dec-19.
//

#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Stopwatch.h"

Game::Game() {

}


int Game::run()
{
    srand(time(NULL));

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(screensizex, screensizey), "Danny invaders");

    graphicsmanager = std::make_shared<SFMLmanager>(window);

    initGame();

    Global::Stopwatch::startGame();

    while(window->isOpen())
    {
        //auto start = std::chrono::system_clock::now();
        Global::Stopwatch::startClock();

        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window->close();
            }

            /*if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }*/
        }

        //std::cout << "start" << std::endl;

        while(Global::Stopwatch::isLaggingBehind()) {

            update();

            Global::Stopwatch::updateLag();

            //std::cout << "loop" << std::endl;
        }

        //std::cout << "stop" << std::endl;

        Global::Stopwatch::calculateDelta();

        //std::cout << graphicsmanager.use_count() << std::endl;

        window->clear();

        graphicsmanager->draw();

        window->display();

        //Global::Stopwatch::sleep();

        //Global::Stopwatch::startGame();

        //std::this_thread::sleep_for(start + std::chrono::milliseconds (MS_PER_UPDATE) - std::chrono::system_clock::now());
    }

    return 0;
}

int Game::initGame() {
    currentLevel = std::make_unique<WorldController>(graphicsmanager);
    currentLevel->initLevel(controllers, graphicsmanager, 1);
    //controllers.push_back(std::make_shared<ControllerPlayer>(manager));
    //controllers.push_back(std::make_shared<ControllerEnemy>(10, manager, 1));
    return 0;
}

int Game::update() {
    for (int i = 0; i < controllers.size(); ++i) {
        controllers[i]->update(controllers);
    }
    currentLevel->update(controllers);
    fixNewEntities();
    collisionChecks();
    expiredRemove();
    if(currentLevel->LevelComplete()){
        if(loadnextlevel() == 1){
            controllers.clear();
            return 0;
        }
    }
    if(currentLevel->gameOver()){
        controllers.clear();
        graphicsmanager->gameover("GAME OVER , EARTH IS KILL , NO");
    }
    return 0;
}

bool Game::offscreen(float posX, float posY) {
    return (0 < posY || posY < -MaxLogicY) || (0 > posX || posX > MaxLogicX);
}

int Game::collisionChecks() {
    for (int i = 0; i < controllers.size(); ++i) {
        for (int j = i+1; j < controllers.size(); ++j) {
            if(controllers[i]->collides(*controllers[j])){
                controllers[i]->onCollision(*controllers[j]);
                controllers[j]->onCollision(*controllers[i]);
            }
        }
    }
    return 0;
}

int Game::expiredRemove() {
    for (int i = 0; i < controllers.size(); ++i) {
        if (controllers[i]->isExpired()) {
            //controllers[i].reset();
            controllers.erase(controllers.begin() + i);
        }
    }
    return 0;
}

int Game::fixNewEntities() {
    for (int i = 0; i < controllers.size(); ++i) {
        if(!controllers[i]->hasObserver()){
            controllers[i]->addObserver(graphicsmanager);
            controllers[i]->gotObserver();
        }
    }
    return 0;
}

int Game::loadnextlevel() {
    int nextLevel = currentLevel->getLevelnr()+1;
    currentLevel->close();
    expiredRemove();
    if(currentLevel->isLast()) {
        graphicsmanager->gameover("YOU WIN");
        graphicsmanager->clearAll();
        return 1;
    }
    currentLevel = std::make_unique<WorldController>(graphicsmanager);
    currentLevel->initLevel(controllers, graphicsmanager, nextLevel);
    return 0;
}
