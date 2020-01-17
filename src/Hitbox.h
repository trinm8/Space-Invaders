//
// Created by timsa on 26-Dec-19.
//

#ifndef SMFL_TEST_HITBOX_H
#define SMFL_TEST_HITBOX_H

class Hitbox
{

        /*! \class Hitbox
         *  The Hitbox class will act as an object with only an width and height, these can be used to give an entity a
         * size next to the actual position of the sprite. This class acts as an extra model with only getters and
         * setters.
         */

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
