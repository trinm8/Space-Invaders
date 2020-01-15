//x
// Created by timsa on 20-Dec-19.
//

#ifndef SMFL_TEST_TRANSFORMATION_H
#define SMFL_TEST_TRANSFORMATION_H

namespace Global {

    class Transformation {

        static int screensizeX, screensizeY;
        static float maxLogicX, maxLogicY;

        Transformation(){};

    public:

        static void update(int screensizeX, int screensizeY);

        static float transformationX(float x);

        static float scaleX(float screensize);

        static float transformationY(float y);

        static float scaleY(float screensize);

    };
}


#endif //SMFL_TEST_TRANSFORMATION_H
