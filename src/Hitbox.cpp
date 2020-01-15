//
// Created by timsa on 26-Dec-19.
//

#include "Hitbox.h"

Hitbox::Hitbox(float w, float h) : w(w), h(h) {}

void Hitbox::setW(float w) {
    Hitbox::w = w;
}

void Hitbox::setH(float h) {
    Hitbox::h = h;
}

float Hitbox::getW() const {
    return w;
}

float Hitbox::getH() const {
    return h;
}
