//
// Created by timsa on 23-Dec-19.
//

#include "Stopwatch.h"
#include "Defines.h"
#include <chrono>
#include <thread>

std::chrono::steady_clock::time_point Global::Stopwatch:: previousStart = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point Global::Stopwatch::startInterval = std::chrono::steady_clock::now();

int Global::Stopwatch::TICKS_PER_SECOND = 25;
int Global::Stopwatch::SKIP_TICKS = 10000 / TICKS_PER_SECOND;;
int Global::Stopwatch::MAX_FRAMESKIP = 5;
int Global::Stopwatch::loops;
float Global::Stopwatch::deltatime;
double Global::Stopwatch::lag;
double Global::Stopwatch::elapsed;


void Global::Stopwatch::startClock() {
    startInterval = std::chrono::steady_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(startInterval - previousStart).count();
    //deltatime = (float)elapsed;
    previousStart = startInterval;
    lag += elapsed;
    loops = 0;
}

bool Global::Stopwatch::isLaggingBehind() {
    //std::cout << lag << std::endl;
    return lag >= MS_PER_UPDATE && loops < MAX_FRAMESKIP;
    //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startInterval).count() << std::endl;
    //return std::chrono::steady_clock::now() > startInterval && loops < MAX_FRAMESKIP;
}

void Global::Stopwatch::updateLag() {
    lag -= MS_PER_UPDATE;
    loops++;
    //startInterval += std::chrono::milliseconds(SKIP_TICKS);
}

void Global::Stopwatch::startGame() {
    previousStart = std::chrono::steady_clock::now();
    //previousStart = startInterval;
}

float Global::Stopwatch::getDeltaTime() {
    //std::cout << MS_PER_UPDATE/lag << std::endl;
    //return lag/MS_PER_UPDATE;
    return deltatime;
}

void Global::Stopwatch::sleep() {
    std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(previousStart - std::chrono::steady_clock::now() + std::chrono::milliseconds(SKIP_TICKS))/1000);
}

void Global::Stopwatch::calculateDelta() {
    //std::cout << deltatime << std::endl;
    //deltatime = elapsed;
    deltatime = (float)(lag/MS_PER_UPDATE);
    //deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() + std::chrono::milliseconds(SKIP_TICKS) - startInterval).count()/(float)SKIP_TICKS;
}
