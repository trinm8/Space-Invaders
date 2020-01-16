//
// Created by timsa on 23-Dec-19.
//

#include "Stopwatch.h"
#include "Defines.h"
#include <chrono>

std::chrono::steady_clock::time_point Global::Stopwatch::previousStart = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point Global::Stopwatch::startInterval = std::chrono::steady_clock::now();

int Global::Stopwatch::maxSkip = 5;
int Global::Stopwatch::loops;
float Global::Stopwatch::deltatime;
double Global::Stopwatch::lag;
double Global::Stopwatch::elapsed;

void Global::Stopwatch::startClock()
{
        startInterval = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(startInterval - previousStart).count();
        previousStart = startInterval;
        lag += elapsed;
        loops = 0;
}

bool Global::Stopwatch::isLaggingBehind() { return lag >= MS_PER_UPDATE && loops < maxSkip; }

void Global::Stopwatch::updateLag()
{
        lag -= MS_PER_UPDATE;
        loops++;
}

void Global::Stopwatch::startGame() { previousStart = std::chrono::steady_clock::now(); }

float Global::Stopwatch::getDeltaTime() { return deltatime; }

void Global::Stopwatch::calculateDelta() { deltatime = (float)(lag / MS_PER_UPDATE); }
