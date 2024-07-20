#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

//#include <iostream>
#include <random>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types.hpp>
//#include <cmath>
//#include <cstdlib>
//#include <windows.h>
//#include <ctime>
//#include "calc.h"

class RandomGenerator {
public:
    RandomGenerator (int rows, int cols);

    cv::Point2i randPointCart();
    cv::Point2i randPointPolar();
    cv::Point2i randPointCartD();
    cv::Point2i randPointPolarD();
    int randY ();
    int randX ();
    double randAngle ();
    double randRadius ();


    static double randProb ();
    static int randInt (int e);
    static double randDouble(double e);
    static int randInt (int b, int e);
    static double randDouble(double b, double e);

    cv::Vec3b randBrightColor ();
    cv::Vec3b randColor ();
private:
    int rows;
    int cols;
    static std::mt19937& getGen();
    static std::uniform_real_distribution<double>& getDist();
    static double rand();
};

#endif // RANDOMGENERATOR_H
