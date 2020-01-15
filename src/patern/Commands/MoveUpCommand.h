//
// Created by timsa on 23-Dec-19.
//

#ifndef SMFL_TEST_MOVEUPCOMMAND_H
#define SMFL_TEST_MOVEUPCOMMAND_H

#include "Command.h"

class MoveUpCommand: public Command {
public:
    void execute(Controller& controller);
};


#endif //SMFL_TEST_MOVEUPCOMMAND_H
