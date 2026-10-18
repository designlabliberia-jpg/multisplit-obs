#include "performance-monitor.hpp"
#include <util/blog.h>

void PerformanceMonitor::Start() {
    start_time = std::chrono::high_resolution_clock::now();
}

double PerformanceMonitor::EndAndGetMilliseconds() {
    auto end_time = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();
    return ms;
}
