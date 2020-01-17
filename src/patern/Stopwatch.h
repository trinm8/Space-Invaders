//
// Created by timsa on 23-Dec-19.
//

#ifndef SMFL_TEST_STOPWATCH_H
#define SMFL_TEST_STOPWATCH_H

#include <chrono>

namespace Global {

class Stopwatch
{
        /*! \class Stopwatch
         *  The Stopwatch keeps track of the Time that has passed in a current loop of the main game loop. Its in the
         *  singleton pattern so that its accesable everywhere and there is always max a single instance of it.
         */

        Stopwatch() = default;

        static std::chrono::steady_clock::time_point previousStart; /*!< Stop time last game loop */
        static std::chrono::steady_clock::time_point startInterval; /*!< Start current game loop */

        static float deltatime; /*!< Keeps track of how much delay there is between the render and update function*/
        static int loops;       /*!< Keeps track of how many (extra) updates there have been in a single loop */
        static double lag;      /*!< How much the CPU is lagging behind*/
        static double elapsed;

public:
        /*!
         * Starts the clock when the game itself starts
         */
        static void startGame();

        /*!
         * Checks if the CPU is lagging behind, it checks if the lag is bigger then the max allowed time, if this is the
         * case we will keep updating and wait with rendering until we have caught up. If we are lagging behind too much
         * the updating will stop and we will get a render, but the lag isnt reset.
         * @return do we need extra loops to catchup
         */
        static bool isLaggingBehind();

        /*!
         * We calculate how much time has passed between loops.
         */
        static void updateLag();

        /*!
         * We calculate how much interpolation is needed between to update the graphics of our game. This is needed when
         * the CPU is lagging behind and the sprite might already be further then would we represented onscreen.
         */
        static void calculateDelta();

        static float getDeltaTime();

        /*!
         * Resets the clock signalling the start of a new game loop.
         */
        static void startClock();
};

} // namespace Global

#endif // SMFL_TEST_STOPWATCH_H
