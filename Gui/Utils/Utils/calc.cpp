#include "calc.h"
//#include <cmath>
#include <fstream>

int Calc::n;
std::vector <double> Calc::val;
bool Calc::load (const std::string& fileName) {
    std::ifstream in;
    in.open(fileName);
    in >> n;
    val = std::vector <double> (n);
    for (int i = 0; i < n; ++i) {
        in >> val[i];
    }
    int k = n/100;
    n--;
    for (int i = 1; i <= k; ++i) {
        val.push_back (val[n-i]);
    }
    in.close();
    return true;
}





std::vector<double> Calc::solveLinear (const Matrix<double>& input) {
    Matrix <double> mat(input.rows, input.cols);
    for (int i = 0; i < input.rows; ++i) {
        for (int j = 0; j < input.cols; ++j) {
            mat.at(i,j) = input.at(i,j);
        }
    }
    assert (mat.cols == mat.rows+1);
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = i+1; j < mat.rows; ++j) {
            double d = -mat.at(j,i)/mat.at(i,i);
            for (int k = i; k < mat.cols; ++k) {
                mat.at(j,k) += d*mat.at(i,k);
            }
        }
    }
    for (int i = mat.rows-1; i >= 0; --i) {
        for (int j = 0; j < i; ++j) {
            double d = -mat.at(j,i)/mat.at(i,i);
            for (int k = i; k < mat.cols; ++k) {
                mat.at(j,k) += d*mat.at(i,k);
            }
        }
    }
    std::vector<double> res(mat.rows);
    for (int i = 0; i < mat.rows; ++i) {
        res[i] = mat.at(i, mat.cols-1) / mat.at(i,i);
    }
    return res;
}



















