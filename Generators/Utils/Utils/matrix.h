#ifndef MATRIX
#define MATRIX
//#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>
#include <cassert>
//#include

template <class T>
class Matrix {
public:
    Matrix (size_t rows, size_t cols);
    Matrix (size_t rows, size_t cols, const T& value);
    Matrix (const cv::Size& size);
    Matrix (const cv::Size& size, const T& value);

    ~Matrix();

    T& at (int y, int x);
    const T& at(int y, int x) const;
    T& at (const cv::Point& p);
    const T& at(const cv::Point& p) const;
    void fill (const T& value);
    const cv::Size size() const;

    T* data;
    const size_t rows;
    const size_t cols;


private:
    Matrix();
    Matrix& operator = (const Matrix& m);
    Matrix (const Matrix& m);
};


template <class T>
Matrix<T>::Matrix (size_t rows, size_t cols) : rows(rows), cols(cols) {
    data = new T[rows*cols];
}

template <class T>
Matrix<T>::Matrix (size_t rows, size_t cols, const T& value) : rows(rows), cols(cols) {
    data = new T[rows*cols];
    fill(value);
}

template <class T>
Matrix<T>::Matrix (const cv::Size& size) : rows(size.height), cols(size.width) {
    data = new T[rows*cols];
}

template <class T>
Matrix<T>::Matrix (const cv::Size& size, const T& value) : rows(size.height), cols(size.width) {
    data = new T[rows*cols];
    fill(value);
}

template <class T>
Matrix<T>::~Matrix() {
    delete[] data;
}

template <class T>
const cv::Size Matrix<T>::size() const {
    return cv::Size(cols,rows);
}

template <class T>
inline T& Matrix<T>::at (int y, int x) {
    assert (y >= 0 && y < rows);
    assert (x >= 0 && x < cols);
    return data [y*cols + x];
}

template <class T>
inline const T& Matrix<T>::at(int y, int x) const {
    assert (y >= 0 && y < rows);
    assert (x >= 0 && x < cols);
    return data [y*cols + x];
}


template <class T>
inline T& Matrix<T>::at (const cv::Point& p) {
    assert (p.y >= 0 && p.y < rows);
    assert (p.x >= 0 && p.x < cols);
    return data [p.y*cols + p.x];
}

template <class T>
inline const T& Matrix<T>::at(const cv::Point& p) const {
    assert (p.y >= 0 && p.y < rows);
    assert (p.x >= 0 && p.x < cols);
    return data [p.y*cols + p.x];
}


template <class T>
void Matrix<T>::fill (const T& fill) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i*cols + j] = fill;
        }
    }
}



#endif // MATRIX
