#ifndef GLOBAL_H
#define GLOBAL_H
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
//#define MESSAGE(msg)

#define ERROR(msg) std::cerr << "Error: " << msg << "\nin " << __FILE__ << " line " << __LINE__ << std::endl;\
    exit(-1);

#define ERROR_NOT_IMPL(msg) std::cerr << "Not implemented: " << msg << "\nin " << __FILE__ << " line " << __LINE__ << std::endl;\
    exit(-1);

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        out << vec[i] << std::endl;
    }
    return out;
}

//std::ostream& operator << (std::ostream& out, const cv::Mat& mat) {

double sqr(double x);

void printX (const cv::Mat& mat);
#endif // GLOBAL_H
