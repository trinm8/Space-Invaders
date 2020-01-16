//
// Created by timsa on 26-Dec-19.
//

#ifndef SMFL_TEST_HITBOX_H
#define SMFL_TEST_HITBOX_H

class Hitbox
{
        float w, h;

public:
        Hitbox() = default;

        Hitbox(float w, float h);

        void setW(float newW);

        void setH(float newH);

        float getW() const;

        float getH() const;
};

#endif // SMFL_TEST_HITBOX_H
