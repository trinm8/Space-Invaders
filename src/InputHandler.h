//
// Created by timsa on 16-Dec-19.
//

#ifndef SMFL_TEST_INPUTHANDLER_H
#define SMFL_TEST_INPUTHANDLER_H

#include <memory>

class Command;

class InputHandler {


public:

    std::unique_ptr<Command> handleInput();

private:

    InputHandler();

    std::unique_ptr<Command> LeftButton;
    std::unique_ptr<Command> RightButton;
    std::unique_ptr<Command> UpButton;

};


#endif //SMFL_TEST_INPUTHANDLER_H
