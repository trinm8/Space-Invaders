//
// Created by timsa on 23-Dec-19.
//

#include "Stopwatch.h"
#include "Defines.h"
#include <iostream>
#include <chrono>
#include <thread>

std::chrono::system_clock::time_point Global::Stopwatch:: previousStart;
std::chrono::system_clock::time_point Global::Stopwatch::startInterval;

double Global::Stopwatch::lag;
double Global::Stopwatch::elapsed;


void Global::Stopwatch::startClock() {
    startInterval = std::chrono::system_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(startInterval - previousStart).count();
    //std::cout << elapsed.count() << std::endl;
    previousStart = startInterval;
    lag += elapsed;
}

bool Global::Stopwatch::isLaggingBehind() {
    //std::cout << lag << std::endl;
    return lag >= MS_PER_UPDATE;
}

void Global::Stopwatch::updateLag() {
    lag = lag - MS_PER_UPDATE;
}

void Global::Stopwatch::startGame() {
    previousStart = std::chrono::system_clock::now();
}

float Global::Stopwatch::getDeltaTime() {
    //std::cout << MS_PER_UPDATE/lag << std::endl;
    return lag/MS_PER_UPDATE;
}
