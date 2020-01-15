//
// Created by timsa on 16-Dec-19.
//

#include <iostream>
#include "InputHandler.h"
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "MoveUpCommand.h"

InputHandler::InputHandler() {
    LeftButton = std::make_unique<MoveLeftCommand>();
    RightButton = std::make_unique<MoveRightCommand>();
    UpButton = std::make_unique<MoveUpCommand>();
}

std::unique_ptr<Command> InputHandler::handleInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return std::move(LeftButton);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return std::move(RightButton);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return std::move(UpButton);

    return nullptr;
}
