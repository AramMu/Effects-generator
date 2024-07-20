#ifndef TIMEMEASURE_H
#define TIMEMEASURE_H
#include <chrono>

class TimeMeasure {
public:
    TimeMeasure();
    void start();
    void finish();
    long long getDif();
    long long getDifMicro();
private:
    std::chrono::steady_clock::time_point mStart;
    std::chrono::steady_clock::time_point mFinish;
};

#endif // TIMEMEASURE_H
