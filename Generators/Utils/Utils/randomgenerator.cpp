#include "randomgenerator.h"
#include "calc.h"
#include <ctime>

RandomGenerator::RandomGenerator(int rows, int cols) :
    rows(rows),
    cols(cols)
{}

std::mt19937& RandomGenerator::getGen() {
    static std::mt19937 gen(time (nullptr));
    return gen;
}

std::uniform_real_distribution<double>& RandomGenerator::getDist() {
    static std::uniform_real_distribution<double> dist(0,1);
    return dist;
}

int RandomGenerator::randY () {
    return getDist() (getGen()) * rows;
}

int RandomGenerator::randX () {
    return getDist() (getGen()) * cols;
}
double RandomGenerator::randAngle () {
    return getDist() (getGen()) * 2*PI;
}
double RandomGenerator::randRadius () {
    return getDist() (getGen()) * (std::min (cols, rows)/2-5);
}

double RandomGenerator::randProb () {
    return getDist() (getGen());
}

int RandomGenerator::randInt(int e) {
    return getDist() (getGen()) * e;
}

double RandomGenerator::randDouble (double e) {
    return getDist() (getGen()) * e;
}

int RandomGenerator::randInt(int b, int e) {
    return Calc::floor(getDist() (getGen()) * (e-b) + b);
}

double RandomGenerator::randDouble (double b, double e) {
    return getDist() (getGen()) * (e-b) + b;
}

cv::Vec3b RandomGenerator::randBrightColor () {
    cv::Vec3b res;
    int c = randInt (0,3);
    res[c] = 255;
    for (int i = 0; i < 3; ++i) {
        if (i == c) continue;
        res[i] = uchar (randInt (0,256));
    }
    return res;
}

cv::Vec3b RandomGenerator::randColor () {
    int val = randInt(0, 256*256*256-1);
    return cv::Vec3b (val%256, (val/256)%256, (val/256)/256);
}

cv::Point2i RandomGenerator::randPointCart() {
    return cv::Point2i (randInt(0, cols-1), randInt(0, rows-1));
}

cv::Point2i RandomGenerator::randPointPolar() {
    double r = randRadius();
    double ang = randAngle();
    return cv::Point2i (r*Calc::cos(ang)+cols/2, r*Calc::sin(ang)+rows/2);
}

cv::Point2i RandomGenerator::randPointCartD() {
    return cv::Point2d (randDouble(0, cols-1), randDouble(0, rows-1));
}

cv::Point2i RandomGenerator::randPointPolarD() {
    double r = randRadius();
    double ang = randAngle();
    //assert (r*Calc::cos(ang)+cols/2-1 < cols && r*Calc::sin(ang)+rows/2-1 < rows);
    return cv::Point2d (r*Calc::cos(ang)+cols/2-1, r*Calc::sin(ang)+rows/2-1);
}
