#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>

using ClockType = std::chrono::steady_clock;

class Clock {
public:
    Clock();
    void setTimer();
    double getElapsedTime() const;
    double getInitialTime() const;
    ClockType::time_point getCurrentTime();

private:
    ClockType::time_point initialTime;
    ClockType::time_point previousTime;
    ClockType::time_point currentTime;
};

#endif // CLOCK_H
