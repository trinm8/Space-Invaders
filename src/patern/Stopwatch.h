//
// Created by timsa on 23-Dec-19.
//

#ifndef SMFL_TEST_STOPWATCH_H
#define SMFL_TEST_STOPWATCH_H

#include <chrono>

namespace Global {

    class Stopwatch {

        Stopwatch(){}

        static std::chrono::steady_clock::time_point previousStart;
        static std::chrono::steady_clock::time_point startInterval;

        static int TICKS_PER_SECOND;
        static int SKIP_TICKS;
        static int MAX_FRAMESKIP;
        static float deltatime;
        static int loops;
        static double lag;
        static double elapsed;

    public:

        static void startGame();

        static bool isLaggingBehind();

        static void updateLag();

        static void calculateDelta();

        static float getDeltaTime();

        static void startClock();

        static void sleep();

    };

}

#endif //SMFL_TEST_STOPWATCH_H
