//
// Created by timsa on 16-Dec-19.
//

#ifndef SMFL_TEST_COMMAND_H
#define SMFL_TEST_COMMAND_H

class Controller;

class Command {

public:
    virtual ~Command(){}
    virtual void execute(Controller& actor) = 0;
};


#endif //SMFL_TEST_COMMAND_H
