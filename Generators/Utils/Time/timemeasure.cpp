#include "timemeasure.h"

TimeMeasure::TimeMeasure() {}
void TimeMeasure::start() {
    mStart = std::chrono::steady_clock::now();
}
void TimeMeasure::finish() {
    mFinish = std::chrono::steady_clock::now();
}
long long TimeMeasure::getDif() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(mFinish - mStart).count();
}
long long TimeMeasure::getDifMicro() {
    return std::chrono::duration_cast<std::chrono::microseconds>(mFinish - mStart).count();
}
