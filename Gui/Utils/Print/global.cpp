#include "global.h"
#include <iomanip>

void printX (const cv::Mat& mat) {
//    std::ostream& out = std::cout;
    std::cout << "Rows cols channels type" << std::endl << mat.rows << " " << mat.cols << " " << mat.channels() << " " << mat.type() << std::endl;
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            std::cout << "Row col " << i << " " << j << std::endl;
            cv::Scalar s = cv::mean(mat(cv::Rect(j,i,1,1)));
            for (int k = 0; k < mat.channels(); ++k) {
                std::cout << s[k] << " ";
            }
            std::cout << std::endl;
        }
    }
//    return out;
}

double sqr(double x) {
    return x*x;
}
