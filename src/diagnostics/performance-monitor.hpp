#pragma once
#include <chrono>

class PerformanceMonitor {
    std::chrono::high_resolution_clock::time_point start_time;
public:
    void Start();
    double EndAndGetMilliseconds();
};
