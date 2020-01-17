// x
// Created by timsa on 20-Dec-19.
//

#ifndef SMFL_TEST_TRANSFORMATION_H
#define SMFL_TEST_TRANSFORMATION_H

namespace Global {

class Transformation
{
        /*! \class Transformation
         *  The transformation class is a singleton class that acts as a converter between in logic and visual
         * coordinates.
         */
        static int screensizeX, screensizeY;
        static float maxLogicX, maxLogicY;

        Transformation() = default;

public:
        static void update(int newScreensizeX, int newScreensizeY);

        static float transformationX(float x);

        static float scaleX(float screensize);

        static float transformationY(float y);

        static float scaleY(float screensize);
};
} // namespace Global

#endif // SMFL_TEST_TRANSFORMATION_H
