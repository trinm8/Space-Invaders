//
// Created by timsa on 23-Dec-19.
//

#include "Stopwatch.h"
#include "Defines.h"
#include <chrono>

std::chrono::steady_clock::time_point Global::Stopwatch::previousStart = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point Global::Stopwatch::startInterval = std::chrono::steady_clock::now();

int Global::Stopwatch::loops;
float Global::Stopwatch::deltatime;
double Global::Stopwatch::lag;
double Global::Stopwatch::elapsed;

/*
 * We use a steady clock to mark the start of the game loop.
 * Then we check what the duration was of the previous game loop by comparing the last interval start.
 * we reset the previousStart so it will save the current start.
 * we then calculate the lag. this is to make sure that the game runs smooth on every system. if we are lagging behind
 * we have to update multiple time.
 * we also keep track of how many times we have updated without rendering to make sure we aren't only updating. So we
 * have to reset the loop counter.
 */
void Global::Stopwatch::startClock()
{
        startInterval = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(startInterval - previousStart).count();
        previousStart = startInterval;
        lag += elapsed;
        loops = 0;
}

/*
 * We check if the lag is bigger then the amout of time it would take to update. also check if we havent updated too much
 */
bool Global::Stopwatch::isLaggingBehind() { return lag >= MS_PER_UPDATE && loops < 10; }

/*
 * every update we substract the amount of time it would to for a single update from our lag value and increase the
 * loops because we have just done a single loop of updating.
 */
void Global::Stopwatch::updateLag()
{
        lag -= MS_PER_UPDATE;
        loops++;
}

void Global::Stopwatch::startGame() { previousStart = std::chrono::steady_clock::now(); }

float Global::Stopwatch::getDeltaTime() { return deltatime; }

/*
 * Deltatime is used by the graphics as a predication of where the graphics should be. This is because if the render and
 * render gets executed too far from each other the entities would have moved further then would be represented on screen.
 * so we calculate an interpolation to see how much further we need to draw the sprites. This also why it is a normalized
 * value.
 */
void Global::Stopwatch::calculateDelta() { deltatime = (float)(lag / MS_PER_UPDATE); }
