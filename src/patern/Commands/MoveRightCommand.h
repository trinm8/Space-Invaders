//
// Created by timsa on 16-Dec-19.
//

#ifndef SMFL_TEST_MOVERIGHTCOMMAND_H
#define SMFL_TEST_MOVERIGHTCOMMAND_H

#include "Command.h"

class MoveRightCommand: public Command {

public:
    void execute(Controller& controller);
};


#endif //SMFL_TEST_MOVERIGHTCOMMAND_H
