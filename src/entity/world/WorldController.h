//
// Created by timsa on 04-Dec-19.
//

#ifndef SMFL_TEST_WORLDCONTROLLER_H
#define SMFL_TEST_WORLDCONTROLLER_H

#include "Controller.h"
#include "ControllerEnemy.h"
#include "ControllerPlayer.h"

class WorldController : public Controller
{

        std::shared_ptr<ControllerPlayer> currentPlayer;
        std::shared_ptr<ControllerEnemy> currentEnemies;
        int levelnr;
        bool last;

public:
        explicit WorldController(const std::shared_ptr<Observer>& sfmLmanager);

        int initLevel(std::vector<std::shared_ptr<Controller>>& controllers,
                      const std::shared_ptr<Observer>& SFMLmanager, int levelnr);

        int update(std::vector<std::shared_ptr<Controller>>& controller) override;

        int onCollision(Controller& other) override;

        bool LevelComplete();

        bool gameOver();

        [[nodiscard]] int getLevelnr() const;

        bool isLast() const;

        int close();
};

#endif // SMFL_TEST_WORLDCONTROLLER_H
