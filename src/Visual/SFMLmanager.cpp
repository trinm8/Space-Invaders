//
// Created by timsa on 05-Dec-19.
//

#include "SFMLmanager.h"
#include <utility>
#include "Controller.h"

int SFMLmanager::placeholder() {
    sf::Music music;
    if (!music.openFromFile("danny.wav"))
        return -1;
    music.play();
    return 0;
}

SFMLmanager::SFMLmanager(std::shared_ptr<sf::RenderWindow> window) {
    this->window = std::move(window);
    sf::Text health;
    this->font = std::make_shared<sf::Font>();
    if (!font->loadFromFile("Assests/letters.ttf"))
    {

    }
    health.setFont(*font);
    health.setString("Health");
    health.setCharacterSize(30);
    health.setStyle(sf::Text::Bold);
    health.setFillColor(sf::Color::White);
    playerLife = std::make_shared<sf::Text>(health);
    texts.push_back(playerLife);
    once = false;
}

const std::shared_ptr<sf::RenderWindow> &SFMLmanager::getWindow() const {
    return window;
}

int SFMLmanager::draw() {

    for(auto itr : views){
        itr->update(window);
    }

    for (int i = 0; i < texts.size(); ++i) {
        window->draw(*texts[i]);
    }

    return 0;
}

void SFMLmanager::onNotify(Controller& controller, Events::event event) {
    if(event == Events::event::Win){
        //TODO::zorgen dat er maar 1 game over is
        gameover("YOU WIN");
    }
    if(event == Events::event::UpdatePlayerHealth){
        playerLife->setString("Health " + std::to_string(controller.getModel()->getLives()));
        return;
    }
    if(event == Events::event::Expired){
        for (int i = views.size()-1; i > -1; --i) {
            if(controller.getModel().get() == views[i]->getModel().get() ){
                views.erase(views.begin()+i);
                return;
            }
        }
    }

    sf::Texture texture;
    switch (event){
        case Events::event::CreatePlayerView: {

            if (!texture.loadFromFile("Assests/danny.png")) {
                return;
            }

            break;
        }
        case Events::event::CreateBulletView: {
            //controller.addObserver(std::make_shared<SFMLmanager>(*this));
            if(!texture.loadFromFile("Assests/sprint.png")){
                return;
            }

            break;
        }
        case Events::event::CreateEnemyView : {
            if(!texture.loadFromFile("Assests/Enemy.png")){
                return;
            }
        }
        default:{

        }
    }
    texture.setSmooth(true);
    std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
    views.push_back(std::make_shared<View>(std::make_shared<sf::Texture>(texture), sprite, controller.getModel(),
                                           window->getSize().x, window->getSize().y));
}

void SFMLmanager::clearAll() {
    views.clear();
}

void SFMLmanager::gameover(const std::string& message) {

    if(once)
        return;

    sf::Text text;
    text.setFont(*font);
    text.setString(message);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);

    //text.setPosition(400, 400);
    texts.clear();
    texts.push_back(std::make_shared<sf::Text>(std::move(text)));
    //texts.push_back(std::make_shared<sf::Text>(text));
    once = true;
}

