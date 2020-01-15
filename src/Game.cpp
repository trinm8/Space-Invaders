//
// Created by timsa on 04-Dec-19.
//

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "ControllerPlayer.h"
#include "InputHandler.h"
#include "Defines.h"

Game::Game() {

}


int Game::run()
{
    sf::RenderWindow window(sf::VideoMode(screensizex, screensizey), "Danny invaders");

    graphicsmanager = SFMLmanager(window);

    initGame(graphicsmanager);

    while(window.isOpen())
    {
        auto start = std::chrono::system_clock::now();

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }

            /*if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }*/
        }

        update();

        window.clear();

        graphicsmanager.draw();

        window.display();

        std::this_thread::sleep_for(start + std::chrono::milliseconds (MS_PER_UPDATE) - std::chrono::system_clock::now());
    }
    return 0;
}

int Game::initGame(SFMLmanager& manager) {
    controllers.push_back(std::make_unique<ControllerPlayer>(manager));
    return 0;
}

int Game::update() {
    for (int i = 0; i < controllers.size(); ++i) {
        controllers[i]->update(controllers);
        if(offscreen(controllers[i]->getModel()->getX(), controllers[i]->getModel()->getY())){
            controllers[i].release();
            controllers.erase(controllers.begin() + i);
        }
    }
    return 0;
}

bool Game::offscreen(float posX, float posY) {
    return (0 < posY || posY < -MaxLogicY) || (0 > posX || posX > MaxLogicX);
}
