//
// Created by timsa on 23-Dec-19.
//

#ifndef SMFL_TEST_STOPWATCH_H
#define SMFL_TEST_STOPWATCH_H

#include <chrono>

namespace Global {

    class Stopwatch {

        Stopwatch(){}

        static std::chrono::system_clock::time_point previousStart;
        static std::chrono::system_clock::time_point startInterval;

        static double lag;
        static double elapsed;

    public:

        static void startGame();

        static bool isLaggingBehind();

        static void updateLag();

        static float getDeltaTime();

        static void startClock();

    };

}

#endif //SMFL_TEST_STOPWATCH_H
