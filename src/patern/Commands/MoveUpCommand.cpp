//
// Created by timsa on 23-Dec-19.
//

#include "MoveUpCommand.h"
#include "Controller.h"

void MoveUpCommand::execute(Controller &controller) {
    controller.moveUp();
}
