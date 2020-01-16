//
// Created by timsa on 26-Dec-19.
//

#include "Hitbox.h"

Hitbox::Hitbox(float w, float h) : w(w), h(h) {}

void Hitbox::setW(float newW) { Hitbox::w = newW; }

void Hitbox::setH(float newH) { Hitbox::h = newH; }

float Hitbox::getW() const { return w; }

float Hitbox::getH() const { return h; }
