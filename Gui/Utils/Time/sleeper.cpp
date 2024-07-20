#include "sleeper.h"
#include <chrono>
#include <thread>

Sleeper::Sleeper() {}

Sleeper::~Sleeper() {}

void Sleeper::sleep (long long delay) {
    std::chrono::milliseconds duration(delay);
    std::this_thread::sleep_for(duration);
}

void Sleeper::sleepMicro (long long delay) {
    std::chrono::microseconds duration(delay);
    std::this_thread::sleep_for(duration);
}
