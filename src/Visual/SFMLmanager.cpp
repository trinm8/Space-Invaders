//
// Created by timsa on 05-Dec-19.
//

#include "SFMLmanager.h"
#include "ViewPlayer.h"
#include "Controller.h"

int SFMLmanager::placeholder() {
    sf::Music music;
    if (!music.openFromFile("danny.wav"))
        return -1;
    music.play();
    return 0;
}

SFMLmanager::SFMLmanager(sf::RenderWindow& window) {
    this->window = std::shared_ptr<sf::RenderWindow>(&window);
}

const std::shared_ptr<sf::RenderWindow> &SFMLmanager::getWindow() const {
    return window;
}

int SFMLmanager::draw() {

    for(auto itr : views){
        itr->update(window);
    }

    return 0;
}

void SFMLmanager::onNotify(Controller& controller, Events::event event) {
    sf::Texture texture;
    switch (event){
        case Events::event::CreatePlayerView: {

            if (!texture.loadFromFile("Assests/danny.png")) {
                return;
            }

            break;
        }
        case Events::event::CreateBulletView: {
            if(!texture.loadFromFile("Assests/sprint.png")){
                return;
            }
            break;
        }
        default:{

        }
    }
    texture.setSmooth(true);
    std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
    views.push_back(std::make_shared<View>(std::make_shared<sf::Texture>(texture), sprite, controller.getModel(),
                                           window->getSize().x, window->getSize().y));
}
