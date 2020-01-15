//
// Created by timsa on 20-Dec-19.
//

#include "Transformation.h"
#include "Defines.h"

int Global::Transformation::screensizeX = screensizex;
int Global::Transformation::screensizeY = screensizey;
float Global::Transformation::maxLogicX = MaxLogicX;
float Global::Transformation::maxLogicY = MaxLogicY;

float Global::Transformation::transformationX(float x) {
    return ((float)screensizeX/maxLogicX)*x ;
}

float Global::Transformation::transformationY(float y) {
    return -((float)screensizeY/maxLogicY)*y ;
}

void Global::Transformation::update(int screensizeX, int screensizeY) {
    Transformation::screensizeX = screensizeX;
    Transformation::screensizeY = screensizeY;
}

float Global::Transformation::scaleX(float screensize) {
    return screensize/(float)defaultscreenX;
}

float Global::Transformation::scaleY(float screensize) {
    return screensize/(float)defaultscreenY;
}
