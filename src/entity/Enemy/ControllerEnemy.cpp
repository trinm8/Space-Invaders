//
// Created by timsa on 14-Jan-20.
//

#include "ControllerEnemy.h"
#include "EntityEnemy.h"

int ControllerEnemy::update(std::vector<std::unique_ptr<Controller>> &controller) {
    return 0;
}

//we create a linked list of enemies and will parse through them to update each one of them
ControllerEnemy::ControllerEnemy(int enemyCount, Observer& SFMLmanager) {
    std::shared_ptr<EntityEnemy> prev;
    model = prev;
    SFMLmanager.onNotify()
    for (int i = 0; i < enemyCount-1; ++i) {
        std::shared_ptr<EntityEnemy> created(prev);
        prev = created;
    }

}
